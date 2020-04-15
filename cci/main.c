#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "list.h"
#include "varray.h"
#include "arraylist.h"
#include "chapter_one.h"

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

  char *compressStr = compressString("aabbbc");
  printf("%s\r\n", compressStr);
  free(compressStr);
  compressStr = compressString("aabbbccceeee");
  printf("%s\r\n", compressStr);
  free(compressStr);
  
  return;
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
  return 0;
}
