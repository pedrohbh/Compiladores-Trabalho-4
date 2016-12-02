#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Tabelas.h"

#define SYMBOL_MAX_SIZE 128

struct linhaLista
{
	int linha;
	struct linhaLista *proximoPtr;
};

//--------------------------------------Tabela de Literais

#define LITERAL_MAX_SIZE 128
#define LITERALS_TABLE_MAX_SIZE 100

struct lit_table {
    char t[LITERALS_TABLE_MAX_SIZE][LITERAL_MAX_SIZE];
    int size;
};

LitTable* create_lit_table() {
    LitTable *lt = malloc(sizeof * lt);
    lt->size = 0;
    return lt;
}

int add_literal(LitTable* lt, char* s) {
    for (int i = 0; i < lt->size; i++) {
        if (strcmp(lt->t[i], s) == 0) {
            return i;
        }
    }
    strcpy(lt->t[lt->size], s);
    int old_side = lt->size;
    lt->size++;
    return old_side;
}

char* get_literal(LitTable* lt, int i) {
    return lt->t[i];
}

void print_lit_table(LitTable* lt) {
    printf("Literals table:\n");
    for (int i = 0; i < lt->size; i++) {
        printf("Entry %d -- %s\n", i, get_literal(lt, i));
    }
}

void free_lit_table(LitTable* lt) {
    free(lt);
}


//--------------------------------------Funcao
struct tabelaFuncao
{
	char *nome;
	LinhaLista *linhas;
	struct tabelaFuncao *proximoPtr;
};

int buscaTabelaFuncao( TabelaFuncao *tb, char *nome )
{
	TabelaFuncao *it;
	int i = 0;
	for ( it = tb; it != NULL; it = it->proximoPtr )
	{
		if ( strcmp( nome, it->nome ) == 0 )
			return i;

		i++;
	}

	return -1;
}

TabelaFuncao *getNodoFuncao( TabelaFuncao *tb, char *nome )
{
	TabelaFuncao *it;
	for ( it = tb; it != NULL; it = it->proximoPtr )
	{
		if ( strcmp( nome, it->nome ) == 0 )
			return it;
	}

	return NULL;
}

int getPrimeiraLinhaFuncao( TabelaFuncao *tb, char *nome )
{
	TabelaFuncao *it;
	for ( it = tb; it != NULL; it = it->proximoPtr )
	{
		if ( strcmp( nome, it->nome ) == 0 )
			return it->linhas->linha;
	}
	return -1;
}

void insereNovaLinhaFuncao( TabelaFuncao *nodo, int linha )
{
	if ( nodo->linhas == NULL )
	{
		nodo->linhas = (LinhaLista *)malloc( sizeof( LinhaLista ) );
		if ( nodo->linhas == NULL )
		{
			fprintf( stderr, "Falta de memória ao alocar linha do elemento da tabela de simbolos \"%s\". Linha: %d.\n", nodo->nome, linha );
			exit( 1 );
		}

		nodo->linhas->linha = linha;
		nodo->linhas->proximoPtr = NULL;
	}
	else
	{
		LinhaLista *it = nodo->linhas;
		while ( it->proximoPtr != NULL )
			it = it->proximoPtr;
		
		it->proximoPtr = (LinhaLista *)malloc( sizeof( LinhaLista ) );
		if ( it->proximoPtr == NULL )
		{
			fprintf( stderr, "Falta de memória ao alocar linha do elemento da tabela de simbolos \"%s\". Linha: %d.\n", nodo->nome, linha );
			exit( 1 );
		}
		it->proximoPtr->linha = linha;
		it->proximoPtr->proximoPtr = NULL;
	}
}		
			

TabelaFuncao *insereTabelaFuncao( TabelaFuncao *tb, char *nome, int linha )
{
	TabelaFuncao *novoElemento = (TabelaFuncao *)malloc( sizeof(TabelaFuncao) );
	
	if ( novoElemento == NULL )
	{
		fprintf( stderr, "Falta de memória ao alocar o elemento da tabela de simbolos \"%s\".\n", nome );
		exit( 1 );
	}

	novoElemento->nome = copiaString( nome );
	//printf("Nome %s\n", novoElemento->nome );
	novoElemento->linhas = NULL;
	novoElemento->proximoPtr = NULL;
	insereNovaLinhaFuncao( novoElemento, linha );


	if ( tb == NULL )
	{
		tb = novoElemento;
	}
	else
	{
		novoElemento->proximoPtr = tb;
		tb = novoElemento;
	}

	if ( tb == NULL )
		printf("Não era pra ta NULOOOOO\n");

	return tb;
}


//--------------------------------------Simbolos


struct tabelaSimbolos
{
	char *nome;
	//int tamanho;
	LinhaLista *linhas;
	struct tabelaSimbolos *proximoPtr;
};


int buscaTabelaSimbolos( TabelaSimbolos *tb, char *nome )
{
	TabelaSimbolos *it;
	int i = 0;
	for ( it = tb; it != NULL; it = it->proximoPtr )
	{
		if ( strcmp( nome, it->nome ) == 0 )
			return i;

		i++;
	}

	return -1;
}

TabelaSimbolos *getNodo( TabelaSimbolos *tb, char *nome )
{
	TabelaSimbolos *it;
	for ( it = tb; it != NULL; it = it->proximoPtr )
	{
		if ( strcmp( nome, it->nome ) == 0 )
			return it;
	}

	return NULL;
}

int getPrimeiraLinhaSimbolo( TabelaSimbolos *tb, char *nome )
{
	TabelaSimbolos *it;
	for ( it = tb; it != NULL; it = it->proximoPtr )
	{
		if ( strcmp( nome, it->nome ) == 0 )
			return it->linhas->linha;
	}
	return -1;
}

void insereNovaLinha( TabelaSimbolos *nodo, int linha )
{
	if ( nodo->linhas == NULL )
	{
		nodo->linhas = (LinhaLista *)malloc( sizeof( LinhaLista ) );
		if ( nodo->linhas == NULL )
		{
			fprintf( stderr, "Falta de memória ao alocar linha do elemento da tabela de simbolos \"%s\". Linha: %d.\n", nodo->nome, linha );
			exit( 1 );
		}

		nodo->linhas->linha = linha;
		nodo->linhas->proximoPtr = NULL;
	}
	else
	{
		LinhaLista *it = nodo->linhas;
		while ( it->proximoPtr != NULL )
			it = it->proximoPtr;
		
		it->proximoPtr = (LinhaLista *)malloc( sizeof( LinhaLista ) );
		if ( it->proximoPtr == NULL )
		{
			fprintf( stderr, "Falta de memória ao alocar linha do elemento da tabela de simbolos \"%s\". Linha: %d.\n", nodo->nome, linha );
			exit( 1 );
		}
		it->proximoPtr->linha = linha;
		it->proximoPtr->proximoPtr = NULL;
	}
}		
			

TabelaSimbolos *insereTabelaSimbolos( TabelaSimbolos *tb, char *nome, int linha )
{
	TabelaSimbolos *novoElemento = (TabelaSimbolos *)malloc( sizeof(TabelaSimbolos) );
	
	if ( novoElemento == NULL )
	{
		fprintf( stderr, "Falta de memória ao alocar o elemento da tabela de simbolos \"%s\".\n", nome );
		exit( 1 );
	}

	novoElemento->nome = copiaString( nome );
	//printf("Nome %s\n", novoElemento->nome );
	novoElemento->linhas = NULL;
	novoElemento->proximoPtr = NULL;
	insereNovaLinha( novoElemento, linha );


	if ( tb == NULL )
	{
		tb = novoElemento;
	}
	else
	{
		novoElemento->proximoPtr = tb;
		tb = novoElemento;
	}

	if ( tb == NULL )
		printf("Não era pra ta NULOOOOO\n");

	return tb;
}

char *copiaString( char *string )
{
	int n;
	char *t;
	if ( string == NULL )
		return NULL;
	n = strlen( string ) + 1;
	t = (char *)malloc( sizeof( char ) * n );
	if ( t == NULL )
	{
		fprintf( stderr, "Falta de memória ao alocar a string \"%s\".\n", string );
		exit( 1 );
	}
	else
		strcpy( t, string );
	
	return t;
}


void imprimeTabelaSimbolos( TabelaSimbolos *tb )
{
	TabelaSimbolos *it;
	int i = 0;
	for ( it = tb; it != NULL; it = it->proximoPtr )
		i++;
	printf("i = %d\n", i );
	for ( it = tb; it != NULL; it = it->proximoPtr )
	{
		printf("Simbolo: %s -------------------- ", it->nome );
		/*for ( ll = it->linhas; ll != NULL; ll = ll->proximoPtr );
			printf("%d ", ll->linha );*/
		printf("\n\n");
	}
}
