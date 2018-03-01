%{
#include <stdio.h>
#include <cstdarg>
#include "entry.hpp"
#define YYDEBUG 1
extern "C" {
/* prototypes */
nodeType *opr(int oper, int nops, ...);
nodeType *id_int(int i);
nodeType *id_str(int i);
nodeType *id_json(std::string &sValue);
nodeType *id_var(std::string &sValue);
nodeType *con_int(int value);
nodeType *con_str(std::string &sValue);
nodeType *con_json(std::string &sValue);
void freeNode(nodeType *p);
extern int yylex(void);
void yyerror(const char *s);
}
int ex(nodeType *p);

std::map<int, nodeEnum> g_id_type;
int g_sym_int[26];
std::string g_sym_str[26];
cJSON *g_sym_json[26];
std::string g_buf_str, g_append_str;
std::string g_request_url, g_request_path;
typedef struct ngx_http_request_s ngx_http_request_t;
ngx_http_request_t *g_request;
objectTypeEnum g_object_type;
cJSON *g_json_root;
std::set<std::string> g_push_ret;
%}

%token<i_entry> INT
%token<s_entry> STR
%token<s_entry> JSON_CON
%token<s_entry> OBJECT_TYPE
%token<i_entry> INT_VARIABLE
%token<i_entry> STR_VARIABLE 
%token<s_entry> JSON_VARIABLE 
%token<s_entry> VARIABLE 
%token STR_CON_BEGIN STR_CON_END JSON_VAR_BEGIN INT_VAR_BEGIN STR_VAR_BEGIN JSON_CON_BEGIN
%token WHILE IF FOR PRINT PUSH PARSE_JSON
%token REQUEST_URL REQUEST_PATH
%nonassoc IFX
%nonassoc ELSE
%left '.'
%left GE LE EQ NE '>' '<'
%left '+' '-' REGEX
%left '*' '/'
%left STR_APPEND_END
%left STR_APPEND
%nonassoc UMINUS
%type <n_ptr> stmt expr stmt_list
%%

program:
function { }
;

function:
function stmt {ex($2); freeNode($2); }
| /* NULL */
;

stmt:
';' { $$ = opr(';', 2, NULL, NULL); }
| expr ';' { $$ = $1; }
| PRINT expr ';' { $$ = opr(PRINT, 1, $2); }
| PUSH expr ';' { $$ = opr(PUSH, 1, $2); }
| JSON_VAR_BEGIN JSON_VARIABLE '=' PARSE_JSON expr ';' { $$ = opr(PARSE_JSON, 2, id_json($2), $5); }
| INT_VAR_BEGIN INT_VARIABLE '=' expr ';' { $$ = opr('=', 2, id_int($2), $4); }
| STR_VAR_BEGIN STR_VARIABLE '=' expr ';' { $$ = opr('=', 2, id_str($2), $4); }
| JSON_VAR_BEGIN JSON_VARIABLE '=' expr ';' { $$ = opr('=', 2, id_json($2), $4); }
| VARIABLE STR_APPEND_END expr ';'{ $$ = opr('~', 2, id_var($1), $3); }
| VARIABLE REGEX expr ';'{ $$ = opr(REGEX, 2, id_var($1), $3); }
| WHILE '(' expr ')' stmt { $$ = opr(WHILE, 2, $3, $5); }
| FOR '(' expr ':' expr ')' stmt { $$ = opr(FOR, 3, $3, $5, $7); }
| IF '(' expr ')' stmt %prec IFX { $$ = opr(IF, 2, $3, $5); }
| IF '(' expr ')' stmt ELSE stmt { $$ = opr(IF, 3, $3, $5, $7); }
| '{' stmt_list '}' { $$ = $2; }
;

stmt_list:
stmt { $$ = $1; }
| stmt_list stmt { $$ = opr(';', 2, $1, $2); }
;

expr:
INT { $$ = con_int($1); }
|STR_CON_BEGIN STR STR_CON_END {$$ = con_str($2);}
| JSON_CON_BEGIN JSON_CON {$$ = con_json($2);}
| VARIABLE { $$ = id_var($1); }
| REQUEST_URL { $$ = con_str(g_request_url); }
| REQUEST_PATH { $$ = con_str(g_request_path); }
| JSON_VAR_BEGIN JSON_VARIABLE { $$ = id_json($2); }
| '-' expr %prec UMINUS { $$ = opr(UMINUS, 1, $2); }
| expr '+' expr { $$ = opr('+', 2, $1, $3); }
| expr '-' expr { $$ = opr('-', 2, $1, $3); }
| expr '*' expr { $$ = opr('*', 2, $1, $3); }
| expr '/' expr { $$ = opr('/', 2, $1, $3); }
| expr '<' expr { $$ = opr('<', 2, $1, $3); }
| expr '>' expr { $$ = opr('>', 2, $1, $3); }
| expr GE expr { $$ = opr(GE, 2, $1, $3); }
| expr LE expr { $$ = opr(LE, 2, $1, $3); }
| expr NE expr { $$ = opr(NE, 2, $1, $3); }
| expr EQ expr { $$ = opr(EQ, 2, $1, $3); }
| expr STR_APPEND expr { $$ = opr(STR_APPEND, 2, $1, $3); }
| '(' expr ')' { $$ = $2; }
;

%%

#define SIZEOF_NODETYPE ((char *)&p->con_int - (char *)p)

nodeType *con_int(int value) {
    nodeType *p;
    size_t nodeSize;
    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(intConNodeType);
    if ((p = (nodeType *)malloc(nodeSize)) == NULL) {
        yyerror("out of memory");
    }
    /* copy information */
    p->type = typeIntCon;
    p->con_int.value = value;
    return p;
}

nodeType *con_str(std::string &sValue) {
    nodeType *p;
    size_t nodeSize;
    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(strConNodeType);
    if ((p = (nodeType *)malloc(nodeSize)) == NULL) {
        yyerror("out of memory");
    }
    /* copy information */
    p->type = typeStrCon;
    p->con_str.p_value = new std::string(sValue);
    if (p->con_str.p_value == NULL) {
        yyerror("out of memory");
    }
    return p;
}

nodeType *con_json(std::string &sValue) {
    nodeType *p;
    size_t nodeSize;
    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(jsonConNodeType);
    if ((p = (nodeType *)malloc(nodeSize)) == NULL) {
        yyerror("out of memory");
    }
    /* copy information */
    p->type = typeJsonCon;
    std::vector<std::string> split_ret;
    split_string(sValue, split_ret, ".");

    p->con_json.cjson = walk_through_json(g_json_root, split_ret);
    if (p->con_json.cjson == NULL) {
        yyerror("json walk error");
    }
    return p;
}

static nodeEnum get_var_type(int i) {
    std::map<int, nodeEnum>::iterator iter = g_id_type.find(i);
    if (iter == g_id_type.end()) {
        return typeNodeUnknown;
    }
    return iter->second;
}

static nodeType *create_int_id_node(int i) {
    nodeType *p;
    size_t nodeSize;
    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(intIdNodeType);
    if ((p = (nodeType *)malloc(nodeSize)) == NULL) {
        yyerror("out of memory");
    }
    /* copy information */
    p->type = typeIntId;
    p->int_id.i = i;
    return p;
}

static nodeType *create_str_id_node(int i) {
    nodeType *p;
    size_t nodeSize;
    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(strIdNodeType);
    if ((p = (nodeType *)malloc(nodeSize)) == NULL) {
        yyerror("out of memory");
    }
    /* copy information */
    p->type = typeStrId;
    p->str_id.i = i;
    return p;
}

static nodeType *create_json_id_node(std::string &sValue) {
    nodeType *p;
    size_t nodeSize;
    if (sValue.empty()) {
        yyerror("empty json key");
    }
    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(jsonIdNodeType);
    if ((p = (nodeType *)malloc(nodeSize)) == NULL) {
        yyerror("out of memory");
    }
    /* copy information */
    p->type = typeJsonId;
    p->json_id.i = (char)(*sValue.begin()) - 'a';
    p->json_id.need_free = false;
    if (sValue.size() == 1) {
        p->json_id.path = NULL;
    } else {
        p->json_id.path = new std::string(sValue.begin() + 2, sValue.end());
    }
    return p;
}

nodeType *id_var(std::string &sValue) {
    nodeType *p;
    int i = (char)(*sValue.begin()) - 'a';
    nodeEnum node_type = get_var_type(i);
    if (node_type == typeNodeUnknown) {
        yyerror("can't find var");
        return NULL;
    }
    if (node_type == typeIntId) {
        p = create_int_id_node(i);
    } else if (node_type == typeStrId) {
        p = create_str_id_node(i);
    } else if (node_type == typeJsonId) {
        p = create_json_id_node(sValue);
    }
    return p;
}

nodeType *id_int(int i) {
    nodeType *p;
    p = create_int_id_node(i);
    g_id_type[i] = typeIntId;
    return p;
}

nodeType *id_str(int i) {
    nodeType *p;
    p = create_str_id_node(i);
    g_id_type[i] = typeStrId;
    return p;
}

nodeType *id_json(std::string &sValue) {
    nodeType *p;
    p = create_json_id_node(sValue);
    g_id_type[p->json_id.i] = typeJsonId;
    return p;
}

nodeType *opr(int oper, int nops, ...) {
    va_list ap;
    nodeType *p;
    size_t nodeSize;
    int i;
    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(oprNodeType) +
               (nops - 1) * sizeof(nodeType*);
    if ((p = (nodeType *)malloc(nodeSize)) == NULL) {
        yyerror("out of memory");
    }
    /* copy information */
    p->type = typeOpr;
    p->opr.oper = oper;
    p->opr.nops = nops;
    va_start(ap, nops);
    for (i = 0; i < nops; i++) {
        p->opr.op[i] = va_arg(ap, nodeType*);
    }
    va_end(ap);
    return p;
}

void freeNode(nodeType *p) {
    int i;
    if (!p) return;
    if (p->type == typeStrCon) {
        delete p->con_str.p_value;
    } else if (p->type == typeJsonId && p->json_id.path != NULL) {
        delete p->json_id.path;
    }
    if (p->type == typeOpr) {
        for (i = 0; i < p->opr.nops; i++)
            freeNode(p->opr.op[i]);
    }
    free (p);
}

void yyerror(const char *s) {
    fprintf(stdout, "%s\n", s);
}
