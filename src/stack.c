#include "stack.h"

static short* stack;
static const short BOTTOM = -1;
static short pop() {
    short v = *(--stack);
    if (v == BOTTOM) {
        printf("Too many operators/Not enough operands!\n");
        free(stack);
        exit(1);
    }
    else return v;
}

static void push(short v) {
    *(stack++) = v;
}

// Evaluate a single character.
static void evaluate(char c) {
    short v;
    switch(c) {
        case '0':   push(0);
                    printf(" ");
                    break;
        case '1':   push(1);
                    printf(" ");
                    break;
        case '-':   v = !pop();
                    push(v);
                    printf("%hd",v);
                    break;
        case '|':   v = pop()|pop();
                    push(v);
                    printf("%hd", v);
                    break;
        case '&':   v = pop()&pop();
                    push(v);
                    printf("%hd", v);
                    break;
        case '#':   v = pop()^pop();
                    push(v);
                    printf("%hd", v);
                    break;
        case '=':   v = pop() == pop();
                    push(v);
                    printf("%hd", v);
                    break;
        case '>':   v = pop()|(!pop());
                    push(v);
                    printf("%hd", v);
                    break;
        default:    printf("_");  // ignore unrecognised characters
    }
}

// Evaluate a binary expression. NO VARIABLES.
void evaluate_expr(char* expr) {
    int ex_l = strlen(expr);
    stack = malloc(sizeof(short)*(ex_l+1));
    push(BOTTOM);
    for (int i = 0; i < ex_l; i++) evaluate(expr[i]);
    printf(" :   %hd\n", pop());
    
    // Last value should be the BOTTOM.
    if (*(--stack) == BOTTOM) free(stack);
    else {
        printf("Not enough operators/Too many operands!\n");
        while(*(--stack) != BOTTOM);
        free(stack);
        exit(2);
    }
}
