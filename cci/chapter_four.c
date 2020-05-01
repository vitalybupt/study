#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <limits.h>

#include "hashtable.h"
#include "graph.h"
#include "chapter_four.h"

#define max(x,y)				\
      __extension__ ({ __typeof__ (x) _x = (x);	\
      __typeof__ (y) _y = (y);			\
      _x > _y ? _x : _y; })

static bool graph_routable(p_graph g, phashtable h, int from, int to) {
  if(from == to) return true;
  if(hashtable_ismember_set(h, from)) return false;

  hashtable_insert_set(h, from);
  
  p_list neighs = graph_get_neighs(g,from);
  for(unsigned i = 1; i <= neighs->len; ++i) {
    int neigh = list_get_integer_value(neighs, i);
    if(graph_routable(g, h, neigh, to)) {
      hashtable_remove_set(h, from);
      return true;
    }
  }
  hashtable_remove_set(h, from);
  return false;
}
void test_route_search() {
    p_graph g = graph_create(6);
    assert(g != NULL && g->node_number == 6);
    graph_insert_neigh(g, 0, 1); graph_insert_neigh(g, 0, 4); graph_insert_neigh(g, 0, 5);
    graph_insert_neigh(g, 1, 3); graph_insert_neigh(g, 1, 4);
    graph_insert_neigh(g, 2, 1);
    graph_insert_neigh(g, 3, 2); graph_insert_neigh(g, 3, 4);

    phashtable hset = hashtable_create();
    assert(graph_routable(g, hset, 0, 3));
    assert(hashtable_empty(hset));
    
    assert(!graph_routable(g, hset, 3, 0));
    assert(hashtable_empty(hset));
    
    assert(!graph_routable(g, hset, 2, 0));
    assert(hashtable_empty(hset));

    hashtable_free(hset);
    free(hset);
    graph_free(g);
}

typedef struct tree_node {
  int val;
  struct tree_node *left;
  struct tree_node *right;
} tree_node, *p_tree_node;

static p_tree_node create_bst(int * sort_array, int len) {
  assert(len);
  
  p_tree_node root = malloc(sizeof(tree_node));
  if(len == 1) {
    root->val = sort_array[0];
    root->left = root->right = NULL;
    return root;
  } else if(len == 2) {
    root->val = sort_array[1];
    p_tree_node left = malloc(sizeof(tree_node));
    left->val = sort_array[0];
    left->left = left->right = NULL;
    root->left = left;
    root->right = NULL;
    return root;
  }

  int mid = len/2;
  root->val = sort_array[mid];
  root->left = create_bst(sort_array, mid);
  root->right = create_bst(sort_array+mid+1, mid-1+len%2);
  
  return root;
}

#ifdef DEBUG
static void dump_bst(p_tree_node root) {
  if(!root) return;
  printf("%d\r\n", root->val);
  dump_bst(root->left);
  dump_bst(root->right);  
  return;
}
#endif

static void free_bst(p_tree_node root) {
  if(!root) return;
  free_bst(root->left);
  free_bst(root->right);
  free(root);
  return;
}

static p_list get_list_of_depth(p_list queue, int depth, int num, int target) {
  if(depth == target) return queue;
  int new_num = 0;
  for(int i = 0; i< num; ++i) {
    p_tree_node n = list_pop_front_generic(queue);
    if(n->left) {list_push_back_generic(queue, n->left); ++new_num;}
    if(n->right) {list_push_back_generic(queue, n->right); ++new_num;}
  }
  
  return get_list_of_depth(queue, ++depth, new_num, target);
}

void test_minimal_tree() {
  int sort_array[] = {1, 3, 5, 6, 8, 9};
  p_tree_node bst = create_bst(sort_array, 6);

  p_list queue = list_create(LIST_TYPE_GENERIC);
  list_push_back_generic(queue, bst);
  p_list list_of_depth_3 = get_list_of_depth(queue, 1, 1, 3);
  assert(list_of_depth_3->len == 3);
  assert( ((p_tree_node)(list_get_generic(list_of_depth_3, 1)))->val == 1);
  assert( ((p_tree_node)(list_get_generic(list_of_depth_3, 2)))->val == 5);
  assert( ((p_tree_node)(list_get_generic(list_of_depth_3, 3)))->val == 8);

  list_pop_front_generic(list_of_depth_3);
  list_pop_front_generic(list_of_depth_3);
  list_pop_front_generic(list_of_depth_3);
  
  free_bst(bst);
  free(queue);
  return;
}


void test_list_of_depths() {
  int sort_array[] = {1, 3, 5, 6, 8, 9, 12};
  p_tree_node bst = create_bst(sort_array, 7);

  p_list queue = list_create(LIST_TYPE_GENERIC);
  list_push_back_generic(queue, bst);
  p_list list_of_depth_3 = get_list_of_depth(queue, 1, 1, 3);
  assert(list_of_depth_3->len == 4);
  assert( ((p_tree_node)(list_get_generic(list_of_depth_3, 1)))->val == 1);
  assert( ((p_tree_node)(list_get_generic(list_of_depth_3, 2)))->val == 5);
  assert( ((p_tree_node)(list_get_generic(list_of_depth_3, 3)))->val == 8);
  assert( ((p_tree_node)(list_get_generic(list_of_depth_3, 4)))->val == 12);
  list_pop_front_generic(list_of_depth_3);
  list_pop_front_generic(list_of_depth_3);
  list_pop_front_generic(list_of_depth_3);
  list_pop_front_generic(list_of_depth_3);
  
  free_bst(bst);
  free(queue);
  return;  
}

static int check_balanced(p_tree_node bst) {
  assert(bst);
  int left_depth = 0;
  int right_depth =0;

  if(bst->left != NULL) {
    int left_child_depth = check_balanced(bst->left);
    if(left_child_depth < 0) {
      return -1;
    } else  {
      left_depth = left_child_depth + 1;
    }
  }

  if(bst->right != NULL) {
    int right_child_depth = check_balanced(bst->right);
    if(right_child_depth < 0) {
      return -1;
    } else  {
      right_depth = right_child_depth + 1;
    }
  }

  if(abs(left_depth - right_depth) > 1) {
    return -1;
  }

  return max(left_depth, right_depth);  
}

void test_check_balanced() {
  int sort_array[] = {1, 3, 5, 6, 8, 9, 12};
  p_tree_node bst = create_bst(sort_array, 7);
  assert(check_balanced(bst)>= 0);
  p_tree_node most_left = bst->left;
  while(most_left->left != NULL)
    most_left = most_left->left;

  most_left->left = malloc(sizeof(tree_node));
  most_left = most_left->left;  
  most_left->val = 4; most_left->left = most_left->right = NULL;
  assert(check_balanced(bst) >= 0);

  most_left->left = malloc(sizeof(tree_node));
  most_left = most_left->left;
  most_left->val = 1; most_left->left = most_left->right = NULL;
  assert(check_balanced(bst) < 0);
  
  free_bst(bst);
  return;
}

static bool validate_bst(p_tree_node bst, int *range) {
  assert(bst);

  if(bst->val > range[1]) return false;
  if(bst->val < range[0]) return true;

  if(bst->left != NULL) {
    if(!validate_bst(bst->left, (int[]){range[0], bst->val}))
      return false;
  }
  if(bst->right != NULL) {
    if(!validate_bst(bst->right, (int[]){bst->val, range[1]}))
      return false;
  }
  return true;
}

void test_validate_bst() {
  int sort_array[] = {1, 3, 5, 6, 8, 9, 12};
  p_tree_node bst = create_bst(sort_array, 7);
  assert(validate_bst(bst, (int[]){INT_MIN, INT_MAX}));

  p_tree_node most_left = bst->left;
  while(most_left->left != NULL)
    most_left = most_left->left;
  most_left->left = malloc(sizeof(tree_node));
  most_left->val = 4; most_left->left = most_left->right = NULL;
  assert(!validate_bst(bst, (int[]){INT_MIN, INT_MAX}));
  free_bst(bst);
  return;
}
