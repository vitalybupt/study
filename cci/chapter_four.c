#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#include "cci_utils.h"
#include "tree.h"
#include "arraylist.h"
#include "hashtable.h"
#include "graph.h"
#include "matrixbuilder.h"
#include "chapter_four.h"

/* macro and type defination */
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
static bool graph_routable_dfs(p_graph g, phashtable h, int from, int to);
static bool graph_routable_bfs(p_graph g, p_list q, int target, phashtable h);
static p_list get_list_of_depth(p_list queue, int depth, int num, int target);
static int check_balanced(p_tree_node bst);
static bool validate_bst(p_tree_node bst, int *range);
static p_tree_node get_successor(p_tree_node root);
static p_project create_project();
static void free_project(p_project project);
static void add_project_dep(p_project *projects, int p1, int p2);
static bool _tree_dfs_cover(p_tree_node root, p_tree_node p);
static p_tree_node _bst_random_node_iteration(p_tree_node root, int random);
#ifdef DEBUG
static void inorder_traverse_dump(p_tree_node root);
#endif

/* internal function defination */
static bool graph_routable_dfs(p_graph g, phashtable h, int from, int to) {
  if(from == to) return true;
  if(hashtable_ismember_set(h, from)) return false;

  hashtable_insert_set(h, from);
  
  p_list neighs = graph_get_neighs(g,from);
  for(int i = 1; i <= neighs->len; ++i) {
    int neigh = list_get_integer_value(neighs, i);
    if(graph_routable_dfs(g, h, neigh, to)) {
      hashtable_remove_set(h, from);
      return true;
    }
  }
  hashtable_remove_set(h, from);
  return false;
}

static bool graph_routable_bfs(p_graph g, p_list q, int target, phashtable h) {
    while(!list_empty(q)) {
        long n = list_pop_front_integer(q);
        //visit node
        if( n == target )
            return true;
        hashtable_insert_set(h, n);
        // exploit node
        p_list neighs = graph_get_neighs(g, n);
        for(int i = 1; i <= neighs->len; ++i) {
            int neigh = list_get_integer_value(neighs, i);
            if(!hashtable_ismember_set(h, neigh))
                list_push_back_integer(q, neigh);
        }
    }
    return false;
}

static bool _tree_dfs_cover(p_tree_node root, p_tree_node p) {
    if(root == NULL) return false;
    if(root == p) return true;
    return _tree_dfs_cover(root->left, p) || _tree_dfs_cover(root->right,p);    
}

static p_tree_node _tree_dfs_search_node(p_tree_node root, int v) {
    p_tree_node ret = NULL;
    
    if(root == NULL) return NULL;
    if(root->val == v) return root;
    if(!(ret = _tree_dfs_search_node(root->left, v)))
        ret = _tree_dfs_search_node(root->right,v);
    return ret;
}

static p_tree_node _tree_search_common_ancestor(p_tree_node root, p_tree_node p1, p_tree_node p2) {
    p_tree_node ret = NULL;
    do {
        if(root == p1 || root == p2) {
            ret = root;
            break;
        }

        bool p1_in_left = _tree_dfs_cover(root->left, p1);
        bool p2_in_left = _tree_dfs_cover(root->left, p2);
        if(p1_in_left && p2_in_left) {
            ret =  _tree_search_common_ancestor(root->left, p1, p2);
            break;
        } else if(p1_in_left || p2_in_left) {
            ret = root;
            break;
        } else {
            ret =  _tree_search_common_ancestor(root->right, p1, p2);
            break;
        }
    } while(0);
    
    return ret;
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

static void _free_list_in_arraylist(pArrayList a) {
    for(int i = 0; i < a->size; ++i) {
      list_free(a->val[i]);
    }
    return;
}

static void weave(p_list left, p_list right, p_list prefix, pArrayList ret ) {
  if(list_empty(left) && list_empty(right)) {
    arraylist_append_generic(ret, list_clone(prefix));
    return;
  }

  if(!list_empty(left)) {
    long val =  list_pop_front_integer(left);
    list_push_back_integer(prefix, val);
    weave(left, right, prefix, ret); 
    list_push_front_integer(left, val);
    list_pop_back_integer(prefix);
  }
  if(!list_empty(right)) {
    long val =  list_pop_front_integer(right);
    list_push_back_integer(prefix, val);
    weave(left, right, prefix, ret);
    list_push_front_integer(right, val);
    list_pop_back_integer(prefix);
  }
  return;
}

static pArrayList _all_arrays(p_tree_node root) {
  pArrayList ret = create_arraylist();

  do{
    if(root == NULL){
      p_list nop = list_create(LIST_TYPE_INTEGER);
      arraylist_append_generic(ret, nop);
      break;
    }

    p_list prefix = list_create(LIST_TYPE_INTEGER);
    list_push_back_integer(prefix, root->val);
    pArrayList left_arrays = _all_arrays(root->left);
    pArrayList right_arrays = _all_arrays(root->right);

    for(int i = 0; i < left_arrays->size; ++i) {
      p_list left = arraylist_get(left_arrays, i);
        for(int j = 0; j < right_arrays->size; ++j) {
	  p_list right = arraylist_get(right_arrays, j);
	  weave(left, right, prefix, ret);
        }
    }
    list_free(prefix);
    free(prefix);
    _free_list_in_arraylist(left_arrays);
    _free_list_in_arraylist(right_arrays);
    free_arraylist(left_arrays);
    free_arraylist(right_arrays);
    free(left_arrays);
    free(right_arrays);
  } while(0);

  return ret;
}

static long long sum_matrix(p_matrix m, bool order) {
  long long sum = 0;
  if(order) {
    for(int r = 0; r < m->row; ++r) {
      for(int c = 0; c < m->col; ++c) {
	sum += matrix_val(m, r, c);
      }
    }
  } else {
    for(int c = 0; c < m->col; ++c) {
      for(int r = 0; r < m->row; ++r) {
	sum += matrix_val(m, r, c);
      }
    }
  }
  return sum;
}

static p_tree_node _bst_random_node_iteration(p_tree_node root, int random){
  p_tree_node ret = NULL;
  do {
    if(root == NULL) break;
    if(random == 0) {
      ret = root;
      break;
    }

    if(random <= root->left_num)
      ret = _bst_random_node_iteration(root->left, random -1);
    else
      ret = _bst_random_node_iteration(root->right, random - 1 - root->left_num);
  }while(0);

  return ret;
}

static p_tree_node _bst_random_node(p_tree_node bst){
  p_tree_node ret = NULL;
  do{
    if(bst == NULL) break;

    unsigned size = 1 + bst->left_num + bst->right_num;

    int random = rand()%size;
    random = (random + 1) %size;

    if(random == 0) {
      ret = bst;
      break;
    }

    if(random <= bst->left_num)
      ret = _bst_random_node_iteration(bst->left, random -1);
    else
      ret = _bst_random_node_iteration(bst->right, random - 1 - bst->left_num);
  }while(0);
  return ret;
}

static int _get_path_sum(p_tree_node tree, int sum, int target, phashtable r_sum) {
  int num = 0;
  do {
    if(tree == NULL) break;
    int running_sum = sum + tree->val;
    
    if(hashtable_lookup_map(r_sum, running_sum) == NULL) {
      int occourts = 1;
      hashtable_insert_map(r_sum, running_sum, &occourts, sizeof(int));
    } else {
      int* occourts = hashtable_lookup_map(r_sum, running_sum);
      (*occourts)++;
    }
    int* occourts = hashtable_lookup_map(r_sum, running_sum-target);
    if(occourts != NULL)
      num = *occourts;
    num += _get_path_sum(tree->left, running_sum, target, r_sum);
    num += _get_path_sum(tree->right, running_sum, target, r_sum);

    occourts = hashtable_lookup_map(r_sum, running_sum);
    (*occourts)--;
  }while(0);
  return num;
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
    assert(graph_routable_dfs(g, hset, 0, 3));
    assert(hashtable_empty(hset));

    p_list q = list_create(LIST_TYPE_INTEGER);
    list_push_back_integer(q, 0);
    assert(graph_routable_bfs(g, q, 3, hset));
    hashtable_free(hset);
    list_free(q);
    assert(hashtable_empty(hset));
    
    assert(!graph_routable_dfs(g, hset, 3, 0));
    assert(hashtable_empty(hset));

    list_push_back_integer(q, 3);
    assert(!graph_routable_bfs(g, q, 0, hset));
    hashtable_free(hset); assert(hashtable_empty(hset));
    list_free(q);
        
    assert(!graph_routable_dfs(g, hset, 2, 0));
    assert(hashtable_empty(hset));

    hashtable_free(hset);
    list_free(q);
    free(q);
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
  most_left = most_left->left;
  most_left->val = 4; most_left->left = most_left->right = NULL;
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

void test_common_ancestor() {
    int sort_array[16];
    for(int i = 0; i < 16; ++i)
        sort_array[i] = i;
    p_tree_node bst = create_bst(sort_array, 16);
    assert(validate_bst(bst, (int[]){INT_MIN, INT_MAX}));
    
    p_tree_node p1 = _tree_dfs_search_node(bst, 1);
    p_tree_node p2 = _tree_dfs_search_node(bst, 7);
    assert(p1 && p2);
    assert(!_tree_dfs_search_node(bst, 17));

    p_tree_node ret = _tree_search_common_ancestor(bst, p1, p2);
    assert(ret && ret->val == 4);    
    free_bst(bst);
    return;
}



void test_row_col_traversals() {
  struct timespec tstart={0,0}, tend={0,0};
  struct timespec tstart2={0,0}, tend2={0,0};
  p_matrix p = matrix_create(6400, 6400);
  clock_gettime(CLOCK_MONOTONIC, &tstart);
  sum_matrix(p, false);
  clock_gettime(CLOCK_MONOTONIC, &tend);

  clock_gettime(CLOCK_MONOTONIC, &tstart2);
  sum_matrix(p, true);
  clock_gettime(CLOCK_MONOTONIC, &tend2);

  printf("int 1 %.5f, int 2 %.5f\r\n", ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - 
	 ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec),
	 ((double)tend2.tv_sec + 1.0e-9*tend2.tv_nsec) - 
	 ((double)tstart2.tv_sec + 1.0e-9*tstart2.tv_nsec));
  return;
}

void test_bst_sequences() {
    int sort_array[7];
    for(int i = 0; i < 7; ++i)
        sort_array[i] = i+1;
    p_tree_node bst = create_bst(sort_array, 7);
    assert(validate_bst(bst, (int[]){INT_MIN, INT_MAX}));

    pArrayList ret = _all_arrays(bst);

#ifdef DEBUG
    for(unsigned i = 0; i < ret->size; ++i) {
      p_list p = arraylist_get(ret, i);
      list_dump(p);
    }
#endif
    
    _free_list_in_arraylist(ret);
    free_arraylist(ret);
    free(ret);
    free_bst(bst);
    return;
}

void test_bst_random_node() {
    int sort_array[7];

    for(int i = 0; i < 7; ++i)
        sort_array[i] = i+1;
    p_tree_node bst = create_bst(sort_array, 7);
    assert(validate_bst(bst, (int[]){INT_MIN, INT_MAX}));
    p_tree_node n = _bst_random_node(bst);
    assert(n);
    n = _bst_random_node(bst);
    free_bst(bst);
    return;
}

void test_path_sum()  {
  p_tree_node binary_tree = create_random_tree(63);
  phashtable r_sum = hashtable_create();
  int num = _get_path_sum(binary_tree, 0, 8, r_sum);
  printf("%d\r\n", num);
  free_bst(binary_tree);
  hashtable_free(r_sum);
  return;
}

