%{
#include "cpp_parser.tab.h"
#include <cstring>
#include <cstdlib>
%}

DIGIT   [0-9]
ID      [A-Za-z_][A-Za-z0-9_]*
WS      [ \t\r\n]+
STRING  \"([^\\\"]|\\.)*\"

%%

{WS}                 { /* skip whitespace */ }
"//".*               { /* line comment */ }
\/\*([^*]|\*+[^*/])*\*+\/   { /* block comment */ }

"int"                { return T_INT; }
"double"             { return T_DOUBLE; }
"bool"               { return T_BOOL; }
"void"               { return T_VOID; }
"class"              { return T_CLASS; }

"if"                 { return T_IF; }
"else"               { return T_ELSE; }
"for"                { return T_FOR; }
"while"              { return T_WHILE; }
"do"                 { return T_DO; }
"return"             { return T_RETURN; }
"break"              { return T_BREAK; }
"continue"           { return T_CONTINUE; }
"switch"             { return T_SWITCH; }
"case"               { return T_CASE; }
"default"            { return T_DEFAULT; }
"public"             { return T_PUBLIC; }
"private"            { return T_PRIVATE; }
"print"              { return T_PRINT; }

"=="                 { return T_EQ; }
"!="                 { return T_NEQ; }
"<="                 { return T_LE; }
">="                 { return T_GE; }
"&&"                 { return T_AND; }
"||"                 { return T_OR; }
"++"                 { return T_INC; }
"--"                 { return T_DEC; }

"+"                  { return T_PLUS; }
"-"                  { return T_MINUS; }
"*"                  { return T_MUL; }
"/"                  { return T_DIV; }
"%"                  { return T_MOD; }

"<"                  { return T_LT; }
">"                  { return T_GT; }

"="                  { return T_ASSIGN; }
";"                  { return T_SEMI; }
","                  { return T_COMMA; }
":"                  { return T_COLON; }
"."                  { return T_DOT; }

"("                  { return T_LPAREN; }
")"                  { return T_RPAREN; }
"{"                  { return T_LBRACE; }
"}"                  { return T_RBRACE; }

{STRING}             { yylval.str = strdup(yytext); return STRING; }

{DIGIT}+("."{DIGIT}*)?([eE][+-]?{DIGIT}+)?  {
                        yylval.num = atof(yytext); return NUMBER;
                      }

{ID}                 { yylval.id = strdup(yytext); return ID; }

.                    { /* unknown char — skip or return as error */ }
%%

int yywrap(void) { return 1; }