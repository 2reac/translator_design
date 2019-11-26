#include "AST.h"
#include "global.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
struct ASTNode* newProgram(struct ASTNode* decList)
{
     return decList;
}
// decList==NULL => declaration
struct ASTNode* newDecList(struct ASTNode* decList, struct ASTNode* declaration)
{
     struct ASTNode* root = NULL;
     struct ASTNode* node = decList;
     assert(declaration != NULL);
     // declaration_list: declaration_list declaration
     if(decList != NULL)
     {
          while(node->sibling != NULL)
               node = node->sibling;
          node->sibling = declaration;
          root = decList;
     }
     else                       // declaration_list: declaration
     {
          root = declaration;
     }
     return root;
}
// type: 0=var, 1=fun
struct ASTNode* newDec(struct ASTNode* declaration, int type)
{
     return declaration;
}
// var_declaration: type_specifier ID SEMI
struct ASTNode* newVarDec(struct ASTNode* typeSpecifier, char* ID)
{
     struct ASTNode* root = newASTNode(VARDEC_AST);
     root->child[0] = typeSpecifier;
     root->child[1] = newIDNode(ID);
     return root;
}
// var_declaration: type_specifier ID LSB NUMBER RSB SEMI
struct ASTNode* newArrayDec(struct ASTNode* typeSpecifier, char* ID, int size)
{
     struct ASTNode* root = newASTNode(ARRAYDEC_AST);
     root->child[0] = typeSpecifier;
     root->child[1] = newIDNode(ID);
     root->child[2] = newNumNode(size);
     return root;
}
struct ASTNode* newTypeSpe(ExpType type)
{
     struct ASTNode* root = newASTNode(TYPE_AST);
     root->type = type;
     return root;
}
// fun_declaration: type_specifier ID LBracket params RBracket compound_stmt
struct ASTNode* newFunDec(struct ASTNode* typeSpecifier, char* ID, struct ASTNode* params, struct ASTNode* compound)
{
     struct ASTNode* root = newASTNode(FUNDEC_AST);
     root->child[0] = typeSpecifier;
     root->child[1] = newIDNode(ID);
     root->child[2] = params;
     root->child[3] = compound;
     return root;
}
// paramList==NULL => params: VOID
struct ASTNode* newParams(struct ASTNode* paramList)
{
     // params: param_list
     struct ASTNode* root = NULL;
     if(paramList != NULL)
     {
          return paramList;
     }
     else
     {
          /* root = newASTNode(TYPE_AST); */
          /* root->type = TYPE_VOID; */
          return NULL;
     }
}
// paramList==NULL => param_list:param
struct ASTNode* newParamList(struct ASTNode* paramList, struct ASTNode* param)
{
     // param_list: param_list SEMI param
     struct ASTNode* node = paramList;
     if(paramList != NULL)
     {
          while(node->sibling != NULL)
               node = node->sibling;
          node->sibling = param;
          return paramList;
     }
     else // param_list: param
     {
          return param;
     }
}
// type: 1=id is array 0=otherwise
struct ASTNode* newParam(struct ASTNode* typeSpecifier, char* ID, int type)
{
     // param: type_specifier ID
     struct ASTNode* root = NULL;
     if(type == 0)
     {
          root = newASTNode(PARAMID_AST);
          root->child[0] = typeSpecifier;
          root->child[1] = newIDNode(ID);
     }
     else // param: type_specifier ID LSB RSB
     {
          root = newASTNode(PARAMARRAY_AST);
          root->child[0] = typeSpecifier;
          root->child[1] = newIDNode(ID);
     }
     return root;
}
struct ASTNode* newCompound(struct ASTNode* localDecs, struct ASTNode* stmtList)
{
     struct ASTNode* node = localDecs;
     struct ASTNode* root = newASTNode(COMPOUND_AST);
     root->child[0] = localDecs;
     root->child[1] = stmtList;
}