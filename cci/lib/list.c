#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "list.h"

pnode pushback_list(plist l, char* val) {
  assert(l != NULL);

  pnode n = malloc(sizeof(node));
  n->val = strdup(val);
  n->next = NULL;
  
  if(l->head == NULL) {
    l->head = n;
  } else {
    pnode tmp = l->head;
    while(tmp->next != NULL) tmp = tmp->next;
    tmp->next = n; 
  }
  l->len++;
  return n;
}

plist create_list() {
  plist l = malloc(sizeof(list));
  l->head = NULL;
  l->len = 0;
  return l;
}

void dump_list(plist l) {
  assert(l != NULL);
  pnode tmp = l->head;
  while(tmp != NULL) {
    printf("%s\r\n", tmp->val);
    tmp = tmp->next;
  }
  
  return;
}
void free_list(plist l) {
  assert(l != NULL);
  pnode tmp = l->head;
  while(tmp != NULL) {
    pnode n = tmp->next;
    free(tmp->val);
    free(tmp);
    tmp = n;
  }
  l->head = NULL;
  l->len = 0;
  return;
}

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
