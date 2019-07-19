#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "binarytree.h"

// return 0 for non binary tree
// for binary tree, return value is the depth
unsigned int verifyBinaryTree(pNode root) {
    int leftdep = root->left ? verifyBinaryTree(root->left) : 0;
    int rightdep = root->right ? verifyBinaryTree(root->right) : 0;
    if(leftdep >= 0 && rightdep >= 0 && abs(leftdep - rightdep) <=1) {
	return leftdep > rightdep ? leftdep + 1 : rightdep + 1;
    }
    return 0;
}
