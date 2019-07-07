#include <stdio.h>
#include <stdlib.h>
#include "uolist.h"

// find the first element with value larger or equal to value in node
static pUoNode searchInsert(pUoList list, pUoNode node){
  pUoNode low = list->head;
  pUoNode high = NULL;
  pUoNode slow, fast = list->head;
  do{
    //split into two halves[low, slow, high]
    do{
      slow = slow->next;
      fast = fast->next->next;
    } while(fast != NULL && fast!= high);
    
    if(list->cmp(slow->data, node->data) < 0) {
    low, slow, fast = slow->next;
    } else{
      high = low->prev;
      slow, fast = low;
    }
  } while(list->cmp(slow->data, node->data) <= 0);
  return low;
}


// find the first element with value larger or equal to value in node
static pUoNode findPos(pUoList list, pUoNode node){
  pUoNode pos = list->head;
  do {
    if(pos != NULL && list->cmp(pos->data, node->data) < 0) { // the element less than value in node
      pos = pos->next;
      continue; 
    }
    break;
  } while(1);
  return pos == NULL ? NULL : pos->prev;
}

unsigned int addList(pUoList list, pUoNode node) {
    unsigned int ret = 0;

    if (list->maxLength == 0) {
        return -1;
    }
    if (list->length == 0) { //the first element
        list->length  = 1;
        list->head = node;
        printf("add first node to list, %p\r\n", node->next);
        return ret;
    }
    pUoNode pos = findPos(list, node);
    if( pos == NULL) { // find the new head 
      node->prev = NULL;
      node->next = list->head;
      list->head->prev = node;
      list->head = node;
      printf("add new head node %p to list, prev:%p, next:%p\r\n", node, node->prev, node->next);
    }
    else {
        node->prev      = pos;
        node->next      = pos->next;
        pos->next = node;
        printf("add new node to list\r\n");
    }
    list->length++;
    if (list->length > list->maxLength) {
        pUoNode removed = list->head; // check if remove from head
        printf("exceed list max length %ud, try to remove node %p", list->maxLength, removed);
        list->head = removed->next;
        list->length--;
        free(removed->data);
        free(removed);
    }
    return ret;
}

unsigned int freeList(pUoList list)
{
    unsigned int ret   = 0;
    pUoNode  p     = list->head;
    unsigned int   index = 0;
    if(list->length == 0) return 0;
    
    do{
      pUoNode next = p->next;
      free(p->data);
      free(p);
      p = next;
    }while(p != NULL);

    list->head  = p;
    list->length = 0;
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
    if(pos != NULL) {
      printf("node %p, prev is %p, next is %p\r\n", pos, pos->prev,pos->next);
      pos = pos->next;
      continue;
    }
    else
      break;
  } while(1);
  printf("\r\n");
  return;
}
