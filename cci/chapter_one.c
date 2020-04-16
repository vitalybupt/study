#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "chapter_one.h"

#include "arraylist.h"
bool checkdup(const char* cstr) {
  bool ret = true;
  if(strlen(cstr) > 128) return false;
  unsigned int dict[4] = {0};

  for(unsigned int i = 0; i<strlen(cstr); ++i) {
    unsigned int element = (unsigned int)cstr[i]/32;
    unsigned int pos = (unsigned int)cstr[i]%32;
    
    if((dict[element] >> pos) & 0x1) {
      ret =  false;
      break;
    }
    else{
      dict[element] |= (0x1 << pos);
    }
  }
  return ret;
}

bool checkpermutation(const char* s1, const char* s2) {
  bool ret = true;

  if(strlen(s1) != strlen(s2)) return false;

  unsigned int *dict = malloc(sizeof(unsigned int)*128);
  memset(dict, 0, sizeof(unsigned int)*128);

  for(unsigned int i = 0; i < strlen(s1); ++i) {
    dict[(unsigned int)s1[i]]++;
  }
  for(unsigned int i =0; i < strlen(s2); ++i) {
    if(0 == dict[(unsigned int)s2[i]]) {
      ret = false;
      break;
    } else {
      dict[(unsigned int)s2[i]]--;
    }
  }

  free(dict);
  return ret;  
}

char* urlify(char* s) {
  assert(s != NULL);

  unsigned int count = 0;

  for(unsigned int i = 0; i< strlen(s); ++i) {
    if(s[i] == ' ') count++;
  }

  unsigned int substrlen = 0;
  char *scanner = s + strlen(s) -1;

  while(scanner != s) {
    if(*scanner == ' ') {
      memmove(scanner+1+count*2,scanner+1, substrlen);
      *(scanner+count*2-2) = '%';  *(scanner+count*2-1) = '2';  *(scanner+count*2) = '0';
      count--; substrlen=0;
    } else{
      substrlen++;
    }
    scanner--;
  }
  return s;
}

bool permutationofpalindrome(const char* s) {
  unsigned int *dict = malloc(sizeof(unsigned int)*128);
  memset(dict, 0, sizeof(unsigned int)*128);
  unsigned int count = 0;

  for(unsigned int i = 0; i < strlen(s); ++i) {
    unsigned int index = (unsigned int)s[i];
    ++dict[index];
    if(dict[index] & 0x1) {
      count++;
    } else {
      count--;
    }
  }

  free(dict);
  if(count > 1) return false;

  return true;
}

static bool checkremove(const char* s1, const char* s2) {
  const char* p1 = s1; const char* p2 = s2;
  while(*p1 != '\0') {
    if(*p1 == *p2) {
      ++p1; ++p2;
      continue;
    }
    p1++;
    return strcmp(p1, p2) == 0;
  }
  return false;
}

static bool checkreplace(const char* s1, const char* s2) {
  const char* p1 = s1; const char* p2 = s2;
  while(*p1 != '\0') {
    if(*p1 == *p2) {
      ++p1; ++p2;
      continue;
    }
    p1++; p2++;
    return strcmp(p1, p2) == 0;
  }
  return false;
}

bool checkoneway(const char* s1, const char* s2) {
  if(strlen(s1) - strlen(s2) == 1)
    return checkremove(s1, s2);
  else if(strlen(s2) - strlen(s1) == 1)
    return checkremove(s2, s1);
  else if(strlen(s1) == strlen(s2))
    return checkreplace(s1, s2);
  return false;
}

char* chapter_one_compress_string(const char*s) {
    pArrayList compressStr = create_arraylist();
    unsigned int subcount = 1;
    
    for(unsigned int i = 0; i < strlen(s); ++i) {
        if(s[i+1] == s[i]) {
            subcount++;
            continue;
        }
        char tmp[32];
        sprintf(tmp, "%c%u", s[i], subcount);
        append_arraylist(compressStr, tmp);
        subcount = 1;
    }
    if(getlen_arraylist(compressStr) >= strlen(s)) {
        free_arraylist(compressStr);
        free(compressStr);
        return strdup(s);
    }
    char *str = tostring_arraylist(compressStr);
    free_arraylist(compressStr);
    free(compressStr);
    return str;
}

#define _matrix_index(m, r, c, d) (unsigned*)(m+(r*d+c))
static void swap_matrix_element(unsigned *a, unsigned *b){
  *a = (*a)^(*b);
  *b = (*a)^(*b);
  *a = (*a)^(*b);
}

void chapter_one_rotate_matrix(void* matrix, unsigned row, unsigned d) {
  unsigned *m = (unsigned *)matrix;

  for(unsigned r = 0; r < row; ++r) {
    for(unsigned c = r+1; c < d; ++c){
      swap_matrix_element(_matrix_index(m,r,c,d), _matrix_index(m,c,r,d));
    }
  }

  for(unsigned r = 0; r < row; ++r) {
    for(unsigned c = 0; c < d/2; ++c ) {
      swap_matrix_element(_matrix_index(m,r,c,d), _matrix_index(m,r,d-c-1,d));
    }
  }

  return;
}
