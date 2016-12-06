#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Interpretador.h"

// Data stack -----------------------------------------------------------------

#define STACK_SIZE 100

int stack[STACK_SIZE];
int sp; // stack pointer

void push(int x) {
    stack[++sp] = x;
}

int pop() {
    return stack[sp--];
}

void init_stack() {
    for (int i = 0; i < STACK_SIZE; i++) {
        stack[i] = 0;
    }
    sp = -1;
}

void print_stack() {
    printf("*** STACK: ");
    for (int i = 0; i <= sp; i++) {
        printf("%d ", stack[i]);
    }
    printf("\n");
}

// ----------------------------------------------------------------------------

// Variables memory -----------------------------------------------------------

#define MEM_SIZE 100

int mem[MEM_SIZE];

void store(int addr, int val) {
    mem[addr] = val;
}

int load(int addr) {
    return mem[addr];
}

void init_mem() {
    for (int addr = 0; addr < MEM_SIZE; addr++) {
        mem[addr] = 0;
    }
}

// ----------------------------------------------------------------------------
void rec_run_ast(TreeNode *ast);
void run_func_decl_list( TreeNode *ast );

void run_ast(TreeNode *ast) {
    init_stack();
    init_mem();
    rec_run_ast(ast);
}


void trace( char *s )
{
	printf("Trace: %s\n", s );
}

/*void run_func_decl_list( TreeNode *ast )
{
	int i;
	TreeNode *filho;
	trace("func_decl_list");
	for ( i = 0; i < 7; i++ )
	{
		filho = getFilho( ast, i );
		if ( filho == NULL )
			continue;
		else
			rec_run_ast( filho );
	}
}


void run_func_decl_list( TreeNode *ast )
{
	int i;
	TreeNode *filho;
	trace("func_decl_list");
	for ( i = 0; i < 7; i++ )
	{
		filho = getFilho( ast, i );
		if ( filho == NULL )
			continue;
		else
			rec_run_ast( filho );
	}
}*/

void run_func_decl_node( TreeNode *ast )
{
	int i;
	TreeNode *filho;
	trace("func_decl_node");
	for ( i = 0; i < 7; i++ )
	{
		filho = getFilho( ast, i );
		if ( filho == NULL )
			continue;
		else
			rec_run_ast( filho );
	}
}

void run_func_header_node( TreeNode *ast )
{
	int i;
	TreeNode *filho;
	trace("func_header_node");
	for ( i = 0; i < 7; i++ )
	{
		filho = getFilho( ast, i );
		if ( filho == NULL )
			continue;
		else
			rec_run_ast( filho );
	}
}

void run_func_body_node( TreeNode *ast )
{
	int i;
	TreeNode *filho;
	trace("func_body_node");
	for ( i = 0; i < 7; i++ )
	{
		filho = getFilho( ast, i );
		if ( filho == NULL )
			continue;
		else
			rec_run_ast( filho );
	}
}

/*void run_stmt_seq(AST *ast) {
    trace("stmt_seq");
    int size = get_child_count(ast);
    for (int i = 0; i < size; i++) {
        rec_run_ast(get_child(ast, i));
    }
}

void run_if(AST *ast) {
    trace("if");
    rec_run_ast(get_child(ast, 0));
    int test = pop();
    if (test == 1) {
        rec_run_ast(get_child(ast, 1));
    } else if (test == 0 && get_child_count(ast) == 3) {
        rec_run_ast(get_child(ast, 2));
    }
}

void run_repeat(AST *ast) {
    trace("repeat");
    int again = 1;
    while (again) {
        rec_run_ast(get_child(ast, 0)); // Run body.
        rec_run_ast(get_child(ast, 1)); // Run test.
        again = !pop();
    }
}

void run_assign(AST *ast) {
    trace("assign");
    rec_run_ast(get_child(ast, 1));
    AST *child = get_child(ast, 0);
    int var_idx = get_data(child);
    store(var_idx, pop());
}

void run_read(AST *ast) {
    trace("read");
    int x;
    printf("read: ");
    scanf("%d", &x);
    AST *child = get_child(ast, 0);
    int var_idx = get_data(child);
    store(var_idx, x);
}

void run_write(AST *ast) {
    trace("write");
    rec_run_ast(get_child(ast, 0));
    int x = pop();
    printf("write: %d\n", x);
}

#define bin_op() \
    rec_run_ast(get_child(ast, 0)); \
    rec_run_ast(get_child(ast, 1)); \
    int r = pop(); \
    int l = pop()

void run_plus(AST *ast) {
    trace("plus");
    bin_op();
    push(l + r);
}

void run_minus(AST *ast) {
    trace("minus");
    bin_op();
    push(l - r);
}

void run_times(AST *ast) {
    trace("times");
    bin_op();
    push(l * r);
}

void run_over(AST *ast) {
    trace("over");
    bin_op();
    push((int) l / r);
}

void run_lt(AST *ast) {
    trace("lt");
    bin_op();
    push(l < r);
}

void run_eq(AST *ast) {
    trace("eq");
    bin_op();
    push(l == r);
}

void run_num(AST *ast) {
    trace("num");
    push(get_data(ast));
}

void run_id(AST *ast) {
    trace("id");
    int var_idx = get_data(ast);
    push(load(var_idx));
}*/

void run_sval_node( TreeNode *ast )
{
	push( load( getData( ast ) ) );
	printf("sval_node: ID = %d valor =  %d\n", getData( ast ), load( getData( ast ) ) );
}

void run_assign_node( TreeNode *ast )
{
	//int i;
	TreeNode *filho;
	trace("assign_node");
	filho = getFilho( ast, 1 );
	if ( filho == NULL )
	{
		puts("Erro em ASSIGN NODE. Filho 1");
		exit( 0 );
	}
	rec_run_ast( filho );
	
	filho = getFilho( ast, 0 );
	if ( filho == NULL )
	{
		puts("Erro em ASSIGN NODE. Filho 2");
		exit( 0 );
	}
	
	store( getData( filho ), pop() );
	//rec_run_ast( filho );
}

void run_stmt_list_node( TreeNode *ast )
{
	int i;
	TreeNode *filho;
	trace("stmt_list_node");
	for ( i = 0; i < 7; i++ )
	{
		filho = getFilho( ast, i );
		if ( filho == NULL )
			continue;
		else
			rec_run_ast( filho );
	}	
}

void run_number_node( TreeNode *ast )
{
	printf("Number: %d\n", getData( ast ) );
	push( getData( ast ) );
}

void run_output_node( TreeNode *ast )
{
	trace("Output node");
	int i;
	TreeNode *filho;
	for ( i = 0; i < 7; i++ )
	{
		filho = getFilho( ast, i );
		if ( filho == NULL )
			continue;
		else
			rec_run_ast( filho );
	}
	int d = pop();
	printf( "%d\n", d );
	//printf("%d\n", load( getData( getFilho( ast, 0 ) ) ) );	DESCOMENTE AQUI EM CASO DE EMERGÊNCIA
}

void run_input_node( TreeNode *ast )
{
	trace("Input Node");
	int d;
	printf("input: ");
	scanf( "%d", &d );
	push( d );
}

void run_plus_node( TreeNode *ast )
{
	trace("Plus node");
	int i;
	TreeNode *filho;
	for ( i = 0; i < 7; i++ )
	{
		filho = getFilho( ast, i );
		if ( filho == NULL )
			continue;
		else
			rec_run_ast( filho );
	}
	int a = pop();
	int b = pop();
	printf("SOMA: Valor de a: %d. Valor de b: %d\n", a, b );
	int c = a + b;
	push( c );
}

void run_over_node( TreeNode *ast )
{
	trace("Over node");
	int i;
	TreeNode *filho;
	for ( i = 0; i < 7; i++ )
	{
		filho = getFilho( ast, i );
		if ( filho == NULL )
			continue;
		else
			rec_run_ast( filho );
	}
	int a = pop();
	int b = pop();
	printf("Divisão: Valor de a: %d. Valor de b: %d\n", a, b );
	int c = b / a;
	push( c );
}

void run_times_node( TreeNode *ast )
{
	trace("Times node");
	int i;
	TreeNode *filho;
	for ( i = 0; i < 7; i++ )
	{
		filho = getFilho( ast, i );
		if ( filho == NULL )
			continue;
		else
			rec_run_ast( filho );
	}
	int a = pop();
	int b = pop();
	printf("Multiplicação: Valor de a: %d. Valor de b: %d\n", a, b );
	int c = b * a;
	push( c );
}

void run_minus_node( TreeNode *ast )
{
	trace("Minus node");
	int i;
	TreeNode *filho;
	for ( i = 0; i < 7; i++ )
	{
		filho = getFilho( ast, i );
		if ( filho == NULL )
			continue;
		else
			rec_run_ast( filho );
	}
	int a = pop();
	int b = pop();
	printf("Subtração: Valor de a: %d. Valor de b: %d\n", a, b );
	int c = b - a;
	push( c );
}

void run_lt_node( TreeNode *ast )
{
	trace("lt node");
	int i;
	TreeNode *filho;
	for ( i = 0; i < 7; i++ )
	{
		filho = getFilho( ast, i );
		if ( filho == NULL )
			continue;
		else
			rec_run_ast( filho );
	}
	int a = pop();
	int b = pop();
	printf("LESS THEN: Valor de a: %d. Valor de b: %d\n", a , b );
	if ( b < a )
		push( 1 );
	else
		push( 0 );
}

void run_le_node( TreeNode *ast )
{
	trace("le node");
	int i;
	TreeNode *filho;
	for ( i = 0; i < 7; i++ )
	{
		filho = getFilho( ast, i );
		if ( filho == NULL )
			continue;
		else
			rec_run_ast( filho );
	}
	int a = pop();
	int b = pop();
	printf("LESS EQUAL: Valor de a: %d. Valor de b: %d\n", a , b );
	if ( b <= a )
		push( 1 );
	else
		push( 0 );
}

void run_gt_node( TreeNode *ast )
{
	trace("gt node");
	int i;
	TreeNode *filho;
	for ( i = 0; i < 7; i++ )
	{
		filho = getFilho( ast, i );
		if ( filho == NULL )
			continue;
		else
			rec_run_ast( filho );
	}
	int a = pop();
	int b = pop();
	printf("GREATER THEN: Valor de a: %d. Valor de b: %d\n", a , b );
	if ( b > a )
		push( 1 );
	else
		push( 0 );
}

void run_ge_node( TreeNode *ast )
{
	trace("ge node");
	int i;
	TreeNode *filho;
	for ( i = 0; i < 7; i++ )
	{
		filho = getFilho( ast, i );
		if ( filho == NULL )
			continue;
		else
			rec_run_ast( filho );
	}
	int a = pop();
	int b = pop();
	printf("LESS THEN: Valor de a: %d. Valor de b: %d\n", a , b );
	if ( b >= a )
		push( 1 );
	else
		push( 0 );
}

void run_eq_node( TreeNode *ast )
{
	trace("eq node");
	int i;
	TreeNode *filho;
	for ( i = 0; i < 7; i++ )
	{
		filho = getFilho( ast, i );
		if ( filho == NULL )
			continue;
		else
			rec_run_ast( filho );
	}
	int a = pop();
	int b = pop();
	printf("EQUAL: Valor de a: %d. Valor de b: %d\n", a , b );
	if ( b == a )
		push( 1 );
	else
		push( 0 );
}

void run_neq_node( TreeNode *ast )
{
	trace("neq node");
	int i;
	TreeNode *filho;
	for ( i = 0; i < 7; i++ )
	{
		filho = getFilho( ast, i );
		if ( filho == NULL )
			continue;
		else
			rec_run_ast( filho );
	}
	int a = pop();
	int b = pop();
	printf("NOT EQUAL: Valor de a: %d. Valor de b: %d\n", a , b );
	if ( b != a )
		push( 1 );
	else
		push( 0 );
}
	



void run_write_node( TreeNode *ast )
{
	trace("write node");
	char *string;
	TreeNode *filho = getFilho( ast, 0 );
	if ( filho == NULL )
		puts("Filho errou");
	string = getNome( filho );
	if ( string == NULL )
		puts("Errou a string");
	
	//printf("String: %s\n", string );
	char *achador = strpbrk( string, "\\n" );
	
	if ( achador != NULL )
	{
		if ( strcmp( string, "\\n" ) == 0 )
			printf("\n");
		else
		{
			string = strtok( string, "\\n" );
			printf("%s\n", string );
		}
	}
	else
		printf("%s", string );
}

void rec_run_ast(TreeNode *ast) {
    switch( getKind(ast) ) 
	{
			case SVAL_NODE:
				run_sval_node( ast );
				break;
        case FUNC_DECL_LIST:
            break;
        case FUNC_DECL_NODE:
            run_func_decl_node( ast );
            break;
        case FUNC_HEADER_NODE:
            run_func_header_node( ast );
            break;
        case PARAM_LIST_NODE:
            break;
        case VAR_DECL_LIST_NODE:
            break;
			case FUNC_BODY_NODE:
				run_func_body_node( ast );
				break;
        case BLOCK_NODE:
            break;
        case INPUT_NODE:
				run_input_node( ast );
            break;
        case OUTPUT_NODE:
				run_output_node( ast );
            break;
        case WRITE_NODE:
				run_write_node( ast );
            break;
        case ASSIGN_NODE:
				run_assign_node( ast );
            break;
        case NUMBER_NODE:
            run_number_node( ast );
            break;
        case INTEGER_NODE:  // INTEGER_NODE CORRESPONDE AO SVAR DA ESPECIFICAÇÃO. NÃO ESQUECER
            //run_eq(ast);
            break;
			case INTEGER_VECTOR_NODE: // INTEGER_VECTOR_NODE CORRESPONDE AO CVAR DA ESPECIFICAÇÃO. NÃO ESQUECER
            //run_num(ast);
            break;
        case PLUS_NODE:
            run_plus_node( ast );
            break;
			case MINUS_NODE:
				run_minus_node( ast );
				break;
			case TIMES_NODE:
				run_times_node( ast );
				break;
			case OVER_NODE:
				run_over_node( ast );
				break;
			case LT_NODE:
				run_lt_node( ast );
				break;
			case LE_NODE:
				break;
			case GT_NODE:
				break;
			case GE_NODE:
				break;
			case EQ_NODE:
				break;
			case NEQ_NODE:
				break;
			case IF_NODE:
				break;
			case WHILE_NODE:
				break;
			case FUNC_CALL_NODE:
				break;
			case ARG_LIST_NODE:
				break;
			case VOID_NODE:
				break;
			case STRING_NODE:
				break;
			case RETURN_NODE:
				break;
			case BOOL_EXPR_NODE:
				break;
			case STMT_LIST_NODE:
				run_stmt_list_node( ast );
				break;
			case OPT_STMT_LIST:
				break;
			case OPT_VAR_DECL:
				break;
        //default:
            //fprintf(stderr, "Invalid kind: %s!\n", kind2str(get_kind(ast)));
            //exit(1);
    }
}

