%{
#include "entry.hpp"
#include "entry.tab.h"
extern "C" {
void yyerror(const char *);
int yywrap(void);
int yylex(void);
}
%}
%x _INT_VAR_BEGIN_
%x _STR_VAR_BEGIN_
%x _STR_CON_BEGIN_
%x _STR_CON_END_
%x _JSON_VAR_BEGIN_
%x _JSON_CON_BEGIN_
%x _COMMENT_

%%

"//" {
    BEGIN _COMMENT_;
}

<_COMMENT_>\n {
    BEGIN INITIAL;
}

<_COMMENT_>[^\n]+ {
}

<INITIAL>\" {
    BEGIN _STR_CON_BEGIN_;
    yylval.clear();
    return STR_CON_BEGIN;
}

<_STR_CON_BEGIN_>[^"]+ {
    BEGIN  _STR_CON_END_;
    yylval.s_entry = yytext;
    return STR;
}

<_STR_CON_END_>\" {
    BEGIN  INITIAL;
    return STR_CON_END;
}

json {
    BEGIN _JSON_VAR_BEGIN_;
    yylval.clear();
    return JSON_VAR_BEGIN;
}

<_JSON_VAR_BEGIN_>[a-zA-Z0-9/.]+ {
    yylval.s_entry = yytext;
    BEGIN  INITIAL;
    return JSON_VARIABLE;
}

$request_url {
    return REQUEST_URL;
}

$request_path {
    return REQUEST_PATH;
}

$response_json {
    BEGIN _JSON_CON_BEGIN_;
    yylval.clear();
    return JSON_CON_BEGIN;
}

<_JSON_CON_BEGIN_>[a-zA-Z0-9/.]+ {
    yylval.s_entry = yytext;
    BEGIN  INITIAL;
    return JSON_CON;
}

int {
    BEGIN _INT_VAR_BEGIN_;
    yylval.clear();
    return INT_VAR_BEGIN;
}

<_INT_VAR_BEGIN_>[a-z] {
    yylval.i_entry = *yytext - 'a';
    BEGIN  INITIAL;
    return INT_VARIABLE;
}

str {
    BEGIN _STR_VAR_BEGIN_;
    yylval.clear();
    return STR_VAR_BEGIN;
}

<_STR_VAR_BEGIN_>[a-z] {
    yylval.i_entry = *yytext - 'a';
    BEGIN  INITIAL;
    return STR_VARIABLE;
}

[0-9]+ {
    yylval.i_entry = atoi(yytext);
    return INT;
}

"parse_json" return PARSE_JSON;

[-()<>=+*/;{}.:] {
    return *yytext;
}
">=" return GE;
"<=" return LE;
"==" return EQ;
"!=" return NE;
"while" return WHILE;
"for" return FOR;
"if" return IF;
"else" return ELSE;
"print" return PRINT;
"push" return PUSH;
"..." return STR_APPEND_END;
".." return STR_APPEND;
"regex" return REGEX;
[ \t\n]+ ; /* ignore whitespace */

[a-zA-Z0-9/.]+ {
    yylval.s_entry = yytext;
    return VARIABLE;
}

. yyerror("Unknown character");
%%

int yywrap(void) {
    return 1;
}
