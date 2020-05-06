#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

#include "cci_utils.h"
#include "arraylist.h"
#include "hashtable.h"
#include "graph.h"
#include "chapter_four.h"

/* macro and type defination */
typedef struct tree_node {
  int val;
  struct tree_node *left;
  struct tree_node *right;
  struct tree_node *parent;
} tree_node, *p_tree_node;

typedef enum {
	      NOT_BUILT,
	      BUILT
} project_status;

typedef struct project {
  p_list neighs;
  int deps;
  project_status status;
} project, *p_project;

/* internal function declaration */
static p_tree_node create_bst(int * sort_array, int len);
static bool graph_routable(p_graph g, phashtable h, int from, int to);
static void free_bst(p_tree_node root);
static p_list get_list_of_depth(p_list queue, int depth, int num, int target);
static int check_balanced(p_tree_node bst);
static bool validate_bst(p_tree_node bst, int *range);
static p_tree_node get_successor(p_tree_node root);
static p_tree_node get_bst_node(p_tree_node tree, int n);
static p_project create_project();
static void free_project(p_project project);
static void add_project_dep(p_project *projects, int p1, int p2);
#ifdef DEBUG
static void inorder_traverse_dump(p_tree_node root);
static void dump_bst(p_tree_node root);
#endif

/* internal function defination */
static bool graph_routable(p_graph g, phashtable h, int from, int to) {
  if(from == to) return true;
  if(hashtable_ismember_set(h, from)) return false;

  hashtable_insert_set(h, from);
  
  p_list neighs = graph_get_neighs(g,from);
  for(int i = 1; i <= neighs->len; ++i) {
    int neigh = list_get_integer_value(neighs, i);
    if(graph_routable(g, h, neigh, to)) {
      hashtable_remove_set(h, from);
      return true;
    }
  }
  hashtable_remove_set(h, from);
  return false;
}

static p_tree_node _create_bst(int *sort_array, int len, p_tree_node parent) {
  p_tree_node root = malloc(sizeof(tree_node));

  if(len == 1) {
    root->val = sort_array[0];
    root->left = NULL;
    root->right = NULL;
    root->parent = parent;
    return root;
  } else if(len == 2) {
    root->val = sort_array[1];
    root->parent = parent;
    p_tree_node left = malloc(sizeof(tree_node));
    left->val = sort_array[0];
    left->parent = root;
    left->left = left->right = NULL;
    root->left = left;
    root->right = NULL;
    return root;
  }

  int mid = len/2;
  root->val = sort_array[mid];
  root->parent = parent;
  root->left = _create_bst(sort_array, mid, root);
  root->right = _create_bst(sort_array+mid+1, mid-1+len%2, root);
  
  return root;
}

static p_tree_node create_bst(int * sort_array, int len) {
  assert(len);
  return _create_bst(sort_array, len, NULL);
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

static bool validate_bst(p_tree_node bst, int *range) {
  assert(bst);
  dbg_printf("validate node %d, %s left, %s right: ",
  	     bst->val, bst->left ? "has" : "no", bst->right ? "has" : "no");
  if(range[0] == INT_MIN)
    dbg_printf("lower unlimited ");
  else
    dbg_printf("lower limist is %d ", range[0]);
  if(range[1] == INT_MAX)
    dbg_printf("upper unlimited\r\n");
  else
    dbg_printf("upper limist is %d\r\n", range[1]);
  
  
  if(bst->val > range[1]) {
    dbg_printf("return false because break upper limit\r\n");
    return false;
  }
  if(bst->val < range[0]) {
    dbg_printf("return false because break lower limit\r\n");
    return false;
  }

  if(bst->left != NULL) {
    if(!validate_bst(bst->left, (int[]){range[0], bst->val})) {
      dbg_printf("return false because left subtree not bst\r\n");
      return false;
    }
  }
  if(bst->right != NULL) {
    if(!validate_bst(bst->right, (int[]){bst->val, range[1]})) {
      dbg_printf("return false because right subtree not bst\r\n");
      return false;
    }
  }
  
  return true;
}

#ifdef DEBUG
static void inorder_traverse_dump(p_tree_node root) {
  if(!root) return;
  if(root->left) inorder_traverse_dump(root->left);
  printf("%d\r\n", root->val);
  if(root->right) inorder_traverse_dump(root->right);
  return;
}
#endif

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

static p_tree_node get_bst_node(p_tree_node tree, int n) {
  return _get_bst_node(tree, &n);
}

static p_tree_node get_successor(p_tree_node root) {
  if(root->right) {
    p_tree_node successor = root->right;
    while(successor->left)
      successor = successor->left;
    return successor;
  } else {
    p_tree_node successor = root->parent;
    while(successor && root->val > successor->val)
      successor = successor->parent;
    return successor;
  }
}

static p_project create_project() {
  p_project project = malloc(sizeof(struct project));
  project->deps = 0;
  project->neighs = list_create(LIST_TYPE_INTEGER);
  project->status = NOT_BUILT;
  return project;
}

static void free_project(p_project project) {
  list_free(project->neighs);
  free(project->neighs);
  free(project);
  return;
}

static void add_project_dep(p_project *projects, int p1, int p2) {
  list_push_back_integer(projects[p1]->neighs, p2);
  projects[p2]->deps++;
  return;  
}

static p_list build_order(p_project *projects, int num) {
  p_list built_projects = list_create(LIST_TYPE_INTEGER);

  int need_process = 0;
  do {
    for(int i = 0; i < num; ++i) {
      if( projects[i]->deps == 0 && projects[i]->status == NOT_BUILT) {
	/* find no dependent project */
	list_push_back_integer(built_projects, i);
      }
    }
    if(need_process == built_projects->len) {
      return NULL;
    }
    
    for(; need_process < built_projects->len; ++need_process) {
      int process_project = list_get_integer_value(built_projects, need_process+1);
      p_list resolve_dep_projects = projects[process_project]->neighs;
      for(int i = 1; i <= resolve_dep_projects->len; ++i) {
	p_project resolve_dep = projects[list_get_integer_value(resolve_dep_projects, i)];
	resolve_dep->deps--;
      }
      projects[process_project]->status = BUILT;
    }
  } while(need_process < num);
  return built_projects;
}

/* public function defination */
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

void test_validate_bst() {
  int sort_array[8];
  for(int i = 0; i < 8; ++i)
    sort_array[i] = i;
  p_tree_node bst = create_bst(sort_array, 8);
  assert(validate_bst(bst, (int[]){INT_MIN, INT_MAX}));

  p_tree_node most_left = bst->left;
  while(most_left->left != NULL)
    most_left = most_left->left;
  most_left->left = malloc(sizeof(tree_node));
  most_left->val = 4; most_left->left = most_left->right = NULL;
  //most_left = most_left->left;
  assert(!validate_bst(bst, (int[]){INT_MIN, INT_MAX}));
  free_bst(bst);
  return;
}

void test_find_successor() {
  int sort_array[16];
  for(int i = 0; i < 16; ++i)
    sort_array[i] = i;
  p_tree_node bst = create_bst(sort_array, 16);
  assert(validate_bst(bst, (int[]){INT_MIN, INT_MAX}));

  assert(get_successor(bst)->val == 9);

  p_tree_node n0 = get_bst_node(bst, 1);
  assert(n0->val == 0);
  assert(get_successor(n0)->val == 1);

  p_tree_node n1 = get_bst_node(bst, 2);
  assert(n1->val == 1);
  assert(get_successor(n1)->val == 2);

  p_tree_node n2 = get_bst_node(bst, 3);
  assert(n2->val == 2);
  assert(get_successor(n2)->val == 3);
  
  free_bst(bst);
  return;
}

void test_build_order() {
  p_project projects[6];
  for(int i = 0; i < 6; ++i) {
    projects[i] = create_project();
  }
  add_project_dep(projects, 0, 5);
  add_project_dep(projects, 1, 5);
  add_project_dep(projects, 2, 3);
  add_project_dep(projects, 3, 0);   add_project_dep(projects, 3, 1);
  list_dump(projects[5]->neighs);

  p_list build_path = build_order(projects, 6);
  assert(build_path != NULL);
  assert(list_get_integer_value(build_path, 1) == 2);
  assert(list_get_integer_value(build_path, 2) == 4);
  assert(list_get_integer_value(build_path, 3) == 3);
  assert(list_get_integer_value(build_path, 4) == 0);
  assert(list_get_integer_value(build_path, 5) == 1);
  assert(list_get_integer_value(build_path, 6) == 5);

  for(int i = 0; i < 6; ++i) {
    free_project(projects[i]);
  }
  list_free(build_path);
  free(build_path);



  p_project projects2[8];
  for(int i = 0; i < 8; ++i) {
    projects2[i] = create_project();
  }
  add_project_dep(projects2, 0, 4);
  add_project_dep(projects2, 1, 0);  add_project_dep(projects2, 1, 4);   add_project_dep(projects2, 1, 7);
  add_project_dep(projects2, 2, 0);
  add_project_dep(projects2, 3, 6);
  add_project_dep(projects2, 5, 0);   add_project_dep(projects2, 5, 1);   add_project_dep(projects2, 5, 2);
  list_dump(projects2[5]->neighs);

  p_list build_path2 = build_order(projects2, 8);
  assert(build_path2 != NULL);
  assert(list_get_integer_value(build_path2, 1) == 3);
  assert(list_get_integer_value(build_path2, 2) == 5);
  assert(list_get_integer_value(build_path2, 3) == 1);
  assert(list_get_integer_value(build_path2, 4) == 2);
  assert(list_get_integer_value(build_path2, 5) == 6);
  assert(list_get_integer_value(build_path2, 6) == 0);
  assert(list_get_integer_value(build_path2, 7) == 7);
  assert(list_get_integer_value(build_path2, 8) == 4);

  for(int i = 0; i < 8; ++i) {
    free_project(projects2[i]);
  }
  list_free(build_path2);
  free(build_path2);
  return;
}
