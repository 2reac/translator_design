
%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cminus.h"
%}

%%

"else"		{return ELSE;}
"if"		{return IF;}
"int"		{return INT;}
"return" 	{return RETURN;}
"void" 		{return VOID;}
"while" 	{return WHILE;}

[a-zA-Z][a-zA-Z0-9_]* {printf ("ID: %s\n",yytext); return ID;}
[0-9]+		{printf ("NUM: %d\n",atoi(yytext)); return NUM;}

"<="		{return Op_lessequal;}
">="		{return Op_greaterequal;}
"=="		{return Op_equal;}
"!="		{return Op_notequal;}

"("			{return LeftPrnts;}
")"			{return RightPrnts;}
"["			{return LeftBrack;}
"]"			{return RightBrack;}
"{"			{return LeftBrace;}
"}"			{return RightBrace;}
"+"			{return Op_add;}
"-"			{return Op_subtract;}
"*"			{return Op_multiply;}
"/"			{return Op_divide;}
"%"			{return Op_mod;}
"<"			{return Op_less;}
">"			{return Op_greater;}
"="			{return Op_assign;}
";"			{return Semicolon;}
","			{return Comma;}

[ \t\n]+

%%

int yywrap(void)
{
	return 1;
}

void comment(void)
{
	char c, prev = 0;
  
	while ((c = input()) != 0)      
	{
		if (c == '/' && prev == '*')
			return;
		prev = c;
	}
}


int column = 0;

void count(void)
{
	int i;

	for (i = 0; yytext[i] != '\0'; i++)
		if (yytext[i] == '\n')
			column = 0;
		else if (yytext[i] == '\t')
			column += 8 - (column % 8);
		else
			column++;
}
