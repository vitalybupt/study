#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "cci_utils.h"
#include "chapter_nine.h"
#include "arraylist.h"
#include "varray.h"
#include "matrixbuilder.h"
#include "stack.h"
#include "list.h"

/* macro and type defination */
typedef struct pair{
  int r;
  int c;
  int count;
} *pair;

typedef enum COLOR {
      GREEN,
      YELLOW,
      RED
} COLOR;

/* declaration of private function */
static pair pair_create(int r, int c);
static int _triple_step(int n);
static p_arraylist _find_maze_path(p_matrix maze, int row, int col);
static int _find_magic_index_1(int *array, int low, int high);
static p_list _find_magic_index_2(int *array, int low, int high);
static p_arraylist _get_powerset( p_list set );
static int _recursive_multiple(int m, int n);
static p_stack* _create_hanoi(int size);
static void _destroy_hanoi(p_stack* tower);
static void _move_hanoi(p_stack *towers, int height, int f, int t, int a);
static p_list _get_no_unique_perms(const char *s);
static p_list _get_unique_perms(const char *s);
static void _paint_fill(p_matrix table, int left, int right, int up, int down, int x, int y, COLOR new_color);
static int _sum_coin(int cur, int* rem, int size, int pos, int count);
#ifdef DEBUG
static void _dump_maze_path(p_arraylist paths);
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
  pair p = malloc(sizeof(struct pair));
  p->r = r;
  p->c = c;
  p->count = 1;
  return p;
}

static pair pair_ref(pair p) {
  p->count++;
  return p;
}

static void pair_release(pair p) {
  p->count--;
  
  if(p->count == 1)
    free(p);
  return;
}

static p_arraylist _find_maze_path(p_matrix maze, int row, int col) {
    p_arraylist paths = arraylist_create();

    do {
        if(row < 0 || col < 0 || matrix_val(maze, row, col) == 1)
            break;
        
        dbg_printf("visit grid (%d,%d)\r\n", row, col);
        pair cur = pair_create(row, col);
        if(row == 0 && col == 0) {
            p_list p = list_create(LIST_TYPE_GENERIC);
            list_push_front_generic(p, pair_ref(cur));
            arraylist_append_generic(paths, p);
            break;
        }

        if(row > 0) {
          p_arraylist sub_paths = _find_maze_path(maze, row - 1, col);

          while(!arraylist_empty(sub_paths)) {
            p_list p = arraylist_pop_back_generic(sub_paths);
            list_push_back_generic(p, pair_ref(cur));
            arraylist_append_generic(paths, p);
          }
          arraylist_free(sub_paths);
          free(sub_paths);
        }

        if(col > 0) {
            p_arraylist sub_paths = _find_maze_path(maze, row, col - 1);
            while(!arraylist_empty(sub_paths)) {
                p_list p = arraylist_pop_back_generic(sub_paths);
                list_push_back_generic(p, pair_ref(cur));
                arraylist_append_generic(paths, p);
            }
            arraylist_free(sub_paths);
            free(sub_paths);
        }
    } while(0);
    
    return paths;  
}

#ifdef DEBUG
static void _dump_maze_path(p_arraylist paths) {
  for(int i = 0; i < paths->size; ++i) {
    dbg_printf("find path [%d]: ", i);
    p_list p = arraylist_peak(paths, i);
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

static void _free_maze_path(p_arraylist paths) {
  while(!arraylist_empty(paths)) {
    p_list p = arraylist_pop_back_generic(paths);
    int p_len = list_get_length(p);
    for(int j = 1; j <= p_len; ++j) {
      pair n = list_get_generic(p, j);
      pair_release(n);
    }
    list_free(p);
    free(p);
  }
  arraylist_free(paths);
  free(paths);
  return;
}

int _find_magic_index_1(int *array, int low, int high) {
  int ret = -1;
  do {
    if(low > high) break;

    if(array[low] == low){
      ret = low;
      break;
    }
    if(array[low] > low) break;

    if(low == high) break;

    if(array[high] == high) {
      ret = high;
      break;
    }
    if(array[high] < high) break;

    int mid = (low + high)/2;
    if(array[mid] == mid) {
      ret = mid;
      break;
    }

    if(array[mid] < mid) {
      ret = _find_magic_index_1(array, mid + 1, high);
      break;
    } else {
      ret = _find_magic_index_1(array, low, mid - 1);
      break;
    }
  }while(0);
  
  return ret;
}

static p_list  _find_magic_index_2(int *array, int low, int high) {
  p_list indices = list_create(LIST_TYPE_INTEGER);
  
  do {
    if(low > high) break;

    if(array[low] == low) {
      dbg_printf("find magic %d\r\n", low);
      list_push_back_integer(indices, low);
    }
    if(low == high) break;
    
    if(array[low] > low)
      low = array[low];
    else
      low++;

    if(array[high] == high) {
      dbg_printf("find magic %d\r\n", high);
      list_push_back_integer(indices, high);
    }
    if(array[high] < high)
      high = array[high];
    else
      high--;
    
    if(low == high) {
      if(array[low] == low) {
        dbg_printf("find magic %d\r\n", low);
        list_push_back_integer(indices, low);
      }
        break;
    }
    
    int mid = (low + high)/2;
    p_list l = NULL, r = NULL;
    
    if(array[mid] == mid) {
      list_push_back_integer(indices, mid);
      dbg_printf("recursive search range %d ~ %d, %d ~ %d\r\n", low, mid -1, mid + 1, high);
      l = _find_magic_index_2(array, low, mid -1);
      r = _find_magic_index_2(array, mid + 1, high);
    } else if(array[mid] < mid) {
      dbg_printf("recursive search range %d ~ %d, %d ~ %d\r\n", low, array[mid], mid + 1, high);
      l = _find_magic_index_2(array, low, array[mid]);
      r = _find_magic_index_2(array, mid + 1, high);
    } else if(array[mid] > mid) {
      dbg_printf("recursive search range %d ~ %d, %d ~ %d\r\n", low, mid - 1, array[mid], high);
      l = _find_magic_index_2(array, low, mid - 1);
      r = _find_magic_index_2(array, array[mid], high);
    }

    while(!list_empty(l)) {
      dbg_printf("find magic %ld\r\n", list_begin_integer(l));
      list_push_back_integer(indices, list_pop_front_integer(l));
    }
    while(!list_empty(r)) {
      dbg_printf("find magic %ld\r\n", list_begin_integer(r));
      list_push_back_integer(indices, list_pop_front_integer(r));
    }
    free(l);
    free(r);
  }while(0);

  return indices;
}

static p_arraylist _get_powerset( p_list set) {
    p_arraylist powerset = arraylist_create();
    do {
        if(list_empty(set)) break;

        long head = list_pop_front_integer(set);
        p_arraylist subset = _get_powerset(set);

        if(arraylist_empty(subset)) {
            p_list t1 = list_create(LIST_TYPE_INTEGER);
            list_push_back_integer(t1, head);
            p_list t2 = list_create(LIST_TYPE_INTEGER);
            arraylist_append_generic(powerset, t1);
            arraylist_append_generic(powerset, t2);
        } else {
            while(!arraylist_empty(subset)) {
                p_list t1 = arraylist_pop_back_generic(subset);
                p_list t2 = list_clone(t1);
                list_push_front_integer(t2, head);
                arraylist_append_generic(powerset, t1);
                arraylist_append_generic(powerset, t2);
            }
        }

        arraylist_free(subset);
        free(subset);
        break;
    } while(0);

    return powerset;
}

static int _recursive_multiple(int m, int n) {
    int ret = -1;
    do {
        if(n == 0) {
            ret = 0;
            break;
        } else if(n == 1) {
            ret = m;
            break;
        } else if(n == 2) {
            ret = m << 1;
            break;
        }
          
        int d = n >> 1;
        int r = _recursive_multiple(m, d);
        ret = r + r;
        if(n %2 == 1)
            ret += m;
        break;
    } while(0);
    return ret;
}

static p_stack* _create_hanoi(int size) {
  p_stack* towers = calloc(sizeof(p_stack), 3);
  for(int i = 0; i < 3; ++i) {
    towers[i] = stack_create(size);
  }
  
  for(int i = size; i > 0; --i) {
    stack_push(towers[0], i);
  }
  return towers;
}

static void _destroy_hanoi(p_stack* tower) {
  for(int i = 0; i < 3; ++i) {
    stack_free(tower[i]);
  }
  free(tower);
  return;
}

static void _move_hanoi(p_stack *towers, int height, int f, int t, int a) {
  if(height <= 0) return;
  int plate = 0;
  
  if(height == 1){
    stack_pop(towers[f], &plate);
    stack_push(towers[t], plate);
    return;
  }

  _move_hanoi(towers, height - 1, f, a, t);
  _move_hanoi(towers, 1, f, t, a);
  _move_hanoi(towers, height -1, a, t, f);
  return;
}

static p_list _get_unique_perms(const char *s) {
  p_list perms = list_create(LIST_TYPE_GENERIC);
  do {
    if(s == NULL || strlen(s) == 0 ) {
      break;
    } else if(strlen(s) == 1) {
      p_arraylist perm = arraylist_create();
      arraylist_append_string(perm, s);
      list_push_front_generic(perms, perm);
      break;
    } else {
      p_list sub_perms = _get_unique_perms( &s[1]);
      do {
	char tmp[2] = {s[0], '\0'};
	p_arraylist perm = list_pop_front_generic(sub_perms);
	int size = arraylist_get_size(perm);
	for(int i = 0; i <= size; ++i) {
	  p_arraylist new_perm = arraylist_clone(perm);
	  arraylist_insert_string(new_perm, i, tmp);
	  list_push_front_generic(perms, new_perm);
	}
	arraylist_free(perm);
	free(perm);
      } while(!list_empty(sub_perms));
      free(sub_perms);
    }
  } while(0);
  return perms;
}

static void _add_parens(p_list list, int left_rem, int right_rem, p_varray str) {
  do {
    if(left_rem < 0 || right_rem < 0) break;

    if(left_rem == 0) {
      if(right_rem != 0) {
	do {
	  varray_append_char(str, ')');
	} while(--right_rem);
      }
      list_push_back_generic(list, str);
      break;
    }

    if(left_rem < right_rem) {
      p_varray new_str = varray_clone(str);
      varray_append_char(new_str, ')');
      _add_parens(list, left_rem , right_rem-1, new_str);
    }

    varray_append_char(str, '(');
    _add_parens(list, left_rem-1 , right_rem, str);
  } while(0);
  
  return;  
}

static p_list _get_valid_parens(int num) {
  p_list list = list_create(LIST_TYPE_GENERIC);

  do {
    if( num == 0 ) break;
    p_varray str = varray_create();
    _add_parens(list, num, num, str);
  } while(0);

  return list;
}

static p_list _get_no_unique_perms(const char *s) {
  p_list perms = list_create(LIST_TYPE_GENERIC);
  do {
    if(s == NULL || strlen(s) == 0 ) {
      break;
    } else if(strlen(s) == 1) {
      p_arraylist perm = arraylist_create();
      arraylist_append_string(perm, s);
      list_push_front_generic(perms, perm);
      break;
    } else {
      p_list sub_perms = _get_no_unique_perms( &s[1]);
      do {
	char tmp[2] = {s[0], '\0'};
	p_arraylist perm = list_pop_front_generic(sub_perms);
	int size = arraylist_get_size(perm);
	for(int i = 0; i <= size; ++i) {
	  if(i != 0 && ((char*)arraylist_peak(perm, i-1))[0] == s[0])
	    continue;
	  p_arraylist new_perm = arraylist_clone(perm);
	  arraylist_insert_string(new_perm, i, tmp);
	  list_push_front_generic(perms, new_perm);
	}
	arraylist_free(perm);
	free(perm);
      } while(!list_empty(sub_perms));
      free(sub_perms);
    }
  } while(0);
  return perms;
}

static void _paint_fill(p_matrix table, int left, int right, int up, int down, int x, int y, COLOR new_color) {
  do {
    assert( left <= x && x <= right && up <= y && y <= down);

    COLOR old_color = matrix_val(table, x, y);
    matrix_set(table, x, y, new_color);

    if(x>left && matrix_val(table, x-1, y) == (int)old_color) {
      _paint_fill(table, left, x-1, up, down, x-1, y, new_color);
    }

    if(y>up && matrix_val(table, x, y-1) == (int)old_color) {
      _paint_fill(table, x, right, up, y-1, x, y-1, new_color);
    }

    if(x<right && matrix_val(table, x+1, y) == (int)old_color) {
      _paint_fill(table, x+1, right, y, down, x+1, y, new_color);
    }

    if(y<down && matrix_val(table, x, y+1) == (int)old_color) {
      _paint_fill(table, x, x, y+1, down, x, y+1, new_color);
    }
  } while(0);

  return;
}

static int _sum_coin(int cur, int* rem, int size, int pos, int count) {
  if(count < 0)
    return 0;
  if(count == 0)
    return 1;

  if(pos == size) {
    if(count%cur == 0)
      return 1;
    else
      return 0;
  }

  int ways = 0;

  for(int i = 0; i <= count/cur; ++i) {
    ways += _sum_coin(rem[pos], rem, size, pos+1, count-i*cur);
  }

  return ways;
  
}

/* defination of public function*/
void test_triple_step() {
  assert(_triple_step(4) == 7);
  return;
}

void test_robot_in_grid() {
  {
    p_matrix maze = matrix_create(2, 2);
    p_arraylist paths = _find_maze_path(maze, 1, 1);
    assert(paths && paths->size == 2);
#ifdef DEBUG
    _dump_maze_path(paths);
#endif
    _free_maze_path(paths);
  
    matrix_set(maze, 1, 0, 1);
    assert(matrix_val(maze, 1, 0) == 1);
    p_arraylist paths2 = _find_maze_path(maze, 1, 1);
    assert(paths2 && paths2->size == 1);
    _free_maze_path(paths2);

    matrix_free(maze);
  }

  if(1){
    p_matrix maze = matrix_create(4, 3);
    matrix_set(maze, 2, 1, 1);
    assert(matrix_val(maze, 2, 1) == 1);
    p_arraylist paths = _find_maze_path(maze, 3, 2);
#ifdef DEBUG
    _dump_maze_path(paths);
#endif
    assert(paths && paths->size == 4);
    _free_maze_path(paths);
    matrix_free(maze);
  }
  return;
}

void test_magic_index() {
  int sort_array1[] = {1, 2, 3, 5, 6};
  assert(_find_magic_index_1(sort_array1, 0, 4) == -1);

  int sort_array2[] = {-2, 1, 2, 5, 6};
  assert(_find_magic_index_1(sort_array2, 0, 4) == 2);

  int sort_array3[] = {-2, 0, 1, 2, 4};
  assert(_find_magic_index_1(sort_array3, 0, 4) == 4);

  int sort_array4[] = {-1, -1, 2, 2, 2, 5};
  p_list magic_indices = _find_magic_index_2(sort_array4, 0, 5);
  assert(list_get_length(magic_indices) == 2);
  assert(list_get_integer_value(magic_indices, 1) == 5);
  assert(list_get_integer_value(magic_indices, 2) == 2);
  list_free(magic_indices);
  free(magic_indices);
    
  return;
}

void test_powerset() {
    p_list set = list_create(LIST_TYPE_INTEGER);
    list_push_back_integer(set, 1); list_push_back_integer(set, 3); list_push_back_integer(set, 5);
    p_arraylist powerset = _get_powerset(set);
    assert(arraylist_get_size(powerset) == 8);
    
    while(!arraylist_empty(powerset)) {
        p_list t = arraylist_pop_back_generic(powerset);
        list_free(t);
        free(t);
    }

    p_list set2 = list_create(LIST_TYPE_INTEGER);
    list_push_back_integer(set2, 1); list_push_back_integer(set2, 3); list_push_back_integer(set2, 5);
    list_push_back_integer(set2, 7); list_push_back_integer(set2, 9);
    p_arraylist powerset2 = _get_powerset(set2);
    assert(arraylist_get_size(powerset2) == 32);
    
    while(!arraylist_empty(powerset2)) {
        p_list t = arraylist_pop_back_generic(powerset2);
        list_free(t);
        free(t);
    }
    
    arraylist_free(powerset);
    free(powerset);
    arraylist_free(powerset2);
    free(powerset2);

    list_free(set);
    free(set);
    list_free(set2);
    free(set2);
    
    return;
}

void test_recursive_multiply() {
    assert(_recursive_multiple(13, 8) == 104);
    assert(_recursive_multiple(13, 1) == 13);
    return;
}

void test_hanoi() {
  p_stack *towers = _create_hanoi(1);
  _move_hanoi(towers, 1, 0, 2, 1);
  _destroy_hanoi(towers);

  towers = _create_hanoi(3);
  _destroy_hanoi(towers);
  
  return;
}

void test_get_unique_perms() {
  p_list perms = _get_unique_perms("abcd");
  assert(list_get_length(perms) == 24);
  do {
    p_arraylist p = list_pop_front_generic(perms);
    arraylist_free(p);
    free(p);
  } while(!list_empty(perms));
  list_free(perms);
  free(perms);

  return;
}


void test_get_no_unique_perms() {
  p_list perms = _get_no_unique_perms("aabcd");
  assert(list_get_length(perms) == 96);
  do {
    p_arraylist p = list_pop_front_generic(perms);
    arraylist_free(p);
    free(p);
  } while(!list_empty(perms));
  list_free(perms);
  free(perms);
  
  return;
}

void test_valid_parens() {
  p_list p = _get_valid_parens(2);
  assert(!list_empty(p) && list_get_length(p) == 2);
  do {
    p_varray str = list_pop_front_generic(p);
    //printf("%s\r\n", varray_get_string(str));
    varray_free(str);
    free(str);
  } while (!list_empty(p));

  list_free(p);
  free(p);

  p = _get_valid_parens(3);
  assert(!list_empty(p) && list_get_length(p) == 5);
  do {
    p_varray str = list_pop_front_generic(p);
    //printf("%s\r\n", varray_get_string(str));
    varray_free(str);
    free(str);
  } while (!list_empty(p));

  list_free(p);
  free(p);

}

void test_pain_fill() {
  p_matrix table = matrix_create_random(16, 16, 3);
  matrix_set(table, 7, 6, GREEN);
  dump_matrix(table);
  _paint_fill(table, 0, 15, 0, 15, 7, 6, RED);
  dump_matrix(table);

  matrix_free(table);
}

void test_sum_coin() {
  int rem[] = {25, 10, 5, 1};

  assert(_sum_coin(25, rem, 4, 1, 4) == 1);
  assert(_sum_coin(25, rem, 4, 1, 5) == 2);
  assert(_sum_coin(25, rem, 4, 1, 9) == 2);
  assert(_sum_coin(25, rem, 4, 1, 10) == 4);
  assert(_sum_coin(25, rem, 4, 1, 14) == 4);
  assert(_sum_coin(25, rem, 4, 1, 15) == 6);
}
