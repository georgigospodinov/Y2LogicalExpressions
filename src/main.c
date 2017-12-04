#include "stack.h"

#define MAX_AMOUNT 26
static char assigned_values[MAX_AMOUNT];
#undef MAX_AMOUNT
static int AMOUNT;

int str_to_int(char* str) {
    
    int value = 0;
    while(*str != '\0') {
        value = value*10 + (*str-'0');
        str++;
    }
    return value;
}

// Essentially assigns a value to a variable in a given expression.
void replace_variable_with_value(char* expr, char var, char val, char* buffer) {
    while (*expr != '\0') {
        if (*expr == var) *buffer = val;
        else *buffer = *expr;
        expr++;
        buffer++;
    }
    *buffer = '\0';
}

// Used to track the depth of the recursion.
// (How many variables have had values assigned?)
static int depth = 0;
void recursion(char* expr) {
    
    if (depth == AMOUNT) {
        //print values stack
        for (int i = 0; i < AMOUNT; i++) printf("%c ", assigned_values[i]);
        printf(": ");
        evaluate_expr(expr);
        return;
    }
    
    //else, replace and call recursively
    depth++;
    char buffer[strlen(expr)+1];
    
    replace_variable_with_value(expr, 'a'+depth-1, '0', buffer);
    assigned_values[depth-1] = '0';
    recursion(buffer);
    
    replace_variable_with_value(expr, 'a'+depth-1, '1', buffer);
    assigned_values[depth-1] = '1';
    recursion(buffer);
    
    depth--;
    
}

// Prints the top line of the table (variables : expression : Result)
void show_header(char* expr) {
    
    for (char i = 'a'; i < 'a'+AMOUNT; i++) printf("%c ", i);
    printf(": %s : Result\n", expr);
    
    // equals sign under every variable:
    for (int i = 0; i < AMOUNT; i++) printf("==");
    printf("==");  // equals signs under ': '
    
    int l = strlen(expr);
    for (int i = 0; i < l; i++) printf("=");  // equals signs under expression
    printf("=========\n"); // equals signs under ' : Result'
    
}

int main(int argc, char** arguments) {

    if (argc != 3) {
        printf("Usage: ./ttable <number of variables> <expr>\n");
        return -1;
    }
    
    AMOUNT = str_to_int(arguments[1]);
    show_header(arguments[2]);
    recursion(arguments[2]);
    return 0;
}
