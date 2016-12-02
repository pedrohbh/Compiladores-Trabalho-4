#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "Arvore.h"

#define MAXCHILDREN 7

extern int yylineno;

struct treeNode
{
	NodeKind kind;
	//struct treeNode *irmaosPtr;
	struct treeNode *filhosPtr[ 7 ];
	int lineno;
};


TreeNode *novoNodo( NodeKind kind )
{
	int i;
	TreeNode *t = (TreeNode *)malloc(sizeof(TreeNode));
	if ( t == NULL )
	{
		fprintf( stderr, "Erro ao alocar novo nodo por falta de memória\n");
	}
	else
	{
		for ( i = 0; i < MAXCHILDREN; i++ )
			t->filhosPtr[ i ] = NULL;
		
		t->kind = kind;
		t->lineno = yylineno;
	}

	return t;
}


/*void adicionaFilhoPrototipo( TreeNode *pai, TreeNode *filho, int posicao )
{
	if ( posicao >= MAXCHILDREN )
	{
		fprintf( stderr, "Estouro do indice máximo de filhos. O valor máximo é %d, enquanto o indice solicitado é %d\n", MAXCHILDREN, posicao );
	}

	pai->filhosPtr[ posicao ] = filho;
}*/

void adicionaFilho( TreeNode *pai, int tamanho, ... )
{
	if ( tamanho >= MAXCHILDREN )
	{
		fprintf( stderr, "Estouro do indice máximo de filhos. O valor máximo é %d, enquanto o indice é %d\n", MAXCHILDREN, tamanho );
	}

	int i;
	va_list ap;

	va_start( ap, tamanho );
	
	for ( i = 0; i < tamanho; i++ )
	{
		pai->filhosPtr[ i ] = va_arg( ap, TreeNode * );
	}

	va_end( ap );

}


// Dot Output
int nr;

void node2str(TreeNode *node, char *s) 
{
    switch(node->kind)
	 {
		case NUMBER_NODE: sprintf(s, "%s", "Numero"); break;
		case PLUS_NODE:   sprintf(s, "%s", "+"); break;
		case MINUS_NODE:  sprintf(s, "%s", "-"); break;
		case TIMES_NODE:  sprintf(s, "%s", "*"); break;
		case OVER_NODE:   sprintf(s, "%s", "/"); break;
		case STRING_NODE: sprintf( s, "%s", "String"); break;
		case BLOCK_NODE: sprintf( s, "%s", "Block"); break;
		case INPUT_NODE: sprintf( s, "%s", "Input"); break;
		case OUTPUT_NODE: sprintf( s, "%s", "Output" ); break;
		case WRITE_NODE: sprintf( s, "%s", "Write" ); break;
		case RETURN_NODE: sprintf( s, "%s", "Return" ); break;
		case IF_NODE: sprintf( s, "%s", "IF NODE"); break;
		case LT_NODE: sprintf( s, "%s", "<" ); break;
		case LE_NODE: sprintf( s, "%s", "<=" ); break;
		case GT_NODE: sprintf( s, "%s", ">" ); break;
		case GE_NODE: sprintf( s, "%s", ">=" ); break;
		case EQ_NODE: sprintf( s, "%s", "==" ); break;
		case NEQ_NODE: sprintf( s, "%s", "!=" ); break;
		case ASSIGN_NODE: sprintf( s, "%s", "=" ); break;
		case VOID_NODE: sprintf( s, "%s", "void" ); break;
		case INTEGER_NODE: sprintf( s, "%s", "int" ); break;
		case BOOL_EXPR_NODE: sprintf( s, "%s", "Bool Expression" ); break;
		case ARG_LIST_NODE: sprintf( s, "%s", "Arg List" ); break;
		case STMT_LIST_NODE: sprintf( s, "%s", "Stmt List" ); break;
		case VAR_DECL_LIST_NODE: sprintf( s, "%s", "Var Decl List" ); break;
		case PARAM_LIST_NODE: sprintf( s, "%s", "Param List" ); break;
		case FUNC_BODY_NODE: sprintf( s, "%s", "Func Body" ); break;
		case FUNC_HEADER_NODE: sprintf( s, "%s", "Func Header" ); break;
		case FUNC_DECL_NODE: sprintf( s, "%s", "Func Decl" ); break;
		case FUNC_DECL_LIST: sprintf( s, "%s", "Func Decl List" ); break;
		default: printf("Invalid node kind: %d!\n", node->kind);
    }
}


int print_node_dot(TreeNode *node) {
	int my_nr = nr++;
	int i;
	char s[ 20 ];
	node2str( node, s );
    printf("node%d[label=\"%s\"];\n", my_nr, s);
    for ( i = 0; i < MAXCHILDREN; i++)
 	{
		if ( node->filhosPtr[ i ] == NULL )
			continue;
        int child_nr = print_node_dot(node->filhosPtr[i]);
        printf("node%d -> node%d;\n", my_nr, child_nr);
    }
    return my_nr;
}

void print_dot(TreeNode *tree) {
    nr = 0;
    printf("digraph {\ngraph [ordering=\"out\"];\n");
    print_node_dot(tree);
    printf("}\n");
}

