#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "list.h"
#include "varray.h"
#include "arraylist.h"
#include "matrixbuilder.h"
#include "chapter_one.h"
#include "hard.h"

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

  char *compressStr = chapter_one_compress_string("aabbbc");
  printf("%s\r\n", compressStr);
  free(compressStr);
  compressStr = chapter_one_compress_string("aabbbccceeee");
  printf("%s\r\n", compressStr);
  free(compressStr);

  unsigned int (*matrix)[3] = (unsigned int (*)[3])create_random_matrix(3, 3);
  dump_matrix(matrix, 3, 3);
  chapter_one_rotate_matrix(matrix, 3, 3);
  dump_matrix(matrix, 3, 3);
  free_matrix(matrix);

  return;
}

static void test_hard() {
  {
    unsigned a = 10; unsigned b = 20;
    swap_unsigned(&a, &b);
    assert(a == 20 && b == 10);
  }
}
int main() {
  plist l = create_list();

  char input[] = "test this string";
  char* ptr = strtok(input, " ");
  while(ptr != NULL) {
    pushback_list(l, ptr);
    ptr = strtok(NULL, " ");
  }
  
  dump_list(l);

  free_list(l);
  free(l);

  unsigned int token;
  memcpy(&token, "    ", 4);
  unsigned int val;
  memcpy(&val, "aa b", 4);

  pvarray va = create_varray();
  assert(va != NULL);
  modifyat_varray(va, 30, 'c');
  free_varray(va);
  free(va);

  pArrayList strings = create_arraylist();
  append_arraylist(strings, "this");
  append_arraylist(strings, " is test");
  append_arraylist(strings, " for strings");
  char* cstr_strings = tostring_arraylist(strings);
  printf("%s\r\n", cstr_strings);
  for(int i = 0; i < 17; ++i)
      append_arraylist(strings, "test");
  append_arraylist(strings, "test");
  free(cstr_strings);
  free_arraylist(strings);
  free(strings);
  test_chapter_one();
  test_hard();
  return 0;
}
