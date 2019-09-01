#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

void traversalBST(struct TreeNode* root, int **stack, bool *ret) {
  if(*ret == false)
    return;

  if(root->left != NULL) {
    traversalBST(root->left, stack, ret);
  }
  if(*stack == NULL) {
    *stack = malloc(sizeof(int));
    **stack = root->val;
  } else if(root->val <= **stack) {
    *ret = false;
    return;
  } else
    **stack = root->val;
  if(root->right != NULL) {
    traversalBST(root->right, stack, ret);
  }
}

bool isValidBST(struct TreeNode* root) {
  if(root == NULL) return true;
  int *stack = NULL;  bool ret = true;
  traversalBST(root, &stack, &ret);
  return ret;
}
int main() {
  struct TreeNode root;
  root.val = 2;
  struct TreeNode left; memset(&left, 0, sizeof(struct TreeNode));
  left.val = 1;
  struct TreeNode right; memset(&right, 0, sizeof(struct TreeNode));
  right.val = 3;
  root.left = &left;
  root.right = &right;

  //printf("%s valid bst\r\n", isValidBST(&root) ? "is" : "not");

  root.val = 1;
  root.right = NULL;
  printf("%s valid bst\r\n", isValidBST(&root) ? "is" : "not");
  
}
