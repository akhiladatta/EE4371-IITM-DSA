RPN Evaluation 
--------------

Reverse polish notation (RPN) is used as a temporary format while evaluating arithmetic expressions: it is otherwise known as the "postfix" notation, as opposed to "infix" that we are normally familiar with. 

For example, the "infix" expression  (2 * (3 + 4) ) / 5  would be represented in RPN as  3 4 + 2 * 5 /  As you can see, there are no parentheses ("()" brackets) used in RPN, and the expression can directly be evaluated while reading from left to right. 

A more detailed explanation can be found online, for example from the Wikipedia article https://en.wikipedia.org/wiki/Reverse_Polish_notation  As seen in the article, evaluation is typically done using a "stack" which is one of the simplest non-trivial data structures.  

For this assignment, you need to  implement a stack - either use classes in C++, or struct and functions in C - either one is acceptable, but you should provide your own implementation and not use someone else's code for this. read the input into the stack - it is probably best to store the operators and numbers as strings or char[] arrays, but you can use functions such "atoi" to convert a string to a number for evaluation. evaluate and print out the result using 4 digits after the decimal place: you can use "printf(".4f", x)" to get this behaviour. 

Example:  
Input: 
1 2 3 / 
2 3 / 
3 4 * / 
1 2 4 + - 5 * 7 /  

Output: 
ERROR 
0.6667 
ERROR 
-3.5714
