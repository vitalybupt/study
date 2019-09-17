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


struct TreeNode* prev = NULL;
struct TreeNode* first = NULL;
struct TreeNode* second = NULL;

void orderCheck(struct TreeNode* n1, struct TreeNode* n2) {
    if(n1 == NULL || n2 == NULL) {
       return;
    }
    if(first == NULL) {
	if(n1->val > n2->val) {
	    first = n1;
	    return;
	}
    } else {
	if(n1->val > n2->val) {
	    second = n2;
	    return;
	}
    }
}
void traverseTree(struct TreeNode* root) {
    if(root == NULL) return;
    struct TreeNode* cur = root;
    struct TreeNode* prev = NULL;
    while(cur != NULL) {
    if(cur->left == NULL) {
	// find leaves;
    prev = cur;
	cur = cur->right;
    orderCheck(prev, cur);
	continue;
    }
    struct TreeNode *scanner = cur->left;
    
    while(scanner->right != NULL && scanner->right != cur) {
	scanner = scanner->right;// find the prev node;
    }
    if(scanner->right == NULL) { //first time find prev node
	scanner->right = cur;
    prev = cur;
	cur = cur->left;
    orderCheck(prev, cur);
    } else {
	scanner->right = NULL; // second time meet the node
    prev = cur;
	cur = cur->right;
    orderCheck(prev, cur);
    }
    }
}
void recoverTree(struct TreeNode* root){
    traverseTree(root);
    int tmp = first->val;
    first->val = second->val;
    second->val = tmp;
    return;	
}

int main() {

    return 0;
}
