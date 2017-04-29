
/*
 * Copyright (C) Alessandro Ghedini
 */


#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include <ngx_http_v2_module.h>

#include "ngx_http_v2_push.h"


#define NGX_HTTP_V2_AUTHORITY_INDEX       1
#define NGX_HTTP_V2_METHOD_GET_INDEX      2
#define NGX_HTTP_V2_PATH_INDEX            4
#define NGX_HTTP_V2_SCHEME_HTTP_INDEX     6
#define NGX_HTTP_V2_SCHEME_HTTPS_INDEX    7


typedef struct {
    ngx_flag_t    enable;
    ngx_uint_t    pushed_streams;
} ngx_http_v2_push_srv_conf_t;

typedef struct {
    ngx_array_t  *paths;
} ngx_http_v2_push_loc_conf_t;

typedef struct {
    ngx_queue_t   pushes;
} ngx_http_v2_push_ctx_t;


static ngx_int_t ngx_http_v2_push_add_variables(ngx_conf_t *cf);
static ngx_int_t ngx_http_v2_push_variable(ngx_http_request_t *r,
    ngx_http_variable_value_t *v, uintptr_t data);

static void *ngx_http_v2_push_create_srv_conf(ngx_conf_t *cf);
static char *ngx_http_v2_push_merge_srv_conf(ngx_conf_t *cf, void *parent,
    void *child);

static void *ngx_http_v2_push_create_loc_conf(ngx_conf_t *cf);
static char *ngx_http_v2_push_merge_loc_conf(ngx_conf_t *cf, void *parent,
    void *child);

static char *ngx_http_v2_push_path(ngx_conf_t *cf, ngx_command_t *cmd,
    void *conf);

static ngx_int_t ngx_http_v2_push_module_init(ngx_cycle_t *cycle);


static ngx_int_t ngx_http_v2_push_filter_init(ngx_conf_t *cf);
static ngx_int_t ngx_http_v2_push_header_filter(ngx_http_request_t *r);


static ngx_http_output_header_filter_pt  ngx_http_next_header_filter;


static ngx_command_t  ngx_http_v2_push_commands[] = {
    { ngx_string("http2_server_push"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_CONF_FLAG,
      ngx_conf_set_flag_slot,
      NGX_HTTP_SRV_CONF_OFFSET,
      offsetof(ngx_http_v2_push_srv_conf_t, enable),
      NULL },

    { ngx_string("http2_max_pushed_streams"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_CONF_FLAG,
      ngx_conf_set_num_slot,
      NGX_HTTP_SRV_CONF_OFFSET,
      offsetof(ngx_http_v2_push_srv_conf_t, pushed_streams),
      NULL },

    { ngx_string("http2_push_path"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_HTTP_LIF_CONF
                        |NGX_CONF_TAKE1,
      ngx_http_v2_push_path,
      NGX_HTTP_LOC_CONF_OFFSET,
      0,
      NULL},

      ngx_null_command
};


static ngx_http_module_t  ngx_http_v2_push_module_ctx = {
    ngx_http_v2_push_add_variables,        /* preconfiguration */
    ngx_http_v2_push_filter_init,          /* postconfiguration */

    NULL,                                  /* create main configuration */
    NULL,                                  /* init main configuration */

    ngx_http_v2_push_create_srv_conf,      /* create server configuration */
    ngx_http_v2_push_merge_srv_conf,       /* merge server configuration */

    ngx_http_v2_push_create_loc_conf,      /* create location configuration */
    ngx_http_v2_push_merge_loc_conf,       /* merge location configuration */
};


ngx_module_t  ngx_http_v2_push_module = {
    NGX_MODULE_V1,
    &ngx_http_v2_push_module_ctx,          /* module context */
    ngx_http_v2_push_commands,             /* module directives */
    NGX_HTTP_MODULE,                       /* module type */
    NULL,                                  /* init master */
    ngx_http_v2_push_module_init,          /* init module */
    NULL,                                  /* init process */
    NULL,                                  /* init thread */
    NULL,                                  /* exit thread */
    NULL,                                  /* exit process */
    NULL,                                  /* exit master */
    NGX_MODULE_V1_PADDING
};


static ngx_http_variable_t  ngx_http_v2_push_vars[] = {

    { ngx_string("http2_pushed"), NULL,
      ngx_http_v2_push_variable, 0, 0, 0 },

    { ngx_null_string, NULL, NULL, 0, 0, 0 }
};


static ngx_int_t
ngx_http_v2_push_add_variables(ngx_conf_t *cf)
{
    ngx_http_variable_t  *var, *v;

    for (v = ngx_http_v2_push_vars; v->name.len; v++) {
        var = ngx_http_add_variable(cf, &v->name, v->flags);
        if (var == NULL) {
            return NGX_ERROR;
        }

        var->get_handler = v->get_handler;
        var->data = v->data;
    }

    return NGX_OK;
}


static ngx_int_t
ngx_http_v2_push_variable(ngx_http_request_t *r,
    ngx_http_variable_value_t *v, uintptr_t data)
{

    if (r->stream) {
        v->data = (u_char *) (r->stream->node->id % 2 ? "." : "p");
        v->len = 1;
        v->valid = 1;
        v->no_cacheable = 0;
        v->not_found = 0;

        return NGX_OK;
    }

    *v = ngx_http_variable_null_value;

    return NGX_OK;
}


static ngx_int_t
ngx_http_v2_push_module_init(ngx_cycle_t *cycle)
{
    return NGX_OK;
}


static ngx_int_t
ngx_http_v2_push_filter_init(ngx_conf_t *cf)
{
    ngx_http_next_header_filter = ngx_http_top_header_filter;
    ngx_http_top_header_filter = ngx_http_v2_push_header_filter;

    return NGX_OK;
}


static void *
ngx_http_v2_push_create_srv_conf(ngx_conf_t *cf)
{
    ngx_http_v2_push_srv_conf_t  *h2pscf;

    h2pscf = ngx_pcalloc(cf->pool, sizeof(ngx_http_v2_push_srv_conf_t));
    if (h2pscf == NULL) {
        return NULL;
    }

    h2pscf->enable = NGX_CONF_UNSET;

    return h2pscf;
}


static char *
ngx_http_v2_push_merge_srv_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_http_v2_push_srv_conf_t *prev = parent;
    ngx_http_v2_push_srv_conf_t *conf = child;

    ngx_conf_merge_value(conf->enable, prev->enable, 0);

    return NGX_CONF_OK;
}


static void *
ngx_http_v2_push_create_loc_conf(ngx_conf_t *cf)
{
    ngx_http_v2_push_loc_conf_t *conf;

    conf = ngx_pcalloc(cf->pool, sizeof(ngx_http_v2_push_loc_conf_t));
    if (conf == NULL) {
        return NULL;
    }

    return conf;
}


static char *
ngx_http_v2_push_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_http_v2_push_loc_conf_t *prev = parent;
    ngx_http_v2_push_loc_conf_t *conf = child;

    if (conf->paths == NULL) {
        conf->paths = prev->paths;
    }

    return NGX_CONF_OK;
}


static char *
ngx_http_v2_push_path(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_v2_push_loc_conf_t *h2plc = conf;
    ngx_str_t                   *value = cf->args->elts;
    ngx_str_t                   *path;

    if (h2plc->paths == NULL) {
        h2plc->paths = ngx_array_create(cf->pool, 1, sizeof(ngx_str_t));
        if (h2plc->paths == NULL) {
            return NGX_CONF_ERROR;
        }
    }

    path = ngx_array_push(h2plc->paths);
    if (path == NULL) {
        return NGX_CONF_ERROR;
    }

    path->data = value[1].data;
    path->len  = value[1].len;

    return NGX_CONF_OK;
}


static ngx_http_v2_push_ctx_t *
ngx_http_v2_push_create_ctx(ngx_http_request_t *r)
{
    ngx_http_v2_push_ctx_t  *ctx;

    ctx = ngx_pcalloc(r->pool, sizeof(ngx_http_v2_push_ctx_t));
    if (ctx == NULL) {
        return NULL;
    }

    ngx_queue_init(&ctx->pushes);

    ngx_http_set_ctx(r, ctx, ngx_http_v2_push_module);

    return ctx;
}


static ngx_int_t
ngx_http_v2_push_promise_frame_handler(ngx_http_v2_connection_t *h2c,
    ngx_http_v2_out_frame_t *frame)
{
    ngx_chain_t           *cl, *ln;
    ngx_http_v2_stream_t  *stream;

    stream = frame->stream;
    cl = frame->first;

    for ( ;; ) {
        if (cl->buf->pos != cl->buf->last) {
            frame->first = cl;

            ngx_log_debug2(NGX_LOG_DEBUG_HTTP, h2c->connection->log, 0,
                           "http2:%ui PUSH_PROMISE frame %p was sent partially",
                           stream->node->id, frame);

            return NGX_AGAIN;
        }

        ln = cl->next;

        if (cl->buf->tag == (ngx_buf_tag_t) &ngx_http_v2_module) {
            cl->next = stream->free_frame_headers;
            stream->free_frame_headers = cl;

        } else {
            cl->next = stream->free_bufs;
            stream->free_bufs = cl;
        }

        if (cl == frame->last) {
            break;
        }

        cl = ln;
    }

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, h2c->connection->log, 0,
                   "http2:%ui PUSH_PROMISE frame %p was sent",
                   stream->node->id, frame);

    stream->request->header_size += NGX_HTTP_V2_FRAME_HEADER_SIZE
                                    + frame->length;

    ngx_http_v2_handle_frame(stream, frame);

    ngx_http_v2_handle_stream(h2c, stream);

    return NGX_OK;
}


static ngx_http_v2_out_frame_t *
ngx_http_v2_create_push_promise_frame(ngx_http_request_t *r, u_char *pos,
    u_char *end, ngx_uint_t promised_sid)
{
    u_char                    type, flags;
    size_t                    rest, frame_size;
    ngx_buf_t                *b;
    ngx_chain_t              *cl, **ll;
    ngx_http_v2_stream_t     *stream;
    ngx_http_v2_out_frame_t  *frame;

    stream = r->stream;
    rest = end - pos;

    frame = ngx_palloc(r->pool, sizeof(ngx_http_v2_out_frame_t));
    if (frame == NULL) {
        return NULL;
    }

    frame->handler = ngx_http_v2_push_promise_frame_handler;
    frame->stream = stream;
    frame->length = rest + 4;
    frame->blocked = 1;
    frame->fin = 0;

    ll = &frame->first;

    type = NGX_HTTP_V2_PUSH_PROMISE_FRAME;
    flags = NGX_HTTP_V2_NO_FLAG;
    frame_size = stream->connection->frame_size;

    for ( ;; ) {

        if (type == NGX_HTTP_V2_PUSH_PROMISE_FRAME) {
            if ((rest + 4) <= frame_size) {
                frame_size = rest + 4;
                flags |= NGX_HTTP_V2_END_HEADERS_FLAG;
            }
            b = ngx_create_temp_buf(r->pool, NGX_HTTP_V2_FRAME_HEADER_SIZE + 4);

        } else {
            if (rest <= frame_size) {
                frame_size = rest;
                flags |= NGX_HTTP_V2_END_HEADERS_FLAG;
            }
            b = ngx_create_temp_buf(r->pool, NGX_HTTP_V2_FRAME_HEADER_SIZE);
        }

        if (b == NULL) {
            return NULL;
        }

        b->last = ngx_http_v2_write_len_and_type(b->last, frame_size, type);
        *b->last++ = flags;
        b->last = ngx_http_v2_write_sid(b->last, stream->node->id);

        if (type == NGX_HTTP_V2_PUSH_PROMISE_FRAME) {
            b->last = ngx_http_v2_write_sid(b->last, promised_sid);
        }

        b->tag = (ngx_buf_tag_t) &ngx_http_v2_module;

        cl = ngx_alloc_chain_link(r->pool);
        if (cl == NULL) {
            return NULL;
        }

        cl->buf = b;

        *ll = cl;
        ll = &cl->next;

        b = ngx_calloc_buf(r->pool);
        if (b == NULL) {
            return NULL;
        }

        b->pos = pos;

        pos += frame_size;
        rest -= frame_size;
        if (type == NGX_HTTP_V2_PUSH_PROMISE_FRAME) {
            pos -= 4;
            rest += 4;
        }

        b->last = pos;
        b->start = b->pos;
        b->end = b->last;
        b->temporary = 1;

        cl = ngx_alloc_chain_link(r->pool);
        if (cl == NULL) {
            return NULL;
        }

        cl->buf = b;

        *ll = cl;
        ll = &cl->next;

        if (rest) {
            type = NGX_HTTP_V2_CONTINUATION_FRAME;
            flags = NGX_HTTP_V2_NO_FLAG;
            continue;
        }

        b->last_buf = 0;
        cl->next = NULL;
        frame->last = cl;

        ngx_log_debug4(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "http2:%ui create PUSH_PROMISE frame %p: len:%uz, id: %d",
                       stream->node->id, frame, frame->length, 2);

        return frame;
    }
}


static ngx_int_t
ngx_http_v2_header_filter_promise(ngx_http_request_t *r,
    ngx_http_v2_stream_t *pushed)
{
    u_char                    *pos, *start, *tmp;
    size_t                     len, tmp_len;

    ngx_http_request_t        *sr;
    ngx_http_v2_out_frame_t   *promise;

#if (NGX_HTTP_GZIP)
    ngx_int_t                  has_accept_encoding = 0;
#endif
    ngx_int_t                  has_user_agent = 0;

    sr = pushed->request;

    len = 3 * NGX_HTTP_V2_INT_OCTETS
          + sr->uri.len
          + sr->headers_in.host->value.len;

#if (NGX_HTTP_GZIP)
    if (r->headers_in.accept_encoding) {
        len += sr->headers_in.accept_encoding->key.len;
        len += sr->headers_in.accept_encoding->value.len;

        has_accept_encoding = 1;
    }
#endif

    if (r->headers_in.user_agent) {
        len += sr->headers_in.user_agent->key.len;
        len += sr->headers_in.user_agent->value.len;

        has_user_agent = 1;
    }

    tmp_len = len;

    tmp = ngx_pcalloc(r->pool, tmp_len);
    pos = ngx_pcalloc(r->pool, len);

    if (pos == NULL || tmp == NULL) {
        return NGX_ERROR;
    }

    start = pos;

    *pos++ = NGX_HTTP_V2_AUTHORITY_INDEX;
    pos = ngx_http_v2_write_value(pos, sr->headers_in.host->value.data,
                                  sr->headers_in.host->value.len, tmp);

    *pos++ = ngx_http_v2_indexed(NGX_HTTP_V2_METHOD_GET_INDEX);

    *pos++ = NGX_HTTP_V2_PATH_INDEX;
    pos = ngx_http_v2_write_value(pos, sr->uri.data, sr->uri.len, tmp);

    if (!ngx_strncmp(sr->schema_start, "http", 5)) {
        *pos++ = ngx_http_v2_indexed(NGX_HTTP_V2_SCHEME_HTTP_INDEX);
    } else {
        *pos++ = ngx_http_v2_indexed(NGX_HTTP_V2_SCHEME_HTTPS_INDEX);
    }

    if (has_accept_encoding) {
        *pos++ = 0;

        pos = ngx_http_v2_write_name(pos,
                                     sr->headers_in.accept_encoding->key.data,
                                     sr->headers_in.accept_encoding->key.len,
                                     tmp);

        pos = ngx_http_v2_write_value(pos,
                                     sr->headers_in.accept_encoding->value.data,
                                     sr->headers_in.accept_encoding->value.len,
                                     tmp);
    }

    if (has_user_agent) {
        *pos++ = 0;

        pos = ngx_http_v2_write_name(pos,
                                     sr->headers_in.user_agent->key.data,
                                     sr->headers_in.user_agent->key.len,
                                     tmp);

        pos = ngx_http_v2_write_value(pos,
                                     sr->headers_in.user_agent->value.data,
                                     sr->headers_in.user_agent->value.len,
                                     tmp);
    }

    promise = ngx_http_v2_create_push_promise_frame(r, start, pos,
                                                    pushed->node->id);
    if (promise == NULL) {
        return NGX_ERROR;
    }

    ngx_http_v2_queue_blocked_frame(r->stream->connection, promise);
    r->stream->queued++;

    ngx_post_event(sr->connection->read, &ngx_posted_events);

    return NGX_OK;
}


static void
ngx_http_v2_push_handler(ngx_event_t *ev)
{
    ngx_connection_t    *fc;
    ngx_http_request_t  *r;

    fc = ev->data;
    r = fc->data;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, fc->log, 0,
                   "http2 push request handler");

    ngx_http_v2_run_request(r);
}


static ngx_int_t
ngx_http_v2_push_populate_header(ngx_http_request_t *r, ngx_table_elt_t *host)
{
    ngx_table_elt_t            *h;
    ngx_http_header_t          *hh;
    ngx_http_core_main_conf_t  *cmcf;

    h = ngx_list_push(&r->headers_in.headers);
    if (h == NULL) {
        return NGX_ERROR;
    }

    h->hash        = host->hash;
    h->key         = host->key;
    h->value       = host->value;
    h->lowcase_key = host->lowcase_key;

    cmcf = ngx_http_get_module_main_conf(r, ngx_http_core_module);

    hh = ngx_hash_find(&cmcf->headers_in_hash, h->hash,
                       h->lowcase_key, h->key.len);

    if (hh == NULL) {
        return NGX_ERROR;
    }

    if (hh->handler(r, h, hh->offset) != NGX_OK) {
        /*
         * request has been finalized already
         * in ngx_http_process_host()
         */
        return NGX_ABORT;
    }

    return NGX_OK;
}


static ngx_int_t
ngx_http_v2_push_populate_path(ngx_http_request_t *r, u_char *u_str, size_t u_len)
{
    r->uri_start = u_str;
    r->uri_end   = u_str + u_len;

    if (ngx_http_parse_uri(r) != NGX_OK) {
        ngx_log_error(NGX_LOG_INFO, r->connection->log, 0,
                      "invalid push path: \"%*s\"", u_len, u_str);

        return NGX_ERROR;
    }

    return ngx_http_process_request_uri(r);
}


ngx_int_t
ngx_http_v2_push(ngx_http_request_t *r, u_char *u_str, size_t u_len)
{
    ngx_http_request_t            *sr;

    ngx_http_v2_push_ctx_t        *ctx;
    ngx_http_v2_connection_t      *h2c;
    ngx_http_v2_push_srv_conf_t   *h2pscf;
    ngx_http_v2_node_t            *node;
    ngx_http_v2_stream_t          *stream;

    h2c = r->stream->connection;

    h2pscf = ngx_http_get_module_srv_conf(r, ngx_http_v2_push_module);

    if (!h2c->enable_push || !h2pscf->enable) {
        return NGX_DECLINED;
    }

    ctx = ngx_http_get_module_ctx(r, ngx_http_v2_push_module);
    if (ctx == NULL) {
        ctx = ngx_http_v2_push_create_ctx(r);
        if (ctx == NULL) {
            return NGX_ERROR;
        }
    }

    node = ngx_http_v2_get_node_by_id(h2c, h2c->next_sid, 1);

    if (node == NULL) {
        goto error;
    }

    h2c->next_sid += 2;

    stream = ngx_http_v2_create_stream(h2c);
    if (stream == NULL) {
        goto error;
    }

    sr = stream->request;

    sr->request_length = h2c->state.length;

    sr->connection->read->handler = ngx_http_v2_push_handler;

    /* populate request method */
    sr->method = NGX_HTTP_GET;
    sr->method_name.data =  (u_char *) "GET";
    sr->method_name.len = sizeof("GET") - 1;

    /* populate request schema */
    sr->schema_start = (u_char *) (r->connection->ssl ? "https" : "http");
    sr->schema_end = sr->schema_start + ngx_strlen(sr->schema_start);

    if (ngx_http_v2_push_populate_path(sr, u_str, u_len) != NGX_OK) {
        goto error;
    }

    if (ngx_http_v2_push_populate_header(sr, r->headers_in.host) != NGX_OK) {
        goto error;
    }

    if (ngx_http_v2_push_populate_header(sr, r->headers_in.accept_encoding) != NGX_OK) {
        goto error;
    }

    if (ngx_http_v2_push_populate_header(sr, r->headers_in.user_agent) != NGX_OK) {
        goto error;
    }

    stream->in_closed = h2c->state.flags & NGX_HTTP_V2_END_STREAM_FLAG;
    stream->node = node;

    node->stream = stream;

    ngx_queue_insert_tail(&ctx->pushes, &stream->queue);

    return NGX_OK;

error:

    return NGX_ERROR;
}


static ngx_int_t
ngx_http_v2_push_header_filter(ngx_http_request_t *r)
{
    ngx_http_v2_push_ctx_t       *ctx;
    ngx_http_v2_push_loc_conf_t  *conf;

    if (!r->stream) {
        goto done;
    }

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "http2 push header filter");

    conf = ngx_http_get_module_loc_conf(r, ngx_http_v2_push_module);

    if (conf->paths) {
        size_t      i;
        ngx_str_t  *p = conf->paths->elts;

        for (i = 0; i < conf->paths->nelts; i++) {
            ngx_http_v2_push(r, p[i].data, p[i].len);
        }
    }

    ctx = ngx_http_get_module_ctx(r, ngx_http_v2_push_module);
    if (ctx == NULL) {
        goto done;
    }

    while (!ngx_queue_empty(&ctx->pushes)) {
        ngx_queue_t           *q;
        ngx_http_v2_stream_t  *push;

        q = ngx_queue_head(&ctx->pushes);
        ngx_queue_remove(q);

        push = ngx_queue_data(q, ngx_http_v2_stream_t, queue);

        ngx_http_v2_header_filter_promise(r, push);
    }

done:

    return ngx_http_next_header_filter(r);
}
