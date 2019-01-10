# Implement a binary search tree

Print the inorder, pre-order and post-order traversals of the given binary tree.  
First line of the input is the no.of elements (n).  
Next n lines are the elements.  

Output format is:  
First n lines is inorder.
Next n lines is pre-order.
Next n lines is post-order.

## Approach

1. A structure for a node of the binary tree is created, with the number it stores, a pointer to the left child and a pointer to the right child.
2. New nodes are inserted when the numbers are read from the input.
3. Functions for inorder, pre-order and post-order traversal are implemented in recursive form.