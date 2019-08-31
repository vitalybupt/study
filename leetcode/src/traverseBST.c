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

void insertNode( int** result, int val, int* size) {
  if(*result == NULL) {
    *result = malloc(sizeof(int));
    *size = 1;
    (*result)[*size -1] = val;
  } else {
    (*size) += 1;
    *result = realloc(*result, sizeof(int*)*(*size));
    (*result)[*size -1] = val;
  }
}

int* inorderTraversal(struct TreeNode* root, int* returnSize){
  struct TreeNode* cur = root;
  int * ret = NULL;

  while(cur!= NULL) {
    if(cur->left == NULL) {
      insertNode(&ret, cur->val, returnSize);
      cur = cur->right;
    } else {
      struct TreeNode* pre = cur->left;
      while(pre->right != NULL && pre->right != cur){
	pre = pre->right;
      }

      if(pre->right == cur) {
	pre->right = NULL;
	insertNode(&ret, cur->val, returnSize);
	cur = cur->right;
      } else {
	pre->right = cur;
	cur = cur->left;
      }
    }
  }

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

  int size = 0;
  int* ret = inorderTraversal(&root, &size);
  for(int i = 0; i<size; i++) {
    printf("%d\r\n", ret[i]);
  }
  printf("%d\r\n", size);
  free(ret);
}
