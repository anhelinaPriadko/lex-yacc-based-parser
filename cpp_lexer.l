%{
#include "cpp_parser.tab.h"
#include <cstring>
#include <cstdlib>
#include <cstdio>
extern int yylineno;
void yyerror(const char *s);
%}

DIGIT   [0-9]
ID      [A-Za-z_][A-Za-z0-9_]*
WS      [ \t\r\n]+
STRING  \"([^\\\"]|\\.)*\"

%%

{WS}                 {
                        // підрахунок нових рядків щоб yylineno був коректним
                        for (char *p = yytext; *p; ++p) if (*p == '\n') ++yylineno;
                      }
"//".*               { /* line comment */ }
\/\*([^*]|\*+[^*/])*\*+\/   {
                        // block comment - підрахуємо перенос рядків в ньому
                        for (char *p = yytext; *p; ++p) if (*p == '\n') ++yylineno;
                      }

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

{STRING}             { 
                        // збережемо рядок без навколишніх лапок
                        std::string s(yytext);
                        if (s.size() >= 2 && s.front() == '"' && s.back() == '"') {
                            s = s.substr(1, s.size()-2);
                        }
                        yylval.str = strdup(s.c_str()); 
                        return STRING; 
                      }

{DIGIT}+("."{DIGIT}*)?([eE][+-]?{DIGIT}+)?  {
                        yylval.num = atof(yytext); return NUMBER;
                      }

{ID}                 { yylval.id = strdup(yytext); return ID; }

.                    {
                        // неочікуваний символ — виведемо повідомлення з номером рядка
                        fprintf(stderr, "Lex error at line %d: unexpected character '%s'\n", yylineno, yytext);
                        /* пропустимо його */
                      }
%%

int yywrap(void) { return 1; }