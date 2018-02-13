#include "entry.hpp"
#include "entry.tab.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <cstdarg>
//#include <ngx_core.h>
#include <regex.h>
#include "ngx_http_v2_push_rule_dynamic_parse.h"


static void set_g_json(const char *test_json) {
    cJSON *json = cJSON_Parse(test_json);
    g_json_root = json;
}

static void clear_g_ret() {
    g_push_ret.clear();
}

static void push_g_ret() {
    for (std::set<std::string>::iterator iter = g_push_ret.begin(); 
         iter != g_push_ret.end(); ++ iter) {
        std::cout << *iter << std::endl;
    }
}
//static void set_g_request(ngx_http_request_t *request) {
//    g_request = request;
//}

void push_rule_dynamic_parse(const char *type,
			 const char *rule_file_path,
			 const char *body ){
                         //ngx_http_request_t *request = NULL) {
#if YYDEBUG
	yydebug = 1;
#endif
	if (strcmp(type, "json") != 0) {
	    return;
	}
	set_g_json(body);
	//set_g_request(request);
        clear_g_ret();
	FILE* fp=fopen(rule_file_path, "r");
	if(fp==NULL)
	{
		printf("cannot open %s\n", rule_file_path);
		return;
	}
	extern FILE* yyin;
	yyin=fp;
	printf("-----begin parsing %s\n", rule_file_path);
	yyparse();
	puts("-----end parsing");
	fclose(fp);
        push_g_ret();
	
	return;

}
