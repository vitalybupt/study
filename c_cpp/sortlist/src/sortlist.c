#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sortlist.h"

/* find the first element with value larger or equal to value in node */
pNode searchInsert(pSortList list, pNode target){
  pNode low = list->head;
  pNode high = NULL;
  pNode slow, fast = list->head;
  slow = list->head;
  do{
    //split into two halves[low, slow, high]
    while(fast->next != high && fast->next->next != high){
      fast = fast->next->next;
      slow = slow->next;
    }

    if(list->cmp(slow, target) < 0) { /* slow->next, high*/
      if(slow == high) break;
      slow = fast = low = slow->next;
    } else{ /* [low, slow->prev ]*/
      if(slow == low)
	break;
      high = slow;
      slow = fast = low;
    }
  } while(1);
  return low;
}


// find the element we should insert the node after
static pNode findPos(pSortList list, pNode node){
    pNode pos = list->head;
    pNode prev = NULL;

    do {
	if(pos != NULL && list->cmp(pos->data, node->data) < 0) { // the element less than value in node
	    prev = pos;
	    pos = pos->next;
	    continue; 
	}
	break;
    } while(1);
    return prev;
}

unsigned int addList(pSortList list, pNode node) {
    unsigned int ret = 0;

    if(list->head == NULL) { //empty list
	list->head = node;
	printf("first node %p to list, next is %p\r\n", list->head, node->next);
    } else {
      /* pNode pos = findPos(list, node); */
      pNode pos =searchInsert(list,node);
	if( pos == NULL) { // new head
	    node->next = list->head;
	    list->head = node;
	    printf("add new head node %p to list, next:%p\r\n", node, node->next);
	} else if( pos->next == NULL) { // new tail
	    pos->next = node;
	    printf("add new tail node %p to list\r\n", node);
	} else {
	    node->next = pos->next;
	    pos->next = node;
	    printf("add new node %p to list\r\n", node);
	}
    }
    list->length++;

    if (list->length > list->maxLength) {
        pNode removed = list->head; // check if remove from head
	printf("exceed list max length %u, try to remove node %p", list->maxLength, removed); 
        list->head = removed->next;
        list->length--;
        free(removed->data);
        free(removed);
    }
    return ret;
}

unsigned int freeList(pSortList list)
{
    unsigned int ret   = 0;
    pNode  p     = list->head;
    if(list->length == 0) return 0;
    
    do{
      pNode next = p->next;
      free(p->data);
      free(p);
      p = next;
    }while(p != NULL);

    list->head  = p;
    list->length = 0;
    return ret;
}

void dumpList(pSortList list) {
  if(list->length == 0) {
    printf("empty list\r\n");
    return;
  }
  printf("begin dump list:\r\n");
  pNode pos = list->head;
  do {
    if(pos != NULL) {
      printf("node %p, next is %p\r\n", pos, pos->next);
      pos = pos->next;
      continue;
    }
    else
      break;
  } while(1);
  printf("\r\n");
  return;
}

void validateList(pSortList list) {
  pNode pos = list->head;
  pNode next = pos->next;
  while(pos->next != NULL){
    printf("validate pos %p, next %p\r\n",pos, next );
    assert(list->cmp(pos, next) < 0 );
    if(next->next == NULL) break;
    pos = next;
    next = next->next;
  }
  return;
}
