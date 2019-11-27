%{
#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "AST.h"
#define YY_DECL int yylex()
extern int yylineno;
extern char* yytext;
%}

%token IF 
%token ELSE
%token RETURN
%token INT
%token VOID
%token WHILE
%token <name>IDENTIFIER
%token <value>NUM

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

%type <node> program declaration_list declaration var_declaration type_specifier fun_declaration 
%type <node> params param_list param compound_stmt local_declarations statement_list statement
%type <node> expression_stmt selection_stmt iteration_stmt return_stmt expression var
%type <node> simple_expression additive_expression term factor call args arg_list
%type <value> relop addop mulop

%union{
     char* name;                /* terminal token: for symbol's name */
     int value;                 /* terminal token: for number */
     struct ASTNode* node;      /* unterminal token: abstract syntax tree node */
 }

%%
program: declaration_list				{ASTRoot = newProgram($1);}
;

 declaration_list: declaration_list declaration  {$$ = newDecList($1, $2);}
| declaration							{$$ = newDecList(NULL, $1);}
;

declaration: var_declaration			{$$ = newDec($1, 0);}
| fun_declaration						{$$ = newDec($1, 1);}
;

var_declaration: type_specifier IDENTIFIER Semicolon 				{$$ = newVarDec($1, $2);}
| type_specifier IDENTIFIER LeftBrack NUM RightBrack Semicolon		{$$ = newArrayDec($1, $2, $4);}
;

type_specifier: INT				{$$ = newTypeSpe(TYPE_INTEGER);}
| VOID							{$$ = newTypeSpe(TYPE_VOID);}
;

fun_declaration: type_specifier IDENTIFIER LeftPrnts params RightPrnts compound_stmt {$$ = newFunDec($1, $2, $4, $6);}
;

params: param_list				{$$ = newParams($1);}
| VOID							{$$ = newParams(NULL);}
;

param_list: param_list Semicolon param		{$$ = newParamList($1, $3);}
| param								{$$ = newParamList(NULL, $1);}
;

param: type_specifier IDENTIFIER							{$$ = newParam($1, $2, 0);}
| type_specifier IDENTIFIER LeftBrack RightBrack			{$$ = newParam($1, $2, 1);}
;

compound_stmt: LeftBrace local_declarations statement_list RightBrace	{$$ = newCompound($2, $3);}
;

local_declarations: local_declarations var_declaration	{$$ = newLocalDecs($1, $2);}
| 									{$$ = NULL;}
;

statement_list: statement_list statement	{$$ = newStmtList($1, $2);}
| 									{$$ = NULL;}
;

statement: expression_stmt			{$$ = newStmt($1);}
| compound_stmt						{$$ = newStmt($1);}
| selection_stmt					{$$ = newStmt($1);}
| iteration_stmt					{$$ = newStmt($1);}
| return_stmt						{$$ = newStmt($1);}
;

expression_stmt: expression Semicolon		{$$ = newExpStmt($1);}
| Semicolon									{$$ = NULL;}
;

selection_stmt: IF LeftPrnts expression RightPrnts statement		{$$ = newSelectStmt($3,$5,NULL);}
| IF LeftPrnts expression RightPrnts statement ELSE statement		{$$ = newSelectStmt($3,$5,$7);}
;

iteration_stmt: WHILE LeftPrnts expression RightPrnts statement 	{$$ = newIterStmt($3, $5);}
;

return_stmt: RETURN Semicolon			{$$ = newRetStmt(NULL);}
| RETURN expression Semicolon			{$$ = newRetStmt($2);}
;

expression: var Op_assign expression		{$$ = newAssignExp($1, $3);}
| simple_expression							{$$ = newExpression($1);}
;

var: IDENTIFIER												{$$ = newVar($1);}
| IDENTIFIER LeftBrack expression RightBrack				{$$ = newArrayVar($1, $3);}
;

simple_expression: additive_expression relop additive_expression	{$$ = newSimpExp($1, $2, $3);}
| additive_expression					{$$ = newSimpExp($1, -1, NULL);}
;

relop: Op_greater						{$$ = Op_greater;}
| Op_less								{$$ = Op_less;}
| Op_greaterequal						{$$ = Op_greaterequal;}
| Op_lessequal							{$$ = Op_lessequal;}
| Op_equal								{$$ = Op_equal;}
| Op_notequal							{$$ = Op_notequal;}
;

additive_expression: additive_expression addop term	{$$ = newAddExp($1, $2, $3);}
| term									{$$ = $1;}
;

addop: Op_add							{$$ = Op_add;}
| Op_subtract							{$$ = Op_subtract;}
;

term: term mulop factor					{$$ = newTerm($1, $2, $3);}
| factor								{$$ = $1;}
;

mulop: Op_multiply						{$$ = Op_multiply;}
| Op_divide								{$$ = Op_divide;}
;

factor: LeftPrnts expression RightPrnts 		{$$ = newTermFactor($2);}
| var											{$$ = newTermFactor($1);}
| call											{$$ = newTermFactor($1);}
| NUM											{$$ = newTermFactor(newNumNode($1));}
;

call: IDENTIFIER LeftPrnts args RightPrnts		{$$ = newCall($1, $3);}
;

args: arg_list							{$$ = newArgs($1);}
| 										{$$ = NULL;}
;

arg_list: arg_list Comma expression		{$$ = newArgList($1, $3);}
| expression							{$$ = $1;}
;

%%
