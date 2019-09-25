#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* prev = NULL;
struct TreeNode* first = NULL;
struct TreeNode* second = NULL;

void orderCheck(struct TreeNode* n1, struct TreeNode* n2) {
    if(n1 == NULL) {
	prev = n2;
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
    while(cur != NULL) {
    if(cur->left == NULL) {
	// find leaves;
	cur = cur->right;
	continue;
    }
    struct TreeNode *scanner = cur->left;
    while(scanner->right != NULL && scanner->right != cur) {
	scanner = scanner->right;// find the prev node;
    }
    if(scanner->right == NULL) { //first time find prev node
	scanner->right = cur;
	cur = cur->left;
    } else {
	scanner->right = NULL; // second time mee the prev
	cur = cur->right;
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
