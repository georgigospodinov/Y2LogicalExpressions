#include "estack.h"

#define MAX_AMOUNT 26
static char assigned_values[MAX_AMOUNT];
#undef MAX_AMOUNT
static int AMOUNT;
const char* END_OF_FORMAT = " : Result\n";

static int number_of_solutions = 0;

int str_to_int(char* str) {
    
    int value = 0;
    int v;
    while(*str != '\0') {
        v = (*str-'0');
        if ( v < 0 || v > 9) {
            printf("Invalid argument - number of variables must be a number!\n");
            exit(1);
        }
        value = value*10 + v;
        str++;
    }
    
    if (value > 26) {
        printf("Invalid argument - number of variables must be less than 27!\n");
        exit(1);
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
        char outbuffer[strlen(expr)+strlen(END_OF_FORMAT)+1];
        if (evaluate_expr(expr, outbuffer)) {
            //print assigned values
            for (int i = 0; i < AMOUNT; i++) printf("%c ", assigned_values[i]);
            printf(": ");
            printf("%s", outbuffer);
            number_of_solutions++;
        }
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
    printf(": %s", expr);
    printf(END_OF_FORMAT);
    
    // equals sign under every variable:
    for (int i = 0; i < AMOUNT; i++) printf("==");
    printf("==");  // equals signs under ': '
    
    int l = strlen(expr);
    for (int i = 0; i < l; i++) printf("=");  // equals signs under expression
    printf("=========\n"); // equals signs under ' : Result'
    
}

int main(int argc, char** arguments) {

    if (argc != 3 && argc != 4) {
        printf("argc=%d", argc);
        printf("Usage: ./ttable2 <number of variables> <expr>\n");
        printf("Or: ./ttable2 <number of variables> <expr1> <expr2>\n");
        return -1;
    }
    AMOUNT = str_to_int(arguments[1]);
    
    if (argc == 3) {
        show_header(arguments[2]);
        recursion(arguments[2]);
        
        if (number_of_solutions == 0) printf("The expression is unsatisfiable!\n");
        else if (number_of_solutions == (1<<AMOUNT)) printf("The expression is valid!\n");
        else printf("The expression is invalid but satisfiable!\n");
    }
    else {  // argc == 4
        
        int l1 = strlen(arguments[2]);
        int l2 = strlen(arguments[3]);
        char expr[l1+l2+3];
        for (int i = 0; i < l1; i++) expr[i] = arguments[2][i];
        for (int i = 0; i < l2; i++) expr[l1+i] = arguments[3][i];
        expr[l1+l2] = ' ';
        expr[l1+l2+1] = '=';
        expr[l1+l2+2] = '\0';
        
        show_header(expr);
        recursion(expr);
        
        if (number_of_solutions == (1<<AMOUNT)) printf("The expressions are equivalent!\n");
        else printf("The expressions are not equivalent!\n");
    }
    return 0;
}
