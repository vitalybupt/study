#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "cci_utils.h"
#include "chapter_nine.h"
#include "arraylist.h"
#include "matrixbuilder.h"
#include "list.h"

/* macro and type defination */
typedef struct {
  int r;
  int c;
} *pair;

/* declaration of private function */
static pair pair_create(int r, int c);
static int _triple_step(int n);
static pArrayList _find_maze_path(p_matrix maze, int row, int col);
#ifdef DEBUG
static void _dump_maze_path(pArrayList paths);
#endif

/* defination of private function */
static int _triple_step(int n) {
  if(n <= 0) return 0;
  if(n == 1) return 1;
  if(n == 2) return 2;
  if(n == 3) return 4;
  int a = 1, b = 2, c = 4;
  for(int i = 3; i < n; ++i) {

    int tmp = a + b + c;

    a = b;
    b = c;
    c = tmp;
  }
  return c;
}

static pair pair_create(int r, int c) {
  pair p = malloc(sizeof(int)*2);
  p->r = r;
  p->c = c;
  return p;
}

static pArrayList _find_maze_path(p_matrix maze, int row, int col) {
  pArrayList paths = create_arraylist();

  do {
    if(row < 0 || col < 0 || matrix_val(maze, row, col) == 1)
      break;

    dbg_printf("visit grid (%d,%d)\r\n", row, col);
    if(row == 0 && col == 0) {
      pair cur = pair_create(row, col);
      p_list p = list_create(LIST_TYPE_GENERIC);
      list_push_front_generic(p, cur);
      arraylist_append_generic(paths, p);
      break;
    }

    if(row > 0) {
      pArrayList sub_paths = _find_maze_path(maze, row - 1, col);
      for(int i = 0; i < sub_paths->size; ++i) {
	pair cur = pair_create(row, col);
	p_list p = arraylist_get(sub_paths, i);
	list_push_back_generic(p, cur);
	arraylist_append_generic(paths, p);
      }
      free(sub_paths);
    }

    if(col > 0) {
      pArrayList sub_paths = _find_maze_path(maze, row, col - 1);
      for(int i = 0; i < sub_paths->size; ++i) {
	pair cur = pair_create(row, col);
	p_list p = arraylist_get(sub_paths, i);
	list_push_back_generic(p, cur);
	arraylist_append_generic(paths, p);
      }
      free(sub_paths);
    }
  } while(0);
  
  return paths;  
}

#ifdef DEBUG
static void _dump_maze_path(pArrayList paths) {
  for(int i = 0; i < paths->size; ++i) {
    dbg_printf("find path [%d]: ", i);
    p_list p = arraylist_get(paths, i);
    int p_len = list_get_length(p);
    for(int j = 1; j <= p_len; ++j) {
      pair n = list_get_generic(p, j);
      if(j == p_len)
	dbg_printf("(%d,%d)\r\n", n->r, n->c);
      else
	dbg_printf("(%d,%d)->", n->r, n->c);
    }
  }
  return;
}
#endif

static void _free_maze_path(pArrayList paths) {
  for(int i = 0; i < paths->size; ++i) {
    p_list p = arraylist_get(paths, i);
    int p_len = list_get_length(p);
    for(int j = 1; j <= p_len; ++j) {
      pair n = list_get_generic(p, j);
      free(n);
    }
    list_free(p);
  }
  free_arraylist(paths);
  free(paths);
  return;
}

/* defination of public function*/
void test_triple_step() {
  assert(_triple_step(4) == 7);
  return;
}

void test_robot_in_grid() {
  {
    p_matrix maze = matrix_create(2, 2);
    pArrayList paths = _find_maze_path(maze, 1, 1);
    assert(paths && paths->size == 2);
#ifdef DEBUG
    _dump_maze_path(paths);
#endif
    _free_maze_path(paths);
  
    /* matrix_set(maze, 1, 0, 1); */
    /* assert(matrix_val(maze, 1, 0) == 1); */
    /* pArrayList paths2 = _find_maze_path(maze, 1, 1); */
    /* assert(paths2 && paths2->size == 1); */
    /* _free_maze_path(paths2); */
    /* free_matrix(maze); */
  }

  if(0){
    p_matrix maze = matrix_create(4, 3);
    matrix_set(maze, 2, 1, 1);
    assert(matrix_val(maze, 2, 1) == 1);
    pArrayList paths = _find_maze_path(maze, 3, 2);
#ifdef DEBUG
    _dump_maze_path(paths);
#endif
    assert(paths && paths->size == 4);
    _free_maze_path(paths);
    free_matrix(maze);
  }
  return;
}
