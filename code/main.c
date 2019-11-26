#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "global.h"
#include "y.tab.h"
#include "AST.h"
extern int yylineno;
struct ASTNode* ASTRoot = NULL;
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
int hashcode(char *key)
{
     int temp = 0;
     int i = 0;
     while(key[i] != '\0')
     {
          temp = ((temp<<SHIFT) + key[i]) % SIZE;
          i++;
     }
     return temp;
}
