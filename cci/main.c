#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "list.h"

void main() {
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
  return;
}
