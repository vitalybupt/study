#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *merge(struct ListNode* h1, struct ListNode* h2) {
   if(h1 == NULL) return h2;
   if(h2 == NULL) return h1;
   
   if(h1->val <= h2->val) {
      h1->next = merge(h1->next, h2);
      return h1;
   } else {
      h2->next = merge(h1, h2->next);
      return h2;
   }
}

struct ListNode* sortIter(struct ListNode* head) {
   if(head == NULL || head->next == NULL) return head;
   /* split the list into two halved */
   struct ListNode* walker = head;
   struct ListNode* runner = head;
   struct ListNode* prev = NULL;
   while(runner != NULL && runner->next != NULL) {
      prev = walker;
      walker = walker->next;
      runner = runner->next->next;
   }

   prev->next = NULL;
   
   return merge(sortIter(head), sortIter(walker));
}

struct ListNode* sortList(struct ListNode* head){
   return sortIter(head);
}


int main() {
   
}
