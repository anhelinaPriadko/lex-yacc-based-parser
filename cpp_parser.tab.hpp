/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_CPP_PARSER_TAB_HPP_INCLUDED
# define YY_YY_CPP_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 13 "cpp_parser.y"

  #include "ast.h"

#line 53 "cpp_parser.tab.hpp"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    NUMBER = 258,                  /* NUMBER  */
    ID = 259,                      /* ID  */
    STRING = 260,                  /* STRING  */
    T_INT = 261,                   /* T_INT  */
    T_DOUBLE = 262,                /* T_DOUBLE  */
    T_BOOL = 263,                  /* T_BOOL  */
    T_VOID = 264,                  /* T_VOID  */
    T_CLASS = 265,                 /* T_CLASS  */
    T_IF = 266,                    /* T_IF  */
    T_ELSE = 267,                  /* T_ELSE  */
    T_FOR = 268,                   /* T_FOR  */
    T_WHILE = 269,                 /* T_WHILE  */
    T_DO = 270,                    /* T_DO  */
    T_RETURN = 271,                /* T_RETURN  */
    T_PUBLIC = 272,                /* T_PUBLIC  */
    T_PRIVATE = 273,               /* T_PRIVATE  */
    T_BREAK = 274,                 /* T_BREAK  */
    T_CONTINUE = 275,              /* T_CONTINUE  */
    T_SWITCH = 276,                /* T_SWITCH  */
    T_CASE = 277,                  /* T_CASE  */
    T_DEFAULT = 278,               /* T_DEFAULT  */
    T_SEMI = 279,                  /* T_SEMI  */
    T_COMMA = 280,                 /* T_COMMA  */
    T_COLON = 281,                 /* T_COLON  */
    T_LPAREN = 282,                /* T_LPAREN  */
    T_RPAREN = 283,                /* T_RPAREN  */
    T_LBRACE = 284,                /* T_LBRACE  */
    T_RBRACE = 285,                /* T_RBRACE  */
    T_ASSIGN = 286,                /* T_ASSIGN  */
    T_PLUS = 287,                  /* T_PLUS  */
    T_MINUS = 288,                 /* T_MINUS  */
    T_MUL = 289,                   /* T_MUL  */
    T_DIV = 290,                   /* T_DIV  */
    T_MOD = 291,                   /* T_MOD  */
    T_INC = 292,                   /* T_INC  */
    T_DEC = 293,                   /* T_DEC  */
    T_EQ = 294,                    /* T_EQ  */
    T_NEQ = 295,                   /* T_NEQ  */
    T_LT = 296,                    /* T_LT  */
    T_GT = 297,                    /* T_GT  */
    T_LE = 298,                    /* T_LE  */
    T_GE = 299,                    /* T_GE  */
    T_AND = 300,                   /* T_AND  */
    T_OR = 301,                    /* T_OR  */
    T_NOT = 302,                   /* T_NOT  */
    T_DOT = 303,                   /* T_DOT  */
    T_PRINT = 304                  /* T_PRINT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 18 "cpp_parser.y"

  double num;
  char* id;
  char* str;
  ASTNode* node;                       /* for single AST nodes */
  std::vector<ASTNode*>* node_list;    /* for lists of AST nodes */
  TypeDescriptor* typeDesc;            /* for types like int/double/bool/void */

#line 128 "cpp_parser.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_CPP_PARSER_TAB_HPP_INCLUDED  */
