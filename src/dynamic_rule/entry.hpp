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
    typeNodeUnknown,
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
        oprNodeType opr; /* operators */
    };
} nodeType;

objectTypeEnum get_object_type(const std::string &type_str);
void split_string(const std::string& s, std::vector<std::string>& v, const std::string& c);
cJSON *walk_through_json(cJSON *json, std::vector<std::string> &paths);
std::string int2string(int i);

extern std::map<int, nodeEnum> g_id_type;
extern int g_sym_int[26];
extern std::string g_sym_str[26];
extern cJSON *g_sym_json[26];
extern std::string g_buf_str, g_append_str;
extern objectTypeEnum g_object_type;
extern cJSON *g_json_root;
extern std::set<std::string> g_push_ret;


