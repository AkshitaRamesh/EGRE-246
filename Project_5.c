#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "stack.h"

#define MAX_SIZE 1000 // Arbitrary Number

/* Project 5 Part 1 
   Akshita Ramesh 
   EGRE 246 - Fall 2023 */
int end(char input[], int endProgram)
{
    if (input[0] == '\n')
    {
        printf("spoottttedddd"); 
        endProgram = 1; 
    }

    return endProgram;
}

void reset(char input[])
{
    strcpy(input, ""); 
    //printf("?");
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

int main(void) {
    char input[MAX_SIZE];  
    stack operand = createStack();
    stack operator = createStack();

    while (1) {
        printf("? ");
        fgets(input, sizeof(input), stdin);

        if (strlen(input) == 1 && input[0] == '\n') {
            break;
        }

       
        char *token;
        token = strtok(input, " ");
        
       while (token != NULL) {

    
    if (token[0] >= 'a' && token[0] <= 'z' && token[1] == '>' && token[2] == '\0') {
       
        int value = atoi(strtok(NULL, " "));
    } else {
        
        printf("%s", token);
        

        if (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/' || token[0] == '%' || token[0] == '^' || token[0] == '(') {
            push(operator, token[0]);
    
        } else {
            int value = atoi(token);
            push(operand, value);
        }

    }

    token = strtok(NULL, " ");
    printf("\n");
}

    printf("(null)");

        printf("\nOperand Stack = [top] ");
        while (!isEmpty(operand)) {
            printf("%d ", top(operand));
            pop(operand);
        }

        printf("\nOperator Stack = [top] ");
        while (!isEmpty(operator)) {
            printf("%c ", top(operator));
            pop(operator);
        }
        printf("\n");
    }

    /*
    printf("\noperand stack = [top] "); 

    // printf("operators count = %d ", operators.count); 

    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (nums.array[i] > 0)
        {
           printf("%c ", nums.array[i]); 
        }
    }

    printf("\noperator stack = [top] "); 

    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (operators.array[i] > 0)
        {
           printf("%c ", operators.array[i]); 
        }
        
    }
    
    
    */

    // reset(input);

    freeStack(operand);
    freeStack(operator);

    return 0;
}
