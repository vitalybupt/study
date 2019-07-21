#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "binarytree.h"

// return 0 for non binary tree
// for binary tree, return value is the depth
int verifyBinaryTree(pNode root) {
  if(root == NULL) return 0;
  int leftdep = verifyBinaryTree(root->left);
  int rightdep = verifyBinaryTree(root->right);
  if(leftdep >= 0 && rightdep >= 0 && abs(leftdep - rightdep) < 2)
    return (leftdep >= rightdep) ? leftdep +1 : rightdep +1 ;
  return -1;
}

pNode insertIntoBinaryTree(pNode root, int val) {
  if(root == NULL)  {
    pNode newNode = malloc(sizeof(Node));
    memset(newNode, 0, sizeof(Node));
    newNode->value = val;
    return newNode;
  }
  if( val < root->value) root->left = insertIntoBinaryTree(root->left, val);
  else root->right = insertIntoBinaryTree(root->right, val);
  return root;			   
}
