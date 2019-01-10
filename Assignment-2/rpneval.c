/*
Author: Atul Balaji
Date: 26-08-18
Assignment 2 - RPN Evaluation
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 256

// Pushes given value onto the stack and increments the top index.
void push(double stack[], double value, int *top)
{	
    *top += 1;
    stack[*top] = value;
}

// Performs the desired arithmetic operation between top two elements of the stack and saves the result in the 2nd element from top.
// Topmost element is popped and top index is decremented.
void pop_operate(double stack[], char op_char, int *top, int *flag)
{
    int i;
    int j = *top;
    int op = op_char;										// Stores the ASCII value of the operation character
    switch (op)
    {
        case 43:
			if j 
            stack[j - 1] += stack[j];
            break;
        case 45:
            stack[j - 1] -= stack[j];
            break;
        case 42:
            stack[j - 1] *= stack[j];
            break;
        case 47:
			if (stack[j])
            	stack[j - 1] /= stack[j];
			else											// Division by zero!
				*flag = 0;
            break;
        default:											// Invalid operator!
            *flag = 0;
    }
    *top -= 1;
}

// Evaluate the expression
void rpneval(char **expstring, int size)
{
    int i = 0, top = 0;												// top keeps track of the top position of the stack
	int flag = 1;													// Monitors if there is division by zero or any invalid operators 
    double stack[size/2];											// Because we put only operands into the stack
	int ct_operands = 0;											// Number of operands
	int ct_operators = 0;											// Number of operators
	for (i=0;i<size;i++)
	{	
		if (atof(expstring[i]) || *expstring[i] == '0')				// If atof of the character is True (is a float) and also when the character is '0' 
		{
			ct_operands++;
			push(stack, atof(expstring[i]), &top);					// Push operand onto the stack.
		}
		else
		{
			ct_operators++;
			pop_operate(stack, *expstring[i], &top, &flag);			// When the character is an operator, do the operation and pop the topmost operand.
        }
    }
	// For a legal expression, the number of operands must be one more than the number of operators.
	// Also, there should be no division by zero or invalid operators.
	if (ct_operands == ct_operators + 1 && flag)
		printf("%.4f\n", stack[top]);
	else 
		printf("ERROR\n");
}

// Main function
int main()
{
	char *expression[MAX_LENGTH];									// Array to store input line
	char buffer[256];
	int wordctr;													// Count number of operands/operators in a line
	while (fgets(buffer, 256, stdin))								// The stdin input is stored in buffer string
	{
		wordctr = 0;
		// Splits a string using a null character when it hits one of the characters mentioned in the call.
		// Token stores the substrings until space is seen.
		char* token = strtok(buffer, " \r\n");
		do 
		{
			expression[wordctr] = calloc(sizeof(char), strlen(token) + 1);			// Allocate memory for each string.
			strcpy(expression[wordctr], token);
			wordctr++;
		} while ((token = strtok(NULL, " \r\n")) != NULL);
		rpneval(expression, wordctr);												// Call the function to evaluate the expression in expression
		for(int i=0;i<wordctr;i++)
		{
			free(expression[i]);													// Deallocate memory
		}
	}
	return 0;
}