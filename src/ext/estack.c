#include "estack.h"

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
static char evaluate(char c) {
    short v;
    switch(c) {
        case '0':   push(0);
                    return ' ';
        case '1':   push(1);
                    return ' ';
        case '-':   v = !pop();
                    push(v);
                    break;
        case '|':   v = pop()|pop();
                    push(v);
                    break;
        case '&':   v = pop()&pop();
                    push(v);
                    break;
        case '#':   v = pop()^pop();
                    push(v);
                    break;
        case '=':   v = pop() == pop();
                    push(v);
                    break;
        case '>':   v = pop()|(!pop());
                    push(v);
                    break;
        default:    return '_';  // ignore unrecognised characters
    }
    return v+'0';
}

// Evaluate a binary expression. NO VARIABLES.
short evaluate_expr(char* expr, char* output) {
    int ex_l = strlen(expr);
    stack = malloc(sizeof(short)*(ex_l+1));
    push(BOTTOM);
    for (int i = 0; i < ex_l; i++) *(output++) = evaluate(expr[i]);
    short v = pop();
    // add (" :   %hd\n", v) at end of string
    *(output++) = ' ';
    *(output++) = ':';
    *(output++) = ' ';
    *(output++) = ' ';
    *(output++) = ' ';
    *(output++) = v+'0';
    *(output++) = '\n';
    *(output++) = '\0';
    
    // Last value should be the BOTTOM.
    if (*(--stack) == BOTTOM) free(stack);
    else {
        printf("Not enough operators/Too many operands!\n");
        while(*(--stack) != BOTTOM);
        free(stack);
        exit(2);
    }
    
    return v;
}
