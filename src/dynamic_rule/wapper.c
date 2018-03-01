#include "ngx_http_v2_push_rule_dynamic_parse.h"

int push_rule_dynamic_parse_wapper(const char *type,
			 const char *rule_file_path,
			 const char *body,
                         ngx_http_request_t *request) {
    return push_rule_dynamic_parse(type, rule_file_path, body, request);
}
