struct ListNode *searchList(struct ListNode* l, int val) {
  struct ListNode* p = l;
  struct ListNode* prev = NULL;
  while(p != NULL) {
    if(p->val >= val) return prev;
    prev = p;
    p = p->next;
  }
  return prev;
}

struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
  struct ListNode *p = l2;
  struct ListNode *retList = l1;
  while(p != NULL) {
    struct ListNode *tmp = searchList(retList, p->val);
    if(tmp == NULL) { // insert to the head
      struct ListNode *tmp2 = p->next;
      p->next = retList;
      retList = p;
      p = tmp2;
    } else {
      struct ListNode *tmp2 = p->next;
      p->next = tmp->next;
      tmp->next = p;
      p = tmp2;
    }
  }
  return retList;
}
