%{
#include<stdio.h>
#include <stdlib.h>
#define YY_DECL int yylex()
extern int yylineno;
%}

%token IF 
%token ELSE
%token RETURN
%token INT
%token VOID
%token WHILE
%token IDENTIFIER
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

program: declaration_list {printf("program\n");}
	   ;
		  
expression_stmt : expression Semicolon {printf("expression_stmt\n");}
			   | Semicolon {printf("expression_stmt\n");}
			   ;
			
selection_stmt : IF LeftPrnts statement RightPrnts {printf("selection_stmt\n");}
			   | IF LeftPrnts expression RightPrnts statement ELSE statement {printf("selection_stmt\n");}
			   ;
			   
iteration_stmt : WHILE LeftPrnts expression RightPrnts statement {printf("iteration_stmt\n");}
			   ;

declaration_list: declaration declaration_list {printf("declaration_list\n");}
                | declaration {printf("declaration_list\n");}
				;
				
declaration : fun_declaration {printf("declaration\n");}
            | var_declaration {printf("declaration\n");}
            ;

var_declaration : type_specifier IDENTIFIER Semicolon
				| type_specifier IDENTIFIER LeftBrack NUM RightBrack {printf("var_declaration\n");}
                ;

type_specifier : INT {printf("type\n");}
				| VOID {printf("type\n");}
				;

fun_declaration : type_specifier IDENTIFIER LeftPrnts params RightPrnts compound_stmt {printf("fun_declaration\n");}
                ;
				
params : params_list {printf("params\n");}
	   | VOID {printf("params\n");}
	   ;
	   
params_list : params_list Comma param {printf("params_list\n");}
			| param {printf("params_list\n");}
			;
			
param : type_specifier IDENTIFIER {printf("param\n");}
	  | type_specifier IDENTIFIER LeftBrack RightBrack {printf("param\n");}
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
		  
return_stmt : RETURN Semicolon {printf("return_stmt\n");}
			| RETURN expression {printf("return_stmt\n");}
			;
			
expression : var Op_equal expression {printf("expression\n");}
		   | simple_expression {printf("expression\n");}
		   ;
		   
var : IDENTIFIER {printf("var\n");}
	| IDENTIFIER LeftBrack expression RightBrack {printf("var\n");}
	;
	
simple_expression : additive_expression relop additive_expression {printf("simple_expression\n");}
				  | additive_expression {printf("simple_expression\n");}
				  ;
				
relop : Op_lessequal {printf("relop\n");}
	  | Op_less {printf("relop\n");}
	  | Op_greater {printf("relop\n");}
	  | Op_greaterequal {printf("relop\n");}
	  | Op_equal {printf("relop\n");}
	  | Op_notequal {printf("relop\n");}
	  ;

additive_expression : additive_expression addop term {printf("additive_expression\n");}
					| term {printf("additive_expression\n");}
					;
					
addop : Op_add {printf("addop\n");}
	  | Op_subtract {printf("addop\n");}
	  ;
	  
term : term mulop factor {printf("term\n");}
	 | factor {printf("term\n");}
	 ;
	 
mulop : Op_multiply {printf("mulop\n");}
	  | Op_divide {printf("mulop\n");}
	  ;
	  
factor : LeftPrnts expression RightPrnts {printf("factor\n");}
	   | var {printf("factor\n");}
	   | call {printf("factor\n");}
	   | NUM {printf("factor\n");}
	   ;
	   
call : IDENTIFIER LeftPrnts args RightPrnts {printf("call\n");}
	 ;
	 
args : args_list {printf("args\n");}
	 | Eps {printf("args\n");}
	 ;
	 
args_list : args_list Comma expression {printf("args_list\n");}
		  | expression {printf("args_list\n");}
		  ;
	  
%%
