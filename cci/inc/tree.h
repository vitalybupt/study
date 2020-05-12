#ifndef TREE_H
#define TREE_H
/* macro and type defination */
#define TREE_NODE_RANGE 100
typedef struct tree_node {
  int val;
  struct tree_node *left;
  struct tree_node *right;
  struct tree_node *parent;
  int left_num;
  int right_num;
} tree_node, *p_tree_node;

/* public function declaration */
p_tree_node create_bst(int * sort_array, int len);
void free_bst(p_tree_node root);
p_tree_node get_bst_node(p_tree_node tree, int n);
p_tree_node create_random_tree(int num);
#ifdef DEBUG
void dump_bst(p_tree_node root);
#endif
#endif
