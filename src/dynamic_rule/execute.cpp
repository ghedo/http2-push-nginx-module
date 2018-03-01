#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <regex.h>
#include<sys/types.h>
#include <stdio.h>
#include "entry.hpp"
#include "entry.tab.h"
extern "C" {
#include <ngx_core.h>
#include <ngx_http.h>
}

static cJSON *get_cjson_from_node(nodeType *p);
static std::string node2_str(nodeType *p);
static std::string jsonode2_str(nodeType *p);
static int jsonode2_int(nodeType *p);
static int regex_replace(std::string &source_str, const std::string &partten_str);

int ex(nodeType *p) {
    std::string ret;
    if (!p) return 0;
    switch(p->type) {
        case typeIntCon: 
            return p->con_int.value;
        case typeStrCon: 
            g_buf_str = *(p->con_str.p_value);
            return 0;
        case typeIntId: 
            return g_sym_int[p->int_id.i];
        case typeStrId: 
            return p->str_id.i;
        case typeJsonId: 
            return jsonode2_int(p);
        case typeOpr:
            switch(p->opr.oper) {
                case WHILE: 
                    while(ex(p->opr.op[0])) {
                        ex(p->opr.op[1]);
                    }
                    return 0;
                case FOR: 
                    if (p->opr.op[0]->type == typeJsonId) {
                        cJSON *json = get_cjson_from_node(p->opr.op[1]);
                        if (json == NULL) {
                            std::cout << "json for iter error" << std::endl;
                            return 0;
                        }
                        int count = cJSON_GetArraySize(json);
                        if (count == 0) {
                            return 0;
                        }
                        for (int cur = 0; cur < count; ++cur) {
                            g_sym_json[p->opr.op[0]->json_id.i] = cJSON_GetArrayItem(json,cur);
                            ex(p->opr.op[2]);
                        }
                    }
                    return 0;
                case IF: 
                    if (ex(p->opr.op[0])) 
                        ex(p->opr.op[1]);
                    else if (p->opr.nops > 2) 
                        ex(p->opr.op[2]);
                    return 0;
                case PUSH: 
                    if (p->opr.op[0]->type == typeIntId) {
                        std::cout << ex(p->opr.op[0]) << std::endl;
                        ret = int2string(ex(p->opr.op[0]));
                    } else if (p->opr.op[0]->type == typeStrId) {
                        std::cout << g_sym_str[p->opr.op[0]->str_id.i] << std::endl;
                        ret = g_sym_str[p->opr.op[0]->str_id.i];
                    } else if (p->opr.op[0]->type == typeStrCon) {
                        std::cout << p->opr.op[0]->con_str.p_value->c_str() << std::endl;
                        ret = p->opr.op[0]->con_str.p_value->c_str();
                    } else if (p->opr.op[0]->type == typeJsonId){
                        std::cout << jsonode2_str(p->opr.op[0]) << std::endl;
                        ret = jsonode2_str(p->opr.op[0]);
                    } else if (p->opr.op[0]->type == typeJsonCon) {
                        std::cout << jsonode2_str(p->opr.op[0]) << std::endl;
                        ret = jsonode2_str(p->opr.op[0]);
                    } else if (p->opr.op[0]->type == typeIntCon) {
                        std::cout << ex(p->opr.op[0]) << std::endl;
                        ret = int2string(ex(p->opr.op[0]));
                    }
                    if (!ret.empty()) {
                        g_push_ret.insert(ret);
                    }
                case PRINT: 
                    if (p->opr.op[0]->type == typeIntId) {
                        std::cout << ex(p->opr.op[0]) << std::endl;
                        ret = int2string(ex(p->opr.op[0]));
                    } else if (p->opr.op[0]->type == typeStrId) {
                        std::cout << g_sym_str[p->opr.op[0]->str_id.i] << std::endl;
                        ret = g_sym_str[p->opr.op[0]->str_id.i];
                    } else if (p->opr.op[0]->type == typeStrCon) {
                        std::cout << p->opr.op[0]->con_str.p_value->c_str() << std::endl;
                        ret = p->opr.op[0]->con_str.p_value->c_str();
                    } else if (p->opr.op[0]->type == typeJsonId){
                        std::cout << jsonode2_str(p->opr.op[0]) << std::endl;
                        ret = jsonode2_str(p->opr.op[0]);
                    } else if (p->opr.op[0]->type == typeJsonCon) {
                        std::cout << jsonode2_str(p->opr.op[0]) << std::endl;
                        ret = jsonode2_str(p->opr.op[0]);
                    } else if (p->opr.op[0]->type == typeIntCon) {
                        std::cout << ex(p->opr.op[0]) << std::endl;
                        ret = int2string(ex(p->opr.op[0]));
                    }
                    ngx_str_t tmp;
                    tmp.data = (u_char *)(ret.c_str());
                    tmp.len = ret.length();
                    ngx_log_error(NGX_LOG_INFO, g_request->connection->log, 0,
                      "dynamic_push log print: \"%V\"", &tmp);
                    return 0;
                case PARSE_JSON:
                    if (p->opr.op[1]->type == typeJsonId || 
                        p->opr.op[1]->type == typeJsonCon) {
                        std::string tmp_json_buf(jsonode2_str(p->opr.op[1]));
                        cJSON *json = cJSON_Parse(tmp_json_buf.c_str());
                        if (json == NULL) {
                            return 0;
                        }
                        g_sym_json[p->opr.op[0]->json_id.i] = json;
                        p->opr.op[0]->json_id.need_free = true;
                    }
                    return 0;
                case ';': 
                    ex(p->opr.op[0]);
                    return ex(p->opr.op[1]);
                case '=': 
                    if (p->opr.op[0]->type == typeIntId)
                        return g_sym_int[p->opr.op[0]->int_id.i] = ex(p->opr.op[1]);
                    else if (p->opr.op[0]->type == typeStrId) {
                        ex(p->opr.op[1]);
                        g_sym_str[p->opr.op[0]->str_id.i] = g_buf_str;
                        return 0; }
                    else if (p->opr.op[0]->type == typeJsonId) {
                        g_sym_json[p->opr.op[0]->json_id.i] = get_cjson_from_node(p->opr.op[1]);
                        return 0;
                    } else {
                    }
                case UMINUS: 
                    return -ex(p->opr.op[0]);
                case '+': 
                    return ex(p->opr.op[0]) + ex(p->opr.op[1]);
                case '-': 
                    return ex(p->opr.op[0]) - ex(p->opr.op[1]);
                case '*': 
                    return ex(p->opr.op[0]) * ex(p->opr.op[1]);
                case '/': 
                    return ex(p->opr.op[0]) / ex(p->opr.op[1]);
                case '<': 
                    return ex(p->opr.op[0]) < ex(p->opr.op[1]);
                case '>': 
                    return ex(p->opr.op[0]) > ex(p->opr.op[1]);
                case GE: 
                    return ex(p->opr.op[0]) >= ex(p->opr.op[1]);
                case LE: 
                    return ex(p->opr.op[0]) <= ex(p->opr.op[1]);
                case NE: 
                    return ex(p->opr.op[0]) != ex(p->opr.op[1]);
                case EQ: 
                    return ex(p->opr.op[0]) == ex(p->opr.op[1]);
                case STR_APPEND:
                    if (p->opr.op[0]->type == typeOpr) {
                        ex(p->opr.op[0]);
                    } else {
                        g_append_str.append(node2_str(p->opr.op[0]));
                    }
                    if (p->opr.op[1]->type == typeOpr) {
                        ex(p->opr.op[1]);
                    } else {
                        g_append_str.append(node2_str(p->opr.op[1]));
                    }
                    return 0;
                case '~':
                    if (p->opr.op[1]->type == typeOpr) {
                        ex(p->opr.op[1]);
                    }
                    if (g_append_str.empty()) {
                        g_sym_str[p->opr.op[0]->str_id.i].append(node2_str(p->opr.op[1]));
                    } else {
                        g_sym_str[p->opr.op[0]->str_id.i].append(g_append_str);
                        g_append_str.clear();
                    }
                    return 0;
                case REGEX:
                    regex_replace(g_sym_str[p->opr.op[0]->str_id.i], node2_str(p->opr.op[1]));
                    return 0;
            }
    }
    return 0;
}

static std::string node2_str(nodeType *p) {
    if (!p) return "";
    std::string ret;
    std::stringstream ss;
    switch(p->type) {
        case typeIntCon: 
            ss << p->con_int.value;
            ss >> ret;
            return ret;
        case typeIntId: 
            ss << g_sym_int[p->int_id.i];
            ss >> ret;
            return ret;
        case typeStrCon:
            return *(p->con_str.p_value);
        case typeStrId:
            return g_sym_str[p->str_id.i];
        case typeJsonId:
            ret = jsonode2_str(p);
            if (ret == "") {
                ret = int2string(jsonode2_int(p));
            }
            return ret;
        default:
            return "";
    }
}

static cJSON *get_cjson_from_node(nodeType *p) {
    if (p->type == typeJsonCon) {
        return p->con_json.cjson;
    } else if (p->type == typeJsonId) {
        if (p->json_id.path == NULL) {
            return g_sym_json[p->json_id.i];
        }
        std::vector<std::string> split_ret;
        split_string(*(p->json_id.path), split_ret, ".");
        return walk_through_json(g_sym_json[p->json_id.i], split_ret);
    } else {
        return NULL;
    }
}

static std::string jsonode2_str(nodeType *p) {
    cJSON *cjson = get_cjson_from_node(p);
    if (cjson == NULL || cjson->valuestring == NULL) {
        return "";
    }
    return cjson->valuestring;
}

static int jsonode2_int(nodeType *p) {
    cJSON *cjson = get_cjson_from_node(p);
    if (cjson == NULL) {
        return 0;
    }
    return cjson->valueint;
}


static int regex_replace(std::string &source_str, const std::string &partten_str) {
    const char *source = source_str.c_str();
    const char *regex = partten_str.c_str();
    regex_t comment;  
    size_t nmatch;  
    int i;  
    int cnt;  
    char str[512];  
    regmatch_t regmatch[1];  /* just 1 match */
    regcomp(&comment, regex, REG_EXTENDED|REG_NEWLINE);  
    while(1)  
    {  
        int j = regexec(&comment,source,sizeof(regmatch)/sizeof(regmatch_t),regmatch,0);  
        if(j != 0) 
            break;  
        for( i = 0; i< 1 && regmatch[i].rm_so!=-1;i++)  
        {  
            memset(str,sizeof(str),0);  
            cnt=regmatch[i].rm_eo-regmatch[i].rm_so;  
            memcpy(str,&source[regmatch[i].rm_so],cnt);  
            str[cnt]='\0';  
            source_str = str;
        }  
  
        if(regmatch[0].rm_so != -1)  
            source+= regmatch[0].rm_eo;  
    }  
    regfree(&comment);  
    return 0;  
}
