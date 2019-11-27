#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "global.h"
#include "y.tab.h"
#include "AST.h"
extern int yylineno;
extern int yylex();
struct ASTNode* ASTRoot = NULL;

void yyerror(const char* msg)
{
     if (msg)
     printf("%s\n", msg);
}
int yywrap(){
     return 1;
}
int main(int argc, char *argv[])
{
     int i;
     yylineno = 1;
     if(argc == 2)
     {
          FILE *fp = fopen(argv[1], "r");
          yyrestart(fp);
          yyparse();
          fclose(fp);
     }
     else
     {
          FILE *fp = fopen("test.cm", "r");
          if(fp==NULL)
          {
               printf("Usage: C- [filename]:\n");
               return -1;
          }
          
          yyrestart(fp);
          yyparse();
          fclose(fp);
     }
     printAST(ASTRoot, 0);
	 printf("Press x to continue");
	 getch();
     return 0;
}
