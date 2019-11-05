%{
#include<cminus.h>
#include<stdio.h>
#include <stdlib.h>
#define YY_DECL int yylex()
%}

%token IF 
%token ELSE
%token RETURN
%token INT
%token VOID
%token WHILE
%token ID
%token NUM
%token Op_lessequal
%token Op_greaterequal
%token Op_equal
%token Op_notequal
%token LeftPrnts
%token RightPrnts
%token LeftBrack
%token RightBrack
%token LeftBrace
%token RightBrace
%token Op_add
%token Op_subtract
%token Op_multiply
%token Op_divide
%token Op_mod
%token Op_less
%token Op_greater
%token Op_assign
%token Semicolon
%token Comma
%token Eps
