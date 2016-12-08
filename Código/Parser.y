
/* Options to bison */
// File name of generated parser.
%output "Parser.c"
// Produces a 'parser.h'
%defines "Parser.h"
// Give proper error messages when a syntax error is found.
%define parse.error verbose
// Enable LAC (lookahead correction) to improve syntax error handling.
%define parse.lac full

// Enable the trace option so that debugging is possible.
%define parse.trace

%code requires{
#include "Arvore.h"
#include "Tabelas.h"
#include "Interpretador.h"
}


%{
#include <stdio.h>
#include <stdlib.h>
#include "Parser.h"

int yylex(void);
void yyerror(char const *s);

LitTable *lt;


TabelaSimbolos *newVar( TabelaSimbolos *tb,  char *nome, int id );
int check_var(TabelaSimbolos *tb, char *nome );

TabelaFuncao *novaFuncao( TabelaFuncao *tb,  char *nome, int id );
int check_funcao( TabelaFuncao *tb, char *nome );

extern int yylineno;

extern char *yytext;

char *tokenSimbolo;
char *stringTemp;
int numeroTemp = 0;
int contadorId = 0;
int contadorFuncaoId = 0;
int idF;
TabelaSimbolos *tabelaSimbolos = NULL;
TabelaFuncao *tabelaFuncao = NULL;
TabelaSimbolos *auxiliarSimbolos;
TabelaSimbolos *auxiliarFuncao = NULL;

TreeNode *arvore;
%}

%define api.value.type {TreeNode*} // Type of variable yylval;

%token IF ELSE INPUT INT OUTPUT RETURN VOID WHILE WRITE
%token PLUS MINUS TIMES OVER
%token LT LE GT GE EQ NEQ
%token ASSIGN SEMI COMMA LPAREN RPAREN LBRACK RBRACK LBRACE RBRACE
%token STRING NUM ID UNKNOWN
%left LT LE GT GE EQ NEQ
%left PLUS MINUS
%left TIMES OVER

%%

program: func_decl_list { arvore = $1; };

func_decl_list: func_decl_list func_decl
					{
						$$ = novoNodo( FUNC_DECL_LIST );
						adicionaFilho( $$, 2, $1, $2 );
					}
					| func_decl
					{
						$$ = $1;
					};

func_decl: func_header func_body
				{
					$$ = novoNodo( FUNC_DECL_NODE );
					adicionaFilho( $$, 2, $1, $2 );
				};

func_header: ret_type ID {
					tabelaFuncao = novaFuncao( tabelaFuncao, tokenSimbolo, contadorFuncaoId ); } LPAREN params RPAREN
				{
					$$ = novoNodo( FUNC_HEADER_NODE );
					adicionaFilho( $$, 2, $1, $5 );
					setData( $$, contadorFuncaoId++ );
				};

func_body: LBRACE opt_var_decl opt_stmt_list RBRACE
				{
					$$ = novoNodo( FUNC_BODY_NODE );
					adicionaFilho( $$, 2, $2, $3 );
				};

opt_var_decl: /* VAZIO */ { $$ = novoNodo( OPT_VAR_DECL ); } | var_decl_list { $$ = $1; };

opt_stmt_list: /* VAZIO */ { $$ = novoNodo( OPT_STMT_LIST ); } | stmt_list { $$ = $1; };

ret_type: INT { $$ = novoNodo( INTEGER_NODE ); } | VOID { $$ = novoNodo( VOID_NODE ); };

params: VOID
			{
				$$ = novoNodo( VOID_NODE );
			}
			| param_list
			{
				$$ = $1;
			};

param_list: param_list COMMA param
				{
					$$ = novoNodo( PARAM_LIST_NODE );
					adicionaFilho( $$, 2, $1, $3 );
				}
				| param
				{
					$$ = $1;
				};

param: INT ID
		{
			$$ = novoNodo( SVAL_NODE );
			tabelaSimbolos = newVar( tabelaSimbolos, tokenSimbolo, contadorId );
			setData( $$, contadorId++ );
			//printf("VAR: %s\n", tokenSimbolo );
			//free( tokenSimbolo );
			//printf("O valor do simbolo é: %s\n", tokenSimbolo );
		}
		| INT ID LBRACK RBRACK
		{
			$$ = novoNodo( CVAL_NODE );
			tabelaSimbolos = newVar( tabelaSimbolos, tokenSimbolo, contadorId++ );
			//free( tokenSimbolo );
		};

var_decl_list: var_decl_list var_decl
					{
						$$ = novoNodo( VAR_DECL_LIST_NODE );
						adicionaFilho( $$, 2, $1, $2 );
					}
					| var_decl
					{
						$$ = $1;
					};

var_decl: INT ID { tabelaSimbolos = newVar( tabelaSimbolos, tokenSimbolo, contadorId ); } SEMI
			{
				$$ = novoNodo( SVAL_NODE );
				setData( $$, contadorId++ );									
			}
			| INT ID { tabelaSimbolos = newVar( tabelaSimbolos, tokenSimbolo, contadorId ); } LBRACK NUM RBRACK SEMI
			{
				$$ = novoNodo( CVAL_NODE );
				setData( $$, contadorId++ );
				adicionaFilho( $$, 1, novoNodo( NUMBER_NODE ) );
				setData( getFilho( $$, 0 ), numeroTemp );
				printf("O valor do número em CVAL é %d\n", numeroTemp );
				
			};

stmt_list: stmt_list stmt
			{
				$$ = novoNodo( STMT_LIST_NODE );
				adicionaFilho( $$, 2, $1, $2 );
			}
			| stmt
			{
				$$ = $1;
			};

stmt: assign_stmt
		{
			$$ = $1;
		}
		| if_stmt
		{
			$$ = $1;
		}
		| while_stmt
		{
			$$ = $1;
		}
		| return_stmt
		{
			$$ = $1;
		}
		| func_call SEMI
		{
			$$ = $1;
		};

assign_stmt: lval ASSIGN arith_expr SEMI
				{
					$$ = novoNodo( ASSIGN_NODE );
					adicionaFilho( $$, 2, $1, $3 );					
				};

lval: ID
		{
			int id = check_var( tabelaSimbolos, tokenSimbolo );
			$$ = novoNodo( SVAL_NODE );
			setData( $$, id );
			//tabelaSimbolos = newVar( tabelaSimbolos, tokenSimbolo );
			//free( tokenSimbolo );
			//$$ = novoNodo( LVAL_NODE ); Pode Dar problema aqui
		}
		| ID LBRACK NUM RBRACK
		{
			int id = check_var( tabelaSimbolos, tokenSimbolo );
			$$ = novoNodo( CVAL_NODE );
			setData( $$, id );
			adicionaFilho( $$, 1, novoNodo( NUMBER_NODE ) );
			printf("Valor do número da varíavel composto é: %d\n", numeroTemp );
			setData( getFilho( $$, 0 ), numeroTemp );
		}
		| ID LBRACK ID RBRACK
		{
			check_var( tabelaSimbolos, tokenSimbolo );
			//free( tokenSimbolo );
		};

if_stmt: IF LPAREN bool_expr RPAREN block
			{
				$$ = novoNodo( IF_NODE );
				adicionaFilho( $$, 2, $3, $5 );
			}
			| IF LPAREN bool_expr RPAREN block ELSE block
			{
				$$ = novoNodo( IF_NODE );
				adicionaFilho( $$, 3, $3, $5, $7 );
			};

block: LBRACE opt_stmt_list RBRACE
		{
			$$ = novoNodo( BLOCK_NODE );
			adicionaFilho( $$, 1, $2 );
		};

while_stmt: WHILE LPAREN bool_expr RPAREN block
				{ 
					$$ = novoNodo( WHILE_NODE );
					adicionaFilho( $$, 2, $3, $5 );
				};

return_stmt: RETURN SEMI
				{
					$$ = novoNodo( RETURN_NODE );
				}
				| RETURN arith_expr SEMI
				{
					$$ = novoNodo( RETURN_NODE );
					adicionaFilho( $$, 1, $2 );
				};

func_call: output_call
				{
					$$ = $1;
				}
				| write_call
				{
					$$ = $1;
				}
				| user_func_call
				{
					$$ = $1;
				};

input_call: INPUT LPAREN RPAREN
				{
					$$ = novoNodo( INPUT_NODE );
				};

output_call: OUTPUT LPAREN arith_expr RPAREN
				{
					$$ = novoNodo( OUTPUT_NODE );
					adicionaFilho( $$, 1, $3 );
				};

write_call: WRITE LPAREN STRING RPAREN
				{ 
					$$ = novoNodo( WRITE_NODE );
					adicionaFilho( $$, 1, novoNodo( STRING_NODE ) );
					setNome( getFilho( $$, 0 ), stringTemp );
					
				};
				

user_func_call: ID { idF = check_funcao( tabelaFuncao, tokenSimbolo ); } LPAREN opt_arg_list RPAREN
					{						
						//$$ = $3;	
						$$ = novoNodo( FUNC_CALL_NODE );
						adicionaFilho( $$, 1, $4 );
						setData( $$, idF );
						//free( tokenSimbolo );
					};

opt_arg_list: /* VAZIO */ | arg_list { $$ = $1; };

arg_list: arg_list COMMA arith_expr 
			{
				$$ = novoNodo( ARG_LIST_NODE );
				adicionaFilho( $$, 2, $1, $3 );
			}
			| arith_expr
			{
				$$ = $1;
			};

bool_expr: arith_expr bool_op arith_expr
				{
					$$ = novoNodo( BOOL_EXPR_NODE );
					adicionaFilho( $$, 3, $1, $2, $3 );
				};

bool_op: LT
			{
				$$ = novoNodo( LT_NODE );
			}
			| LE
			{
				$$ = novoNodo( LE_NODE );
			}
			| GT
			{
				$$ = novoNodo( GT_NODE );
			}
			| GE
			{
				$$ = novoNodo( GE_NODE );
			}
			
			| EQ
			{
				$$ = novoNodo( EQ_NODE );
			}
			| NEQ { $$ = novoNodo( NEQ_NODE ); };

arith_expr: arith_expr PLUS arith_expr
				{
					$$ = novoNodo( PLUS_NODE );
					adicionaFilho( $$, 2, $1, $3 );
				}
 				| arith_expr MINUS arith_expr
				{
					$$ = novoNodo( MINUS_NODE );
					adicionaFilho( $$, 2, $1, $3 );
				}
 				| arith_expr TIMES arith_expr
				{
					$$ = novoNodo( TIMES_NODE );
					adicionaFilho( $$, 2, $1, $3 );
				}
				| arith_expr OVER arith_expr
				{
					$$ = novoNodo( OVER_NODE );
					adicionaFilho( $$, 2, $1, $3 );
				}
				| LPAREN arith_expr RPAREN
				{
					$$ = $2;
				}
				| lval
				{
					$$ = $1;
				}
				| input_call
				{
					$$ = $1;
				}
				
				| user_func_call
				{
					$$ = $1;
				}
				| NUM { $$ = novoNodo( NUMBER_NODE ); printf( "O valor de número é %d\n", numeroTemp ); setData( $$, numeroTemp ); };
							
				

%%

TabelaFuncao *novaFuncao( TabelaFuncao *tb,  char *nome, int id )
{
	//printf("Nome: %s\n", nome );
	int idx = buscaTabelaFuncao( tb, nome );
	
	if ( idx != -1 )
	{
		printf("SEMANTIC ERROR (%d): function ’%s’ already declared at line %d.\n", yylineno, nome, getPrimeiraLinhaFuncao( tb, nome ) );
		exit( 1 );
	}

	tb = insereTabelaFuncao( tb, nome,  yylineno, id );

	return tb;

}

int check_funcao(TabelaFuncao *tb, char *nome ) 
{
    int idx = buscaTabelaFuncao( tb, nome );

    if (idx == -1) {
        printf("SEMANTIC ERROR (%d): function '%s' was not declared.\n", yylineno, nome);
        exit(1);
    }

	TabelaFuncao *it = getNodoFuncao( tb, nome );
	insereNovaLinhaFuncao( it, yylineno );
	return idx;

	
}


TabelaSimbolos *newVar( TabelaSimbolos *tb,  char *nome, int id )
{
	int idx = buscaTabelaSimbolos( tb, nome );
	
	if ( idx != -1 )
	{
		printf("SEMANTIC ERROR (%d): variable ’%s’ already declared at line %d.\n", yylineno, nome, getPrimeiraLinhaSimbolo( tb, nome ) );
		exit( 1 );
	}

	tb = insereTabelaSimbolos( tb, nome,  yylineno, id );

	return tb;

}

int check_var(TabelaSimbolos *tb, char *nome ) 
{
    int idx = buscaTabelaSimbolos( tb, nome );

    if (idx == -1) {
        printf("SEMANTIC ERROR (%d): variable '%s' was not declared.\n", yylineno, nome);
        exit(1);
    }

	TabelaSimbolos *it = getNodo( tb, nome );
	insereNovaLinha( it, yylineno );
	return idx;	
}


void yyerror( char const *s )
{
	printf("PARSE ERROR (%d): %s\n", yylineno, s);
}

int main()
{
	//puts("oi");
	lt = create_lit_table();
	int resultado = yyparse();
	//printf("Resultado: %d\n", resultado);
	if ( resultado == 0 )
	{
		//puts("Opa");
		//stdin = fopen(ctermid(NULL), "r");
      //run_ast(arvore);
		//printf("PARSE SUCESSFUL!\n");
		//imprimeTabelaSimbolos( tabelaSimbolos );
		print_dot( arvore );
	}

	return 0;
}

