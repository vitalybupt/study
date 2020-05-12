#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

#include "tree.h"
#include "list.h"

static p_tree_node _create_bst(int *sort_array, int len, p_tree_node parent) {
  p_tree_node root = malloc(sizeof(tree_node));

  if(len == 1) {
    root->val = sort_array[0];
    root->left = NULL;
    root->right = NULL;
    root->left_num = 0;
    root->right_num = 0;
    root->parent = parent;
    return root;
  } else if(len == 2) {
    root->val = sort_array[1];
    root->parent = parent;
    p_tree_node left = malloc(sizeof(tree_node));
    left->val = sort_array[0];
    left->parent = root;
    left->left = left->right = NULL;
    left->left_num = 0;
    left->right_num = 0;
    root->left = left;
    root->right = NULL;
    root->left_num = 1;
    root->right_num = 0;
    return root;
  }

  int mid = len/2;
  root->val = sort_array[mid];
  root->parent = parent;
  root->left = _create_bst(sort_array, mid, root);
  root->right = _create_bst(sort_array+mid+1, mid-1+len%2, root);
  root->left_num = mid;
  root->right_num = len - mid - 1;
  return root;
}

static p_tree_node _create_random_node() {
  p_tree_node ret = NULL;
  do{
    ret = malloc(sizeof(tree_node));
    ret->val = rand()%TREE_NODE_RANGE - TREE_NODE_RANGE/2;
    ret->left = NULL;
    ret->right = NULL;
  }while(0);
  return ret;
}

static void _append_random_node(p_list queue, int num) {
  p_tree_node cur = list_pop_front_generic(queue);
  assert(cur);
  do {
    p_tree_node n = _create_random_node();
    if(cur->left == NULL) {
      cur->left = n;
    } else {
      cur->right = n;
      cur = list_pop_front_generic(queue);
    }
    list_push_back_generic(queue, n);
  }while(--num);
  return;
}

static p_tree_node _get_bst_node(p_tree_node node, int *n) {
  p_tree_node ret = NULL;
  do {
    if(node->left) {
      ret = _get_bst_node(node->left, n);
      if(ret)
	break;
    }

    if(--(*n) ==0 ) {
      ret = node;
      break;
    }

    if(node->right) {
      ret = _get_bst_node(node->right, n);
      if(ret)
	break;
    }
  }while(0);
  return ret;
}

/* public function defination */
p_tree_node create_bst(int * sort_array, int len) {
  assert(len);
  return _create_bst(sort_array, len, NULL);
}

#ifdef DEBUG
void dump_bst(p_tree_node root) {
  if(!root) return;
  printf("%d\r\n", root->val);
  dump_bst(root->left);
  dump_bst(root->right);  
  return;
}
#endif


p_tree_node get_bst_node(p_tree_node tree, int n) {
  return _get_bst_node(tree, &n);
}

p_tree_node create_random_tree(int num) {
  p_tree_node tree = NULL;
  do {
    if(num <= 0) break;
    tree = _create_random_node();
    p_list queue = list_create(LIST_TYPE_GENERIC);
    list_push_back_generic(queue, tree);
    _append_random_node(queue, num-1);
    list_free(queue);
    free(queue);
  } while(0);
  return tree;
}

void free_bst(p_tree_node root) {
  if(!root) return;
  free_bst(root->left);
  free_bst(root->right);
  free(root);
  return;
}


