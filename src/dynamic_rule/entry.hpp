#pragma once
#include <string>
#include <vector>
#include <map>
#include <set>
extern "C" {
    #include "cJSON.h"
}

typedef enum { 
    typeIntCon, 
    typeStrCon,
    typeJsonCon,
    typeIntId, 
    typeStrId, 
    typeJsonId,
    //typeStrObj,
    typeOpr,
} nodeEnum;

typedef enum { 
    typeJson, 
    typeXml,
    typeHtml, 
    typeUnknown, 
} objectTypeEnum;

typedef struct nodeTypeTag nodeType;

/*  */
struct entry_t {
    std::string s_entry;
    int         i_entry;
    nodeType   *n_ptr;
    void clear();
};

#define YYSTYPE entry_t

/* int constants */
typedef struct {
    int value; /* value of constant */
} intConNodeType;

/* string constants */
typedef struct {
    std::string *p_value; /* value of constant */
} strConNodeType;

typedef struct {
    cJSON *cjson;
} jsonConNodeType;

/* identifiers */
typedef struct {
    std::string *p_var_name;
} IdNodeType;

/* json identifiers */
typedef struct {
    int i; /* subscript to sym array */
    std::string *path;
    bool need_free; /* if json is create with new json string, need free it */
} jsonIdNodeType;

/* int identifiers */
typedef struct {
    int i; /* subscript to sym array */
} intIdNodeType;

/* string identifiers */
typedef struct {
    int i; /* subscript to sym array */
} strIdNodeType;

/* operators */
typedef struct {
    int oper; /* operator */
    int nops; /* number of operands */
    struct nodeTypeTag *op[1]; /* operands (expandable) */
} oprNodeType;

typedef struct nodeTypeTag {
    nodeEnum type; /* type of node */
/* union must be last entry in nodeType */
/* because operNodeType may dynamically increase */
    union {
        intConNodeType con_int; /* int constants */
        strConNodeType con_str; /* string constants */
        intIdNodeType int_id; /* int identifiers */
        jsonConNodeType con_json;
        jsonIdNodeType json_id;
        strIdNodeType str_id; /* string identifiers */
        IdNodeType var_id;
        oprNodeType opr; /* operators */
    };
} nodeType;

/*
class GlobalMemSpace {
private:
    typedef std::string var_name_t;
    typedef std::pair<nodeEnum , void * > value_t;
    typedef std::map<var_name_t, value_t > var_map_t;
    typedef std::map<std::string, int > int_var_t;
    typedef std::map<std::string, std::string > str_var_t;
    typedef std::map<std::string, cJSON * > json_var_t;
    typedef std::vector<std::string> push_ret_var_t;
    typedef std::set<var_name_t> tmp_var_name_t;
    
    static var_map_t g_sym_var;
    static int_var_t g_sym_int;
    static str_var_t g_sym_str;
    static json_var_t g_sym_json;
    static tmp_var_name_t g_tmp_var_name;
    static push_ret_var_t g_push_ret;
    static objectTypeEnum g_object_type;
    static cJSON *g_json_root;

public:
    static void clear() {
        g_sym_var.clear();
        g_sym_int.clear();
        g_sym_str.clear();
        g_sym_json.clear();
        g_tmp_var_name.clear();
        g_push_ret.clear();
        g_object_type = typeUnknown;
        cJSON_Delete(g_json_root);
    }
    static var_name_t genarate_tmp_var_name();
    static int check_exist_var(var_name_t &var_name);
    static int set_var(var_name_t &var_name, value_t *value);
    static int get_var(var_name_t &var_name, value_t **value);

};
*/

objectTypeEnum get_object_type(const std::string &type_str);
void split_string(const std::string& s, std::vector<std::string>& v, const std::string& c);
cJSON *walk_through_json(cJSON *json, std::vector<std::string> &paths);
std::string int2string(int i);

extern int g_sym_int[26];
extern std::string g_sym_str[26];
extern cJSON *g_sym_json[26];
extern std::string g_buf_str;
extern objectTypeEnum g_object_type;
extern cJSON *g_json_root;
extern std::set<std::string> g_push_ret;


