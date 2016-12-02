#ifndef TABELAS_H
#define TABELAS_H

typedef struct linhaLista LinhaLista;

typedef struct tabelaFuncao TabelaFuncao;

typedef struct tabelaSimbolos TabelaSimbolos;

//-------------------------------------Literais-----------------------------------------------
typedef struct lit_table LitTable;

LitTable* create_lit_table();

int add_literal(LitTable* lt, char* s);


char* get_literal(LitTable* lt, int i);

void print_lit_table(LitTable* lt);

void free_lit_table(LitTable* lt);


//--------------------------------------Funcao------------------------------------------------

int buscaTabelaFuncao( TabelaFuncao *tb, char *nome );

TabelaFuncao *getNodoFuncao( TabelaFuncao *tb, char *nome );

int getPrimeiraLinhaFuncao( TabelaFuncao *tb, char *nome );

void insereNovaLinhaFuncao( TabelaFuncao *nodo, int linha );

TabelaFuncao *insereTabelaFuncao( TabelaFuncao *tb, char *nome, int linha );

//--------------------------------------Simbolos---------------------------------------------
int buscaTabelaSimbolos( TabelaSimbolos *tb, char *nome );

void insereNovaLinha( TabelaSimbolos *nodo, int linha );

int getPrimeiraLinhaSimbolo( TabelaSimbolos *tb, char *nome );

TabelaSimbolos *insereTabelaSimbolos( TabelaSimbolos *tb, char *nome, int linha );

TabelaSimbolos *getNodo( TabelaSimbolos *tb, char *nome );

char *copiaString( char *string );

void imprimeTabelaSimbolos( TabelaSimbolos *tb );

#endif

