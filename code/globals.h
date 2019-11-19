#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

typedef enum { StmtK, ExpK } NodeKind;
typedef enum { CompStmtK, SelStmtK, IterStmtK, RetStmtK, CallK } StmtKind;
typedef enum { VarDeclK, VarArrayDeclK, FuncDeclK, AssignK, OpK, IdK, ConstK } ExpKind;

typedef enum { Void, Integer } ExpType;

#define MAXCHILDREN 3

struct scopeListRec;

typedef struct treeNode
{
	struct treeNode * child[MAXCHILDREN];
	struct treeNode * sibling;
	int lineno;
	NodeKind nodekind;
	union { StmtKind stmt; ExpKind exp; } kind;
	union {
		TokenType op;
		int val;
		char * name;
		struct ScopeListRec *scope;
	} attr;
	ExpType type;
	int isParam;
	int arraysize;
} TreeNode;

TreeNode * parse(void);

void printToken( TokenType, const char* );

#endif