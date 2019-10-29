#include <stdio.h>
#include "cminus.h"

extern int yylex();


int main()
{
	int ntoken;
	ntoken = yylex();
	while (ntoken){
		printf("defined %d\n", ntoken);
		ntoken = yylex();
	}
	return 0;

}
