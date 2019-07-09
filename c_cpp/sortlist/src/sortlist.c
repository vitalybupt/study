#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sortlist.h"

/**
   Find parent element so that target will be inserted after that element.       

   In practice, we will find the first element greater or equal than
   the target (the child element), then return the previous element of that one.

   if the child element is head of the list, NULL will be returned to
   indicate that we should insert the terget as the new head of list
**/
static pNode binarySearch(pSortList list, pNode target){
   /* start state:
      NULL  [ ]  [ ]  [ ]  [ ]  NULL
       ¡ü     ¡ü              ¡ü    ¡ü
 prev->found low           high high->next
              ¡ü
     slow ¡ú fast
     invariant: target between [low, high->next]
     if low >= high->next or low > high, break
   */
   pNode found, prev, slow, fast, low, high;
   slow = fast = low = list->head;
   found = prev = NULL;
   high = list->tail;
   /* unsigned count = 0; */

   while( high && low != high->next) {
      /* search step:
	 walk through the list until:
	 [ ]  [ ]  ...   [ ]  [ ]  ...  [ ]  [ ]
          ¡ü    ¡ü          ¡ü    ¡ü         ¡ü    ¡ü
        found low       prev  slow      fast  high
	 or:
	 [ ]  [ ]  ...  [ ]  [ ]  ...  [ ]
          ¡ü    ¡ü         ¡ü    ¡ü         ¡ü 
        found low      prev slow  fast¡úhigh
	the target must be inserted in the range [low, high->next]
	so the range of parent node is [found, high]
      */ 
      while (fast != high && fast->next != high){
	 fast = fast->next->next;
	 prev = slow;
	 slow = slow->next;
	 /* count++; */
      }

      /* update state:
	 split the list into two halves then choose one for next iteration:
	 if slow >= target: [low, prev]
	 [ ]  [ ]  ...  [ ]
	  ¡ü    ¡ü         ¡ü 
	found low       prev
	the update rule is:
	low = low; high = prev; found = found; slow = fast = low; prev = found
	if slow < target:  [slow+1, high]
	[ ]  [ ] ... [ ]
	 ¡ü    ¡ü       ¡ü
       found slow+1  high
       the update rule is:
       low = slow->next; high = high; found = slow; slow = fast = low; prev = found
      */
      if(list->cmp(slow->data, target->data) >= 0) {  /* [low, prev]*/
	 high = prev; // high may become NULL if we found new head
	 slow = fast = low;
	 prev = found;
	 /* printf("update search list1 to low: %p, high: %p\r\n", low, high); */
      } else{ 	 /* [slow->next, high] */
	 low = slow->next;
	 found = slow;
	 slow = fast = low;
	 prev = found;
	 /* printf("update search list2 to low: %p, high: %p\r\n", low, high); */
      }
   }
   /* if(list->length > 2000) */
   /*    printf("list length is %d total loop times is %d\r\n", list->length, count); */
  return found;
}


// find the element we should insert the node after
// if the target is the new head, NULL returned
static pNode linearSearch(pSortList list, pNode target){
    pNode pos = list->head;
    pNode prev = NULL;

    do {
	if(pos != NULL && list->cmp(pos->data, target->data) < 0) { // the element less than value in target
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
	list->tail = node;
	printf("first node %p to list, next is %p\r\n", list->head, node->next);
    } else {
	pNode pos = list->search(list, node);
	if( pos == NULL) { // new head
	    node->next = list->head;
	    list->head = node;
	    printf("add new head node %p to list, next:%p\r\n", node, node->next);
	} else if( pos->next == NULL) { // new tail
	    pos->next = node;
	    list->tail = node;
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
	//printf("exceed list max length %u, try to remove node %p", list->maxLength, removed); 
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

void validateList(pSortList list, unsigned int length) {
  pNode pos = list->head;
  pNode next = pos->next;
  while(pos->next != NULL){
     assert(list->cmp(pos->data, next->data) < 0 );
     if(next->next == NULL) break;
     pos = next;
     next = next->next;
  }
  return;
}

void setAlgo(pSortList list, SearchAlgo algo){
    if(algo == linear)
	list->search = linearSearch;
    else
	list->search = binarySearch;
}
