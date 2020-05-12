#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>


#include "list.h"
#include "varray.h"
#include "arraylist.h"
#include "matrixbuilder.h"
#include "hashtable.h"

#include "chapter_one.h"
#include "chapter_two.h"
#include "chapter_three.h"
#include "chapter_four.h"
#include "hard.h"

static p_list create_random_integer_list(unsigned len) {
  p_list l = list_create(LIST_TYPE_INTEGER);
  srand(time(0));
  while(len-- > 0)
    list_push_back_integer(l, rand()%100);

  return l;   
}

static void test_chapter_one(){
  assert(checkdup("abcd") == true);
  assert(checkdup("abcda") == false);
  assert(checkdup("abcd#cea#") == false);

  assert(true == checkpermutation("abba", "bbaa"));
  assert(false == checkpermutation("abba", "bbaae"));
  assert(false == checkpermutation("abbac", "bbaae"));

  char *cstr = malloc(sizeof(char)*32);
  memset(cstr, 0, sizeof(char)*32);
  memcpy(cstr, "this is test", 12);
  printf("%s\r\n", cstr);
  printf("%s\r\n", urlify(cstr));
  free(cstr);

  assert( false == permutationofpalindrome("abca"));
  assert( true == permutationofpalindrome("aaebb"));

  assert( true == checkoneway("pale", "ple"));
  assert( true == checkoneway("pales", "pale"));
  assert( true == checkoneway("pale", "bale"));
  assert( false == checkoneway("pale", "bake"));

  {
    char *compressStr = chapter_one_compress_string("aabbbc");
    assert(strlen(compressStr) == 6 && !strcmp(compressStr, "aabbbc"));
    free(compressStr);
    compressStr = chapter_one_compress_string("aabbbccceeee");
    assert(strlen(compressStr) == strlen("a2b3c3e4") && !strcmp(compressStr, "a2b3c3e4"));
    free(compressStr);
  }

  {
    unsigned int (*matrix)[3] = (unsigned int (*)[3])create_random_matrix(3, 3);
    dump_matrix(matrix, 3, 3);
    chapter_one_rotate_matrix(matrix, 3, 3);
    dump_matrix(matrix, 3, 3);
    free_matrix(matrix);
  }
  return;
}

static void test_chapter_two() {
        /* remove duplicate */ 
    {
      p_list l1 = list_create(LIST_TYPE_INTEGER);
      p_list l2 = list_create(LIST_TYPE_INTEGER);

      list_push_back_integer(l1, 1);
      list_push_back_integer(l1, 5);
      list_push_back_integer(l1, 10);
      list_push_back_integer(l1, 23);
      list_push_back_integer(l1, 19);
      
      list_push_back_integer(l2, 3);
      list_push_back_integer(l2, 6);
      list_push_back_integer(l2, 5);
      list_push_back_integer(l2, 11);
      list_push_back_integer(l2, 22);
      list_push_back_integer(l2, 19);

      remove_dup(l1, l2);
      assert(l2->len == 4);
      list_free(l1);
      free(l1);
      list_free(l2);
      free(l2);
    }

  {
    p_list l = create_random_integer_list(16);
    p_node n1 = list_get(l, 10);
    p_node n2 = reverse_count(l, 6);
    assert(n2 && n2 == n1);
    list_free(l);
    free(l);
  }

  {
    p_list l = create_random_integer_list(16);
    unsigned v1 = list_get_integer_value(l, 16);
    p_node n = list_get(l, 10);
    delete_middle_node(l, n);
    unsigned v2 = list_get_integer_value(l, 15);
    assert(l->len == 15 && v1 == v2);
    list_free(l);
    free(l);
  }

  {
    p_list l = create_random_integer_list(15);
    list_push_back_integer(l, 20);
    partition_list(l, 50);
    assert(l->len == 16);
    p_node n = l->head;
    while(n) {
      if((unsigned long)(n->key) >= 50) break;
      n = n->next;
    }
    assert(n);
    while(n) {
      assert((unsigned long)(n->key) >= 50);
      n = n->next;
    }
    list_free(l);
    free(l);
  }

  {
    p_list l1 = list_create(LIST_TYPE_INTEGER);
    p_list l2 = list_create(LIST_TYPE_INTEGER);

    list_push_back_integer(l1, 2); list_push_back_integer(l1, 1); list_push_back_integer(l1, 6);
    list_push_back_integer(l2, 3); list_push_back_integer(l2, 4); list_push_back_integer(l2, 2);

    p_list sum = sum_list_1(l1, l2);
    assert(sum->len == 3 && list_get_integer_value(sum, 1) == 5 && list_get_integer_value(sum, 2) == 5 && list_get_integer_value(sum, 3) == 8);
    list_free(l1);
    free(l1);
    list_free(l2);
    free(l2);
    list_free(sum);
    free(sum);

    p_list l3 = list_create(LIST_TYPE_INTEGER);
    p_list l4 = list_create(LIST_TYPE_INTEGER);

    list_push_back_integer(l3, 7); list_push_back_integer(l3, 1); list_push_back_integer(l3, 6);
    list_push_back_integer(l4, 5); list_push_back_integer(l4, 9); list_push_back_integer(l4, 2);

    p_list sum2 = sum_list_1(l3, l4);
    assert(list_get_integer_value(sum2, 1) == 2 && list_get_integer_value(sum2, 2) == 1 && list_get_integer_value(sum2, 3) == 9);
    list_free(l3);
    free(l3);
    list_free(l4);
    free(l4);
    list_free(sum2);
    free(sum2);
  }

    {
    p_list l1 = list_create(LIST_TYPE_INTEGER);
    p_list l2 = list_create(LIST_TYPE_INTEGER);

    list_push_back_integer(l1, 2); list_push_back_integer(l1, 1); list_push_back_integer(l1, 6);
    list_push_back_integer(l2, 3); list_push_back_integer(l2, 4); list_push_back_integer(l2, 2);

    p_list sum = sum_list_2(l1, l2);
    assert(sum->len == 3 && list_get_integer_value(sum, 1) == 5 && list_get_integer_value(sum, 2) == 5 && list_get_integer_value(sum, 3) == 8);
    list_free(l1);
    free(l1);
    list_free(l2);
    free(l2);
    list_free(sum);
    free(sum);

    p_list l3 = list_create(LIST_TYPE_INTEGER);
    p_list l4 = list_create(LIST_TYPE_INTEGER);

    list_push_back_integer(l3, 7); list_push_back_integer(l3, 1); list_push_back_integer(l3, 6);
    list_push_back_integer(l4, 5); list_push_back_integer(l4, 9); list_push_back_integer(l4, 2);

    p_list sum2 = sum_list_2(l3, l4);
    assert(sum2->len == 4 && list_get_integer_value(sum2, 1) == 1 && list_get_integer_value(sum2, 2) == 3 && list_get_integer_value(sum2, 3) == 0 && list_get_integer_value(sum2, 4) == 8);
    list_free(l3);
    free(l3);
    list_free(l4);
    free(l4);
    list_free(sum2);
    free(sum2);
  }
    
    if(1){
        p_list l1 = list_create(LIST_TYPE_INTEGER);
        list_push_back_integer(l1, 1);
        list_push_back_integer(l1, 5);
        list_push_back_integer(l1, 10);
        list_push_back_integer(l1, 23);
        list_push_back_integer(l1, 19);
        assert(check_palindrome(l1) == false);
        list_free(l1);free(l1);

        p_list l2 = list_create(LIST_TYPE_INTEGER);
        list_push_back_integer(l2, 1);
        list_push_back_integer(l2, 5);
        list_push_back_integer(l2, 10);
        list_push_back_integer(l2, 5);
        list_push_back_integer(l2, 1);
        assert(check_palindrome(l2)== true);
        list_free(l2);free(l2);

        p_list l3 = list_create(LIST_TYPE_INTEGER);
        list_push_back_integer(l3, 1);
        list_push_back_integer(l3, 5);
        list_push_back_integer(l3, 5);
        list_push_back_integer(l3, 1);
        assert(check_palindrome(l3) == true);
        list_free(l3);free(l3);
    }

    if(1) {
        p_list l1 = create_random_integer_list(15);
        p_node n = list_get(l1, 10);
        p_list l2 = create_random_integer_list(16);
        p_node n2 = list_get(l2, 16);
        assert(n2->next == NULL);
        n2->next = n;
        list_update_size(l2);
        assert(l2->len == 22);
        assert(check_intersection(l1, l2) == n);

        n2->next = NULL;
        list_update_size(l2);
        assert(l2->len == 16);
        
        list_free(l1); free(l1);
        list_free(l2); free(l2);
    }

    
}

static void test_chapter_three () {
  if(1) {
    test_multiple_stacks();
    test_myqueue();
    test_sort_stack();
    test_animal_sheleter();
  }
}

static void test_chapter_four () {
  if(1) {
    test_route_search();
    test_minimal_tree();
    test_list_of_depths();
    test_check_balanced();
    test_validate_bst();
    test_find_successor();
    test_build_order();
    test_common_ancestor();
    test_bst_sequences();
    test_bst_random_node();
    test_path_sum();
#ifdef DEBUG
    test_row_col_traversals(); // verify the cache line performance
#endif
  }
}
static void test_hard() {
  {
    unsigned a = 10; unsigned b = 20;
    swap_unsigned(&a, &b);
    assert(a == 20 && b == 10);
  }
}
int main() {
  srand(time(0));
  list_test();
  unsigned int token;
  memcpy(&token, "    ", 4);
  unsigned int val;
  memcpy(&val, "aa b", 4);

  pvarray va = create_varray();
  assert(va != NULL);
  modifyat_varray(va, 30, 'c');
  free_varray(va);
  free(va);

  stringbuilder_test();
  hashtable_test();
  
  test_chapter_one();
  test_chapter_two();
  test_chapter_three();
  test_chapter_four();
  test_hard();
  return 0;
}
