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
#include "hard.h"

static plist create_random_integer_list(unsigned len) {
  plist l = list_create(LIST_TYPE_INTEGER);
  srand(time(0));
  while(len-- > 0)
    list_push_integer(l, rand()%100);

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

static void test_chapter_two(){
  {
    
    plist l1 = list_create(LIST_TYPE_INTEGER);
    plist l2 = list_create(LIST_TYPE_INTEGER);

    list_push_integer(l1, 1);
    list_push_integer(l1, 5);
    list_push_integer(l1, 10);
    list_push_integer(l1, 23);
    list_push_integer(l1, 19);

    list_push_integer(l2, 3);
    list_push_integer(l2, 6);
    list_push_integer(l2, 5);
    list_push_integer(l2, 11);
    list_push_integer(l2, 22);
    list_push_integer(l2, 19);

    remove_dup(l1, l2);
    assert(l2->len == 4);
    list_free(l1);
    free(l1);
    list_free(l2);
    free(l2);
  }

  {
    plist l = create_random_integer_list(16);
    pnode n1 = list_get(l, 10);
    pnode n2 = reverse_count(l, 6);
    assert(n2 && n2 == n1);
    list_free(l);
    free(l);
  }

  {
    plist l = create_random_integer_list(16);
    unsigned v1 = list_get_integer_value(l, 16);
    pnode n = list_get(l, 10);
    delete_middle_node(l, n);
    unsigned v2 = list_get_integer_value(l, 15);
    assert(l->len == 15 && v1 == v2);
    list_free(l);
    free(l);
  }

  {
    plist l = create_random_integer_list(15);
    list_push_integer(l, 20);
    partition_list(l, 50);
    assert(l->len == 16);
    pnode n = l->head;
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
}

static void test_hard() {
  {
    unsigned a = 10; unsigned b = 20;
    swap_unsigned(&a, &b);
    assert(a == 20 && b == 10);
  }
}
int main() {
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
  test_hard();
  return 0;
}
