#include "globals.h"

static TokenType token;

static TreeNode * decl_list(void);
static TreeNode * decl(void);
static TreeNode * var_decl(void);
static ExpType type_spec(void);
static TreeNode * params(void);
static TreeNode * param_list(ExpType type);
static TreeNode * param(ExpType type);
static TreeNode * comp_stmt(void);
static TreeNode * local_decl(void);
static TreeNode * stmt_list(void);
static TreeNode * stmt(void);
static TreeNode * expr_stmt(void);
static TreeNode * sel_stmt(void);
static TreeNode * iter_stmt(void);
static TreeNode * ret_stmt(void);
static TreeNode * expr(void);
static TreeNode * simp_expr(TreeNode *f);
static TreeNode * add_expr(TreeNode *f);
static TreeNode * term(TreeNode *f);
static TreeNode * factor(TreeNode *f);
static TreeNode * call(void);
static TreeNode * args(void);
static TreeNode * args_list(void);

static void printToken(TokenType token, const char* tokenString)
{
	switch (token)
	{
	case IF:
	case WHILE:
	case RETURN:
	case INT:
	case VOID:
	case ELSE:

		fprintf(listing, "reserved word: %s\n", tokenString);
		break;

	case Op_assign: fprintf(listing, "=\n"); break;
	case Op_equal: fprintf(listing, "==\n"); break;
	case Op_notequal: fprintf(listing, "!=\n"); break;
	case Op_less: fprintf(listing, "<\n"); break;
	case Op_lessequal: fprintf(listing, "<=\n"); break;
	case Op_greater: fprintf(listing, ">\n"); break;
	case Op_greaterequal: fprintf(listing, ">=\n"); break;
	case LeftPrnts: fprintf(listing, "(\n"); break;
	case RightPrnts: fprintf(listing, ")\n"); break;
	case LeftBrack: fprintf(listing, "[\n"); break;
	case RightBrack: fprintf(listing, "]\n"); break;
	case LeftBrace: fprintf(listing, "{\n"); break;
	case RightBrace: fprintf(listing, "}\n"); break;
	case Semicolon: fprintf(listing, ";\n"); break;
	case Comma: fprintf(listing, ",\n"); break;
	case Op_add: fprintf(listing, "+\n"); break;
	case Op_subtract: fprintf(listing, "-\n"); break;
	case Op_multiply: fprintf(listing, "*\n"); break;
	case Op_divide: fprintf(listing, "/\n"); break;
	case Op_mod: fprintf(listing, "%\n"); break;
	case Eps: fprintf(listing, "Eps\n"); break;
	case NUM:
		fprintf(listing, "NUM, val= %s\n", tokenString);
		break;
	case ID:
		fprintf(listing, "ID, name= %s\n", tokenString);
		break;
	default: 
		fprintf(listing, "Unknown token: %d\n", token);
	}
}

static void syntaxError(char * message)
{ fprintf(listing,"\n>>> ");
  fprintf(listing,"Syntax error at line %d: %s",lineno,message);
  Error = TRUE;
}

static void match(TokenType expected)
{ if (token == expected) token = getToken();
  else {
    syntaxError("unexpected token (match) -> ");
    printToken(token,tokenString);
    fprintf(listing,"      ");
  }
}

TreeNode * decl_list(void)
{ TreeNode * t = decl();
  TreeNode * p = t;
  while (token!=ENDFILE)
  { TreeNode * q;
    q = decl();
    if (q!=NULL) {
      if (t==NULL) t = p = q;
      else 
      { p->sibling = q;
        p = q;
      }
    }
  }
  return t;
}

TreeNode * decl(void)
{
	TreeNode *t;
	ExpType type;
	char *name;

	type = type_spec();
	name = copyString(tokenString);
	match(ID);

	switch (token)
	{
	case SEMI:
		t = newExpNode(VarDeclK);
		if (t != NULL)
		{
			t->attr.name = name;
			t->type = type;
		}
		match(SEMI);
		break;
	case LBRACE:
		t = newExpNode(VarArrayDeclK);
		if (t != NULL)
		{
			t->attr.name = name;
			t->type = type;
		}
		match(LBRACE);
		if (t != NULL)
			t->arraysize = atoi(tokenString);
		match(NUM);
		match(RBRACE);
		match(SEMI);
		break;
	case LPAREN:
		t = newExpNode(FuncDeclK);
		if (t != NULL)
		{
			t->attr.name = name;
			t->type = type;
		}
		match(LPAREN);
		if (t != NULL)
			t->child[0] = params();
		match(RPAREN);
		if (t != NULL)
			t->child[1] = comp_stmt();
		break;
	default: syntaxError("unexpected token (decl) -> ");
		printToken(token, tokenString);
		token = getToken();
		break;
	}
	return t;
}

TreeNode * var_decl(void)
{
	TreeNode *t;
	ExpType type;
	char *name;
	
	type = type_spec();
	name = copyString(tokenString);
	match(ID);
	switch (token)
	{
	case SEMI:
		t = newExpNode(VarDeclK);
		if (t != NULL)
		{
			t->attr.name = name;
			t->type = type;
		}
		match(SEMI);
		break;
	case LBRACE:
		t = newExpNode(VarArrayDeclK);
		if (t != NULL)
		{
			t->attr.name = name;
			t->type = type;
		}
		match(LBRACE);
		if (t != NULL)
			t->arraysize = atoi(tokenString);
		match(NUM);
		match(RBRACE);
		match(SEMI);
		break;
	default: syntaxError("unexpected token(var_decl) -> ");
		printToken(token, tokenString);
		token = getToken();
		break;
	}
	return t;
}

ExpType type_spec(void)
{
	switch (token)
	{
	case INT:
		token = getToken();
		return Integer;
	case VOID:
		token = getToken();
		return Void;
	default: syntaxError("unexpected token(type_spec) -> ");
		printToken(token, tokenString);
		token = getToken();
		return Void;
	}
}

TreeNode * params(void)
{
	ExpType type;
	TreeNode *t;

	type = type_spec();
	if (type == Void && token == RPAREN)
	{
		t = newExpNode(VarDeclK);
		t->isParam = TRUE;
		t->type = Void;
	}
	else
		t = param_list(type);
	return t;
}
