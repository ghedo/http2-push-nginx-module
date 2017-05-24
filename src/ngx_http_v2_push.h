
/*
 * Copyright (C) Nginx, Inc.
 * Copyright (C) Valentin V. Bartenev
 */

#ifndef _NGX_HTTP_V2_PUSH_H_INCLUDED_
#define _NGX_HTTP_V2_PUSH_H_INCLUDED_

struct ngx_http_v2_push_state {
    ngx_array_t  *already_pushed;
};

#define ngx_http_v2_indexed(i)      (128 + (i))

#define NGX_HTTP_V2_ENCODE_RAW            0
#define NGX_HTTP_V2_ENCODE_HUFF           0x80

#define ngx_http_v2_write_name(dst, src, len, tmp)                            \
    ngx_http_v2_string_encode(dst, src, len, tmp, 1)
#define ngx_http_v2_write_value(dst, src, len, tmp)                           \
    ngx_http_v2_string_encode(dst, src, len, tmp, 0)

u_char *ngx_http_v2_string_encode(u_char *dst, u_char *src, size_t len,
    u_char *tmp, ngx_uint_t lower);

void ngx_http_v2_handle_frame(ngx_http_v2_stream_t *stream,
    ngx_http_v2_out_frame_t *frame);
void ngx_http_v2_handle_stream(ngx_http_v2_connection_t *h2c,
    ngx_http_v2_stream_t *stream);

ngx_http_v2_stream_t *ngx_http_v2_create_stream(
    ngx_http_v2_connection_t *h2c);
ngx_http_v2_node_t *ngx_http_v2_get_node_by_id(
    ngx_http_v2_connection_t *h2c, ngx_uint_t sid, ngx_uint_t alloc);

void ngx_http_v2_run_request(ngx_http_request_t *r);

#endif /* _NGX_HTTP_V2_PUSH_H_INCLUDED_ */
