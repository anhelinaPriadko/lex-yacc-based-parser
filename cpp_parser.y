/* cpp_parser.y Ч Bison (Yacc) grammar for an extended C++-subset */
%{
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include "ast.h"     /* доповнений заголовок AST */
ASTNode* ast_root = nullptr;
void yyerror(const char *s);
int yylex(void);
%}

/* union for semantic values */
%union {
  double num;
  char* id;
  char* str;
  ASTNode* node;
  std::vector<ASTNode*>* node_list;
}

/* tokens */
%token <num> NUMBER
%token <id> ID
%token <str> STRING
%token T_INT T_DOUBLE T_BOOL T_VOID T_CLASS
%token T_IF T_ELSE T_FOR T_WHILE T_DO T_RETURN
%token T_PUBLIC T_PRIVATE
%token T_BREAK T_CONTINUE
%token T_SWITCH T_CASE T_DEFAULT
%token T_SEMI T_COMMA T_COLON
%token T_LPAREN T_RPAREN T_LBRACE T_RBRACE T_ASSIGN
%token T_PLUS T_MINUS T_MUL T_DIV T_MOD
%token T_INC T_DEC
%token T_EQ T_NEQ T_LT T_GT T_LE T_GE
%token T_AND T_OR T_NOT
%token T_DOT
%token T_PRINT

/* operator precedence (from low to high) */
%left T_OR
%left T_AND
%left T_EQ T_NEQ
%left T_LT T_GT T_LE T_GE
%left T_PLUS T_MINUS
%left T_MUL T_DIV T_MOD
%right T_NOT
%right T_ASSIGN
%nonassoc T_INC T_DEC

/* nonterminals */
%type <node> translation_unit declaration decl_list function_defdeclarator
%type <node> stmt stmt_list compound_stmt expr expression_stmt selection_stmt iteration_stmt jump_stmt
%type <node> declaration_specifiers init_declarator_list init_declarator
%type <node> expr assignment_expr conditional_expr logical_or_expr logical_and_expr equality_expr relational_expr additive_expr multiplicative_expr unary_expr postfix_expr primary_expr
%type <node_list> parameter_list argument_list member_list

%%

translation_unit:
    /* zero or more declarations / function definitions / class declarations */
    decl_list               { ast_root = new BlockStmt($1); }
;

decl_list:
    /* empty */            { $$ = new std::vector<ASTNode*>(); }
  | decl_list declaration { $1->push_back($2); $$ = $1; }
  | decl_list function_defdeclarator { $1->push_back($2); $$ = $1; }
  | decl_list member_list { /* for top-level class-like members if needed */ $$ = $1; }
;

declaration:
    declaration_specifiers init_declarator_list T_SEMI
        { /* var declarations list */
          VarDeclList* vlist = new VarDeclList($1, $2); $$ = vlist;
        }
  | T_CLASS ID T_LBRACE member_list T_RBRACE T_SEMI
        { $$ = new ClassDecl(std::string($2), $4); free($2); }
;

declaration_specifiers:
    T_INT    { $$ = new TypeDescriptor("int"); }
  | T_DOUBLE { $$ = new TypeDescriptor("double"); }
  | T_BOOL   { $$ = new TypeDescriptor("bool"); }
  | T_VOID   { $$ = new TypeDescriptor("void"); }
;

init_declarator_list:
    init_declarator             { $$ = new std::vector<ASTNode*>(); $$->push_back($1); }
  | init_declarator_list T_COMMA init_declarator { $1->push_back($3); $$ = $1; }
;

init_declarator:
    ID                        { $$ = new VarDecl(std::string($1), nullptr); free($1); }
  | ID T_ASSIGN expr          { $$ = new VarDecl(std::string($1), $3); free($1); }
;

function_defdeclarator:
    declaration_specifiers ID T_LPAREN parameter_list T_RPAREN compound_stmt
        { $$ = new FunctionDecl($1, std::string($2), $4, dynamic_cast<BlockStmt*>($6)); free($2); }
;

parameter_list:
    /* empty */             { $$ = new std::vector<ASTNode*>(); }
  | parameter_list_nonempty { $$ = $1; }
;

parameter_list_nonempty:
    declaration_specifiers ID            { $$ = new std::vector<ASTNode*>(); $$->push_back(new ParamDecl($1, std::string($2))); free($2); }
  | parameter_list_nonempty T_COMMA declaration_specifiers ID { $1->push_back(new ParamDecl($3, std::string($4))); free($4); $$ = $1; }
;

member_list:
    /* empty */ { $$ = new std::vector<ASTNode*>(); }
  | member_list declaration { $1->push_back($2); $$ = $1; }
  | member_list function_defdeclarator { $1->push_back($2); $$ = $1; }
;

compound_stmt:
    T_LBRACE stmt_list T_RBRACE { /* take block */ $$ = new BlockStmt(*$2); delete $2; }
;

stmt_list:
    /* empty */ { $$ = new std::vector<ASTNode*>(); }
  | stmt_list stmt { $1->push_back($2); $$ = $1; }
;

stmt:
    expression_stmt { $$ = $1; }
  | compound_stmt   { $$ = $1; }
  | selection_stmt  { $$ = $1; }
  | iteration_stmt  { $$ = $1; }
  | jump_stmt       { $$ = $1; }
  | declaration     { $$ = $1; }
;

expression_stmt:
    T_SEMI            { $$ = new ExprStmt(nullptr); }
  | expr T_SEMI       { $$ = new ExprStmt($1); }
;

selection_stmt:
    T_IF T_LPAREN expr T_RPAREN stmt              { $$ = new IfStmt($3, $5, nullptr); }
  | T_IF T_LPAREN expr T_RPAREN stmt T_ELSE stmt  { $$ = new IfStmt($3, $5, $7); }
  | T_SWITCH T_LPAREN expr T_RPAREN compound_stmt { $$ = new SwitchStmt($3, dynamic_cast<BlockStmt*>($5)); }
;

iteration_stmt:
    T_WHILE T_LPAREN expr T_RPAREN stmt { $$ = new WhileStmt($3, $5); }
  | T_DO stmt T_WHILE T_LPAREN expr T_RPAREN T_SEMI { $$ = new DoWhileStmt($2, $5); }
  | T_FOR T_LPAREN expression_stmt expression_stmt expr T_RPAREN stmt
      { $$ = new ForStmt($3, $4, $5, $7); }
;

jump_stmt:
    T_BREAK T_SEMI   { $$ = new BreakStmt(); }
  | T_CONTINUE T_SEMI { $$ = new ContinueStmt(); }
  | T_RETURN T_SEMI  { $$ = new ReturnStmt(nullptr); }
  | T_RETURN expr T_SEMI { $$ = new ReturnStmt($2); }
;

expr: assignment_expr { $$ = $1; } ;

assignment_expr:
    conditional_expr                  { $$ = $1; }
  | unary_expr T_ASSIGN assignment_expr { $$ = new BinaryExpr("=", $1, $3); }
;

conditional_expr:
    logical_or_expr
  | logical_or_expr '?' expr ':' conditional_expr
      { $$ = new ConditionalExpr($1, $3, $5); }
;

logical_or_expr:
    logical_and_expr
  | logical_or_expr T_OR logical_and_expr { $$ = new BinaryExpr("||", $1, $3); }
;

logical_and_expr:
    equality_expr
  | logical_and_expr T_AND equality_expr { $$ = new BinaryExpr("&&", $1, $3); }
;

equality_expr:
    relational_expr
  | equality_expr T_EQ relational_expr { $$ = new BinaryExpr("==", $1, $3); }
  | equality_expr T_NEQ relational_expr { $$ = new BinaryExpr("!=", $1, $3); }
;

relational_expr:
    additive_expr
  | relational_expr T_LT additive_expr { $$ = new BinaryExpr("<", $1, $3); }
  | relational_expr T_GT additive_expr { $$ = new BinaryExpr(">", $1, $3); }
  | relational_expr T_LE additive_expr { $$ = new BinaryExpr("<=", $1, $3); }
  | relational_expr T_GE additive_expr { $$ = new BinaryExpr(">=", $1, $3); }
;

additive_expr:
    multiplicative_expr
  | additive_expr T_PLUS multiplicative_expr { $$ = new BinaryExpr("+", $1, $3); }
  | additive_expr T_MINUS multiplicative_expr { $$ = new BinaryExpr("-", $1, $3); }
;

multiplicative_expr:
    unary_expr
  | multiplicative_expr T_MUL unary_expr { $$ = new BinaryExpr("*", $1, $3); }
  | multiplicative_expr T_DIV unary_expr { $$ = new BinaryExpr("/", $1, $3); }
  | multiplicative_expr T_MOD unary_expr { $$ = new BinaryExpr("%", $1, $3); }
;

unary_expr:
    postfix_expr
  | T_PLUS unary_expr  { $$ = new UnaryExpr("+", $2); }
  | T_MINUS unary_expr { $$ = new UnaryExpr("-", $2); }
  | T_NOT unary_expr   { $$ = new UnaryExpr("!", $2); }
  | T_INC unary_expr   { $$ = new UnaryExpr("++", $2); }
  | T_DEC unary_expr   { $$ = new UnaryExpr("--", $2); }
;

postfix_expr:
    primary_expr
  | postfix_expr T_INC { $$ = new PostfixExpr($1, "++"); }
  | postfix_expr T_DEC { $$ = new PostfixExpr($1, "--"); }
  | postfix_expr T_LPAREN argument_list T_RPAREN { $$ = new CallExpr($1, $3); }
  | postfix_expr T_DOT ID { $$ = new MemberExpr($1, std::string($3)); free($3); }
;

primary_expr:
    ID        { $$ = new VarExpr(std::string($1)); free($1); }
  | NUMBER    { $$ = new NumberExpr($1); }
  | STRING    { $$ = new StringExpr(std::string($1)); free($1); }
  | T_LPAREN expr T_RPAREN { $$ = $2; }
;

argument_list:
    /* empty */ { $$ = new std::vector<ASTNode*>(); }
  | argument_list_nonempty { $$ = $1; }
;

argument_list_nonempty:
    expr { $$ = new std::vector<ASTNode*>(); $$->push_back($1); }
  | argument_list_nonempty T_COMMA expr { $1->push_back($3); $$ = $1; }
;

%%

/* error and helper */
void yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
}