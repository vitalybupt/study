#include <stdio.h>
#include <stdlib.h>
#include "uolist.h"
static pUoNode findPos(pUoList list, pUoNode node);

// find the first element with value larger or equal to value in node
static pUoNode findPos(pUoList list, pUoNode node){
  if(list->length == 0) return 0; //MUST not called in case list is empty
  pUoNode pos = list->head;
  do {
    if(list->cmp(pos->data, node->data) < 0) { // the element less than value in node
      if(pos != list->tail) // move to next element
	pos = pos->next;
      else { //special case: we find the new tail
	return NULL;
      }
      continue; 
    }
    // find the element we should insert the node as the previous
    return pos;
  } while(1);
}

unsigned int addList(pUoList list, pUoNode node) {
  unsigned int ret = 0;
  if(list->length == 0){ // the first element
    list->length =1;
    list->head = list->tail = node;
    return ret;
  }
  pUoNode pos = findPos(list, node);
  if(pos == list->head) { //find the new head
    node->prev = pos->prev;
    node->next = pos;
    pos->prev = node;
    list->head = node;
  } else if(pos == NULL) { // find the new tail
    node->prev = list->tail;
    node->next = NULL;
    list->tail->next = node;
    list->tail = node;
  } else {
    node->prev = pos->prev;
    node->next = pos;
    pos->prev->next = node;
    pos->prev = node;
  }
  list->length++;
  if(list->length > list->maxLength) {
    pUoNode remove = list->tail;
    list->tail = remove->prev;
    list->tail->next = NULL;
    free(remove->data);
    free(remove);
  }
  return ret;
}

void dumpList(pUoList list) {
  if(list->length == 0) {
    printf("empty list\r\n");
    return;
  }
  printf("begin dump list:\r\n");
  pUoNode pos = list->head;
  do {
    printf("node %p, prev is %p, next is %p\r\n", pos, pos->prev,pos->next);
    if(pos != list->tail) {
      pos = pos->next;
      continue;
    }
    else
      break;
  } while(1);
  printf("\r\n");
  return;
}
