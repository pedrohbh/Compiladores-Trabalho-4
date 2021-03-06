#ifndef ARVORE_H
#define ARVORE_H

struct treeNode;

typedef struct treeNode TreeNode;

typedef enum
{
	NUMBER_NODE,
	STRING_NODE,
	BLOCK_NODE,
	INPUT_NODE,
	OUTPUT_NODE,
	WRITE_NODE,
	WHILE_NODE,
	RETURN_NODE,
	ASSIGN_NODE,
	IF_NODE,
	LT_NODE,
	LE_NODE,
	GT_NODE,
	GE_NODE,
	EQ_NODE,
	NEQ_NODE,
	PLUS_NODE,
	MINUS_NODE,
	TIMES_NODE,
	OVER_NODE,
	VOID_NODE,
	INTEGER_NODE,
	INTEGER_VECTOR_NODE,
	SVAL_NODE,
	CVAL_NODE,
	BOOL_EXPR_NODE,
	ARG_LIST_NODE,
	STMT_LIST_NODE,
	VAR_DECL_LIST_NODE,
	PARAM_LIST_NODE,
	FUNC_BODY_NODE,
	FUNC_HEADER_NODE,
	FUNC_DECL_NODE,
	FUNC_DECL_LIST,
	FUNC_CALL_NODE,
	OPT_STMT_LIST,
	OPT_VAR_DECL,
	OPT_ARG_LIST
} NodeKind;

TreeNode *novoNodo( NodeKind kind );

NodeKind getKind( TreeNode *ast );

void setNome( TreeNode *ast, char *nome );

char *getNome( TreeNode *ast );

int getData( TreeNode *ast );

void setData( TreeNode *ast, int valor );

//void adicionaFilhoPrototipo( TreeNode *pai, TreeNode *filho, int posicao );

void adicionaFilho( TreeNode *pai, int tamanho, ... );

void node2str(TreeNode *node, char *s);

int print_node_dot(TreeNode *node);

void print_dot(TreeNode *tree);

TreeNode *getFilho( TreeNode *pai, int nFilho );

#endif

