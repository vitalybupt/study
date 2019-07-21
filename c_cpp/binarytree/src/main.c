#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "binarytree.h"

int main()
{
  pNode tree1 = malloc(sizeof(Node));
  tree1->value = 3;
  tree1->left = malloc(sizeof(Node));
  tree1->left->value = 9;
  tree1->left->left = tree1->left->right = NULL;
  tree1->right = malloc(sizeof(Node));
  tree1->right->value = 20;
  tree1->right->left = malloc(sizeof(Node));
  tree1->right->left->value = 15;
  tree1->right->left->left = tree1->right->left->right = NULL;
  tree1->right->right = malloc(sizeof(Node));
  tree1->right->right->value = 7;
  tree1->right->right->left = tree1->right->right->right = NULL;
  int ret = verifyBinaryTree(tree1);
  printf("the tree1 is %s avl\r\n", ret < 0 ? "not" : "a");

  /* tree1->right->right->right = malloc(sizeof(Node)); */
  /* tree1->right->right->right->value = 3; */
  /* tree1->right->right->right->left = tree1->right->right->right->right = NULL; */

  insertIntoBinaryTree(tree1, 20);
  ret = verifyBinaryTree(tree1);
  printf("the tree2 is %s avl\r\n", ret < 0 ? "not" : "a");
  
  return 0;
}
