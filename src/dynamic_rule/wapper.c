#include "ngx_http_v2_push_rule_dynamic_parse.h"

//const char *g_test_json = "{\"key\" : \"{\\\"x\\\" : \\\"y\\\"}\", \"array\" : [\"1\", \"2\"], \
                            \"arrays\" : [{\"a\": \"22343hsdjkfhjksdfhkj543\", \"b\": 4,  \
                                           \"userList\" : [ \
                                               {\"userNo\" : \"678\"} \
             ] }]}";
const char *g_test_json = "{ \
	\"code\": 200,\
	\"message\": \"OK\",\
	\"recentMessage\": {\
		\"userUnreadCount\": 2,\
		\"userFirstMessageNo\": 1,\
		\"userLastMessageNo\": 3,\
		\"messageList\": [{\
			\"messageTypeCode\": 18,\
			\"number\": 111, \
                        \"sub\": [ {\"key\" : \"vvv\"} \
                   ] \
		}]\
	}\
}";

void push_rule_dynamic_parse_wapper(const char *type,
			 const char *rule_file_path,
			 const char *body) {
    push_rule_dynamic_parse(type, rule_file_path, body);
}
int main (void) {
   push_rule_dynamic_parse_wapper("json",
			    "file.txt",
      g_test_json);
    return 0;

}
