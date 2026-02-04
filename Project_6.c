#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "stack.h"

/* Project 5 - Part 2
   Akshita Ramesh
   EGRE 246 - Fall 2023
*/
int precedence(char val)
{
    if (val == '(' || val == ')')
    {
        return 6;
    } else if (val == '^')
    {
        return 5;
    } else if (val == '*' || val == '/' || val == '%')
    {
        return 4;
    } else if (val == '+' || val == '-')
    {
        return 2; 
    } else {
        return 1; 
    }

    return 1; 
}


/* void separate(char input[], struct stack oper, struct stack num)
{
    int operAms = 0;
    int valAms = 0; 
    for (int i = 0; input[i] != 32; i++)
    {
        if (input[i] > 39 && input[i] < 48 && input[i] != 0)
        {
            oper.array[operAms] = input[i]; 
            operAms++;  
        }

        if (input[i] > 47 && input[i] < 58 && input[i] != 0)
        {
            num.array[valAms] = input[i]; 
            valAms++;  
        }

    }
} */

int eval(char *input, int variables[26]) {
    stack operandStack = createStack();
    stack operatorStack = createStack();

    char *token = strtok(input, " ");

    while (token != NULL) {
        if (isdigit(token[0])) {
            push(operandStack, atoi(token));
        } else if (isalpha(token[0])) {
            push(operandStack, variables[token[0] - 'a']);
        } else if (token[0] == '(') {
            push(operatorStack, '(');
        } else if (token[0] == ')') {
            while (!isEmpty(operatorStack) && top(operatorStack) != '(') {
                char op = top(operatorStack);
                pop(operatorStack);
                int b = top(operandStack);
                pop(operandStack);
                int a = top(operandStack);
                pop(operandStack);
                switch (op) {
                    case '^':
                        push(operandStack, (int)pow(a, b));
                        break;
                    case '*':
                        push(operandStack, a * b);
                        break;
                    case '/':
                        if (b != 0) {
                            push(operandStack, a / b);
                        } else {
                            printf("Error - division by zero");
                            exit(0);
                        }
                        break;
                    case '%':
                        push(operandStack, a % b);
                        break;
                    case '+':
                        push(operandStack, a + b);
                        break;
                    case '-':
                        push(operandStack, a - b);
                        break;
                }
            }
            if (!isEmpty(operatorStack) && top(operatorStack) == '(') {
                pop(operatorStack); // Pop the '('
            }
        } else if (strchr("^", token[0]) != NULL) {
            push(operatorStack, token[0]);
        } else if (strchr("*/%", token[0]) != NULL) {
            while (!isEmpty(operatorStack) && top(operatorStack) != '(' && precedence(top(operatorStack)) >= precedence(token[0])) {
                char op = top(operatorStack);
                pop(operatorStack);
                int b = top(operandStack);
                pop(operandStack);
                int a = top(operandStack);
                pop(operandStack);
                switch (op) {
                    case '+':
                        push(operandStack, a + b);
                        break;
                    case '-':
                        push(operandStack, a - b);
                        break;
                    case '*':
                        push(operandStack, a * b);
                        break;
                    case '/':
                        if (b != 0) {
                            push(operandStack, a / b);
                        } else {
                            printf("Error - division by zero");
                            exit(0);
                        }
                        break;
                    case '%':
                        push(operandStack, a % b);
                        break;
                    case '^':
                        push(operandStack, (int)pow(a, b));
                        break;
                }
            }
            push(operatorStack, token[0]);
        } else if (strchr("+-", token[0]) != NULL) {
            while (!isEmpty(operatorStack) && top(operatorStack) != '(' && precedence(top(operatorStack)) >= precedence(token[0])) {
                char op = top(operatorStack);
                pop(operatorStack);
                int b = top(operandStack);
                pop(operandStack);
                int a = top(operandStack);
                pop(operandStack);
                switch (op) {
                    case '+':
                        push(operandStack, a + b);
                        break;
                    case '-':
                        push(operandStack, a - b);
                        break;
                    case '*':
                        push(operandStack, a * b);
                        break;
                    case '/':
                        if (b != 0) {
                            push(operandStack, a / b);
                        } else {
                            printf("Error - division by zero");
                            exit(0);
                        }
                        break;
                    case '%':
                        push(operandStack, a % b);
                        break;
                    case '^':
                        push(operandStack, (int)pow(a, b));
                        break;
                }
            }
            push(operatorStack, token[0]);
        } else {
            printf("Error - illegal character '%c'", token[0]);
            exit(0);
        }

        token = strtok(NULL, " ");
    }

    while (!isEmpty(operatorStack)) {
        char op = top(operatorStack);
        pop(operatorStack);
        int b = top(operandStack);
        pop(operandStack);
        int a = top(operandStack);
        pop(operandStack);
        switch (op) {
            case '+':
                push(operandStack, a + b);
                break;
            case '-':
                push(operandStack, a - b);
                break;
            case '*':
                push(operandStack, a * b);
                break;
            case '/':
                if (b != 0) {
                    push(operandStack, a / b);
                } else {
                    printf("Error - division by zero");
                    exit(0);
                }
                break;
            case '%':
                push(operandStack, a % b);
                break;
            case '^':
                push(operandStack, (int)pow(a, b));
                break;
        }
    }

    int result = top(operandStack);

    freeStack(operandStack);
    freeStack(operatorStack);

    return result;
}

int assignVar (char *input, int variables[])
{
    if (strstr(input, ">")) {
            char var;
            int value;
            if (sscanf(input, "%d > %c", &value, &var) == 2) {
                if (value == 0 && strchr(input, '0') == NULL) {
                    printf("Error - invalid assignment");
                    exit(0);
                } else {
                    variables[var - 'a'] = value;
                    printf("%d\n", variables[var - 'a']);
                }
            } 
            else if (strlen(input) > 3)
            {
                const char split[5] = ">"; 

                char *token, *token2;
                /* get the first token */
                token = strtok(input, split); 
                token2 = strtok(NULL, " "); 

                //printf("%s", token); 
                //printf("%s", token2); 

                //char vals = token2; 

                value = eval(token, variables); 
                variables[token2[0] - 'a'] = value;
                printf("%d\n", variables[token2[0] - 'a']);
            }
            else {
                printf("Error - invalid assignment format\n");
                exit(0); 
            }
        }


}

int main() {
    char input[100];
    int variables[26] = {0};

    while (1) {
        printf("? ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        if (input[0] == '\n') {
            break;
        }

        if (strstr(input, ">"))
        {
            assignVar(input, variables); 
        }  
        else if (input[0] != '\n') {
            int result = eval(input, variables);
            printf("%d\n", result);
        } else {
            exit(0);
        }
    }


    /* else if (input[0] == '\n') {
            break;*/
    return 0;
}
