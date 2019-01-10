# RPN Evaluation

Reverse polish notation (RPN) is used as a temporary format while evaluating arithmetic expressions: it is otherwise known as the "postfix" notation, as opposed to "infix" that we are normally familiar with.

For example, the "infix" expression (2*(3 + 4) ) / 5 would be represented in RPN as 3 4 + 2*5 /. As you can see, there are no parentheses ("()" brackets) used in RPN, and the expression can directly be evaluated while reading from left to right.

A more detailed explanation can be found online, for example from the Wikipedia article [here.](https://en.wikipedia.org/wiki/Reverse_Polish_notation) As seen in the article, evaluation is typically done using a "stack" which is one of the simplest non-trivial data structures.  

## Example

Input:
1 2 3 /  
2 3 /  
3 4 * /  
1 2 4 + - 5 * 7 /  

## Output

ERROR  
0.6667  
ERROR  
-3.5714

## Approach

1. Expression is read and passed to the function.
2. If the character is an operand, it is pushed into the stack.
3. If the character is an operator, then the operation is performed on the two topmost elements of stack and the result is stored in the second element from top. The top element is then popped from stack.
