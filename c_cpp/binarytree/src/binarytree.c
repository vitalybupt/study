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

pNode insertBinaryNode(pNode root, int value ) {
    pNode newRoot = NULL;
    if (root == NULL) {
	newRoot = malloc(sizeof(Node));
	memeset(newRoot, 0, sizeof(Node));
	newRoot->value = value;
	newRoot->height = 0;
	return newRoot;
    }

    newRoot = root;
    if( value < root->data ) {
	root->left = insertBinaryNode(root->left, value);
	root->height = maxHeight(root->left, root->right) + 1;
	if (root->left->left->height > root->right->height) newRoot = rotateLL(root, root->left, root->right);
	else if(root->left->right->height > root->right->height ) newRoot = rotateLR(root, root->left, root->right);
    }else {
	root->right = insertBinaryNode(root->right, value);
	root->height = maxHeight(root->left, root->right) + 1;
	if (root->right->left->height > root->left->height) newRoot = rotateRL(root, root->left, root->right);
	else if(root->right->right->height > root->left->height ) newRoot = rotateRR(root, root->left, root->right);
    }
    return newRoot;    
}
