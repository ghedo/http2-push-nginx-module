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
nodeType *con_int(int value);
nodeType *con_str(std::string &sValue);
nodeType *con_json(std::string &sValue);
void freeNode(nodeType *p);
extern int yylex(void);
void yyerror(const char *s);
}
int ex(nodeType *p, std::string *str_ret = NULL);
int g_sym_int[26];
std::string g_sym_str[26];
cJSON *g_sym_json[26];
std::string g_buf_str;
objectTypeEnum g_object_type;
cJSON *g_json_root;
std::set<std::string> g_push_ret;
%}

%token<i_entry> INT
%token<s_entry> STR
%token<s_entry> JSON_CON
%token<s_entry> OBJECT_TYPE
%token<s_entry> INT_JSON_BEGIN
%token<i_entry> INT_VARIABLE
%token<i_entry> STR_VARIABLE 
%token<s_entry> JSON_VARIABLE 
%token<s_entry> INT_VAR_BEGIN 
%token<s_entry> STR_VAR_BEGIN
%token<s_entry> STR_CON_BEGIN
%token<s_entry> JSON_VAR_BEGIN
%token<s_entry> JSON_CON_BEGIN
%token WHILE IF FOR PRINT PUSH PARSE_JSON
%nonassoc IFX
%nonassoc ELSE
%left '.'
%left GE LE EQ NE '>' '<'
%left '+' '-' STR_APPEND REGEX
%left '*' '/'
%nonassoc UMINUS
%type <n_ptr> stmt expr stmt_list
%%

program:
function { }
;

function:function stmt {ex($2); freeNode($2); }
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
| STR_VAR_BEGIN STR_VARIABLE STR_APPEND expr ';'{ $$ = opr(STR_APPEND, 2, id_str($2), $4); }
| STR_VAR_BEGIN STR_VARIABLE REGEX expr ';'{ $$ = opr(REGEX, 2, id_str($2), $4); }
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
|STR_CON_BEGIN STR {$$ = con_str($2);}
| JSON_CON_BEGIN JSON_CON {$$ = con_json($2);}
| INT_VAR_BEGIN INT_VARIABLE { $$ = id_int($2); }
| STR_VAR_BEGIN STR_VARIABLE { $$ = id_str($2); }
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
| '(' expr ')' { $$ = $2; }
;

%%

#define SIZEOF_NODETYPE ((char *)&p->con_int - (char *)p)
nodeType *con_int(int value) {
    nodeType *p;size_t nodeSize;
    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(intConNodeType);
    if ((p = (nodeType *)malloc(nodeSize)) == NULL)
    yyerror("out of memory");
    /* copy information */
    p->type = typeIntCon;
    p->con_int.value = value;
    return p;
}

nodeType *con_str(std::string &sValue) {
    nodeType *p;size_t nodeSize;
    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(strConNodeType);
    if ((p = (nodeType *)malloc(nodeSize)) == NULL)
    yyerror("out of memory");
    /* copy information */
    p->type = typeStrCon;
    p->con_str.p_value = new std::string(sValue.begin(), sValue.end() - 1);
    if (p->con_str.p_value == NULL)
        yyerror("out of memory");
    return p;
}

nodeType *con_json(std::string &sValue) {
    nodeType *p;size_t nodeSize;
    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(jsonConNodeType);
    if ((p = (nodeType *)malloc(nodeSize)) == NULL)
    yyerror("out of memory");
    /* copy information */
    p->type = typeJsonCon;
    std::vector<std::string> split_ret;
    split_string(sValue, split_ret, ".");

    p->con_json.cjson = walk_through_json(g_json_root, split_ret);
    if (p->con_json.cjson == NULL)
        yyerror("json walk error");
    return p;
}

nodeType *id_int(int i) {
    nodeType *p;
    size_t nodeSize;
    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(intIdNodeType);
    if ((p = (nodeType *)malloc(nodeSize)) == NULL)
    yyerror("out of memory");
    /* copy information */
    p->type = typeIntId;
    p->int_id.i = i;
   return p;
}

nodeType *id_str(int i) {
    nodeType *p;
    size_t nodeSize;
    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(strIdNodeType);
    if ((p = (nodeType *)malloc(nodeSize)) == NULL)
    yyerror("out of memory");
    /* copy information */
    p->type = typeStrId;
    p->str_id.i = i;
   return p;
}

nodeType *id_json(std::string &sValue) {
    printf("in... %s\n", sValue.c_str());
    nodeType *p;
    size_t nodeSize;
    if (sValue.empty()) {
        yyerror("empty json key");
    }
    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(jsonIdNodeType);
    if ((p = (nodeType *)malloc(nodeSize)) == NULL)
        yyerror("out of memory");
    /* copy information */
    p->type = typeJsonId;
    printf(".............%s", sValue.c_str());
    p->json_id.i = (char)(*sValue.begin()) - 'a';
    p->json_id.need_free = false;
    if (sValue.size() == 1) {
        p->json_id.path = NULL;
    } else {
        p->json_id.path = new std::string(sValue.begin() + 2, sValue.end());
    }

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
    if ((p = (nodeType *)malloc(nodeSize)) == NULL)
    yyerror("out of memory");
    /* copy information */
    p->type = typeOpr;
    p->opr.oper = oper;
    p->opr.nops = nops;
    va_start(ap, nops);
    for (i = 0; i < nops; i++)
        p->opr.op[i] = va_arg(ap, nodeType*);
    va_end(ap);
    return p;
}

void freeNode(nodeType *p) {
    int i;
    if (!p) return;
    if (p->type == typeStrCon) {
        delete p->con_str.p_value;
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

/*
int main(void) {
    #if YYDEBUG
    yydebug = 1;
    #endif
    set_g_json();
    const char* sFile="file.txt";
    FILE* fp=fopen(sFile, "r");  
    if(fp==NULL)  
    {  
        printf("cannot open %s\n", sFile);  
        return -1;  
    } 
    extern FILE* yyin;
    yyin=fp;
    printf("-----begin parsing %s\n", sFile); 
    yyparse();
    puts("-----end parsing");  
    fclose(fp);  
    return 0;
}
*/
