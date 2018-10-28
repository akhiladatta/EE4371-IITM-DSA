/*
EE4371 - Assignment 3 - Binary Search Tree
Date: 07-09-2018
Author: Atul Balaji (EE16B002)
*/

#include "stdio.h"
#include<stdlib.h>

// Structure for each node in the tree
struct node
{
    int data;
    struct node* left;
    struct node* right;
};

// Function to add a node with some value so that insertion can be node
struct node* createNode(int value)
{
    struct node* newNode = malloc(sizeof(struct node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}
  
// Function to insert a new node to the tree at appropriate location
struct node* insert(struct node* root, int data)
{   
    if (root == NULL) return createNode(data);                  // If you reach a leaf, it is time to make the insertion
    if (data < root->data)
        root->left  = insert(root->left, data);                 // Call the function again with the current node acting as the new root
    else if (data > root->data)
        root->right = insert(root->right, data);
 
    return root;
}

// Function to implement in-order traversal. The output is in sorted order.
void inorder(struct node* root)
{
    if(root == NULL) return;
    inorder(root->left);
    printf("%d\n", root->data);
    inorder(root->right);
}

// Function to implement pre-order traversal
void preorder(struct node* root)
{
    if(root == NULL) return;
    printf("%d\n", root->data);
    preorder(root->left);
    preorder(root->right);
}

// Function to implement post-order traversal
void postorder(struct node* root)
{
    if(root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d\n", root->data);
}

int main()
{
    int num,j,*arr;
    struct node *root = NULL;                               // Root node
    scanf("%d",&num);                                       // Read number of elements
    arr = (int*)malloc(num * sizeof(int));                  // Allocate memory for the tree
    for(j=0;j<num;j++)
    {
        scanf("%d",&arr[j]);
        if (j == 0) root = insert(root, arr[j]);            // Make the first element to be inserted as the root
        else insert(root, arr[j]);                          // Routine insertion
    }

    // Print the inorder, pre-order, post-order traversals
    inorder(root);
    preorder(root);
    postorder(root);
}