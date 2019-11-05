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

%% /* Grammar rules and actions follow */

program: declaration_list 
	   ;

		  
expression_stmt : expression Semicolon {printf("expression_stmt\n");}
			   | Semicolon {printf("expression_stmt\n");}
			   ;
			
selection_stmt : IF LeftPrnts statement RightPrnts {printf("selection_stmt\n");}
			   | IF LeftPrnts expression RightPrnts statement ELSE statement {printf("selection_stmt\n");}
			   ;
			   
iteration_stmt : WHILE LeftPrnts expression RightPrnts statement {printf("iteration_stmt\n");}
declaration_list: declaration declaration_list {printf("declaration_list\n");}
                | declaration {printf("declaration_list\n");}
				;
				
declaration : fun_declaration {printf("declaration\n");}
            | var_declaration {printf("declaration\n");}
            ;

var_declaration : type_specifier ID Semicolon
				| type_specifier ID LeftBrack NUM RightBrack {printf("var_declaration\n");}
                ;

type_specifier : INT {printf("type\n");}
				| VOID {printf("type\n");}
				;

fun_declaration : type_specifier ID LeftPrnts params RightPrnts compound_stmt {printf("fun_declaration\n");}
                ;
				
params : params_list {printf("params\n");}
	   | VOID {printf("params\n");}
	   ;
	   
params_list : params_list Comma param {printf("params_list\n");}
			| param {printf("params_list\n");}
			;
			
param : type_specifier ID {printf("param\n");}
	  | type_specifier ID LeftBrack RightBrack {printf("param\n");}
	  ;
	  
compound_stmt : LeftBrace local_declarations statement_list RightBrace {printf("compound_stmt\n");}
			  ;
			  
local_declarations : local_declarations var_declaration {printf("local_declarations\n");}
				   | Eps {printf("local_declarations\n");}
				   ;
				   
statement_list : statement_list statement {printf("statement_list\n");}
			   | Eps {printf("statement_list\n");}
			   ;
			   
statement : expression_stmt {printf("statement\n");}
		  | compound_stmt {printf("statement\n");}
		  | selection_stmt {printf("statement\n");}
		  | iteration_stmt {printf("statement\n");}
		  | return_stmt {printf("statement\n");}
		  ;
			 