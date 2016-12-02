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


void run_ast(AST *ast) {
    init_stack();
    init_mem();
    rec_run_ast(ast);
}

void rec_run_ast(AST *ast) {
    switch(get_kind(ast)) {
        case FUNC_DECL_LIST:
            //run_stmt_seq(ast);
            break;
        case FUNC_DECL_NODE:
            //run_if(ast);
            break;
        case FUNC_HEADER_NODE:
            //run_repeat(ast);
            break;
        case PARAM_LIST_NODE:
            //run_assign(ast);
            break;
        case VAR_DECL_LIST_NODE:
            //run_read(ast);
            break;
        case BLOCK_NODE:
            //run_write(ast);
            break;
        case INPUT_NODE:
            //run_plus(ast);
            break;
        case OUTPUT_NODE:
            //run_minus(ast);
            break;
        case WRITE_NODE:
            //run_times(ast);
            break;
        case ASSIGN_NODE:
            //run_over(ast);
            break;
        case NUMBER_NODE:
            //run_lt(ast);
            break;
        case INTEGER_NODE:  // INTEGER_NODE CORRESPONDE AO SVAR DA ESPECIFICAÇÃO. NÃO ESQUECER
            //run_eq(ast);
            break;
			case INTEGER_VECTOR_NODE: // INTEGER_VECTOR_NODE CORRESPONDE AO CVAR DA ESPECIFICAÇÃO. NÃO ESQUECER
            //run_num(ast);
            break;
        case PLUS_NODE:
            //run_id(ast);
            break;
			case MINUS_NODE:
				break;
			case TIMES_NODE:
				break;
			case OVER_NODE:
				break;
			case LT_NODE:
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
        default:
            fprintf(stderr, "Invalid kind: %s!\n", kind2str(get_kind(ast)));
            exit(1);
    }
}

void run_stmt_seq(AST *ast) {
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
}

