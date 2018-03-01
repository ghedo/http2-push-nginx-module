#include <iostream>
#include <string.h>
#include <stdio.h>
#include <cstdarg>
#include <regex.h>
#include "entry.hpp"
#include "entry.tab.h"
#include "ngx_http_v2_push_rule_dynamic_parse.h"

static void set_g_request_content(ngx_http_request_t *r) {
    g_request = r;
    g_request_url = std::string(r->uri.data, r->uri.data + r->uri.len + 1);
    g_request_path = g_request_url.substr(0, g_request_url.find_last_of("/")+1);
}

static void set_g_json(const char *test_json) {
    cJSON *json = cJSON_Parse(test_json);
    g_json_root = json;
}

static void clear_g_ret() {
    g_push_ret.clear();
}

static int push_g_ret(ngx_http_request_t *request) {
    int rc = 0;
    for (std::set<std::string>::iterator iter = g_push_ret.begin(); 
         iter != g_push_ret.end(); ++ iter) {
         std::cout << *iter << std::endl;
         rc = ngx_http_v2_push(request, (u_char*)(iter->c_str()), iter->length());
    }
    return rc;
}

int push_rule_dynamic_parse(const char *type,
			 const char *rule_file_path,
			 const char *body,
                         ngx_http_request_t *request) {
    int rc = 0;
#if YYDEBUG
    yydebug = 1;
#endif
    if (strcmp(type, "json") != 0) {
        return rc;
    }
    set_g_json(body);
    set_g_request_content(request);
    clear_g_ret();
    FILE* fp=fopen(rule_file_path, "r");
    if(fp==NULL)
    {
        printf("cannot open %s\n", rule_file_path);
        return rc;
    }
    extern FILE* yyin;
    yyin=fp;
    printf("-----begin parsing %s\n", rule_file_path);
    yyparse();
    puts("-----end parsing");
    fclose(fp);
    rc = push_g_ret(request);
    return rc;
}
