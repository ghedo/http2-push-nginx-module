#pragma once

#ifdef   __cplusplus
extern "C" {
#endif
#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include <ngx_http_v2_module.h>

#include "../ngx_http_v2_push.h"
int push_rule_dynamic_parse(const char *type,
			 const char *rule_file_path,
			 const char *body, 
                         ngx_http_request_t *request);
#ifdef   __cplusplus
}
#endif
