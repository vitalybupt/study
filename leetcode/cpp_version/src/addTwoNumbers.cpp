#include <iostream>
#include <vector>

using std::vector;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
      if(l1 == NULL) return l2;
      else if(l2 == NULL) return l1;
      int newVal = l1->val + l2->val;
      ListNode *ret = new ListNode(newVal % 10 );
      ret->next = addTwoNumbers(l1->next, l2->next);
      if(newVal >= 10) {
	ListNode *tmp1 = ret->next; ListNode *tmp2 = new ListNode(1);
	ret->next = addTwoNumbers(tmp1, tmp2);
	delete tmp1; delete tmp2;
      }
      return ret;
    }
};

ListNode* convert(vector<int> rawData) {
  ListNode *ret = NULL; ListNode * cur = ret;
  for(int const & val : rawData) {
    ListNode* p = new ListNode(val);
    p->val = val;
    if(cur == NULL) {cur = p; ret = cur;}
    else {
      cur->next = p;
      cur = p;
    }
  }

  return ret;
}
void free_listNode(ListNode *l) {
  ListNode *cur = l;
  while(cur != NULL) {
    ListNode *next = cur->next;
    delete cur;
    cur = next;
  }
}
int main() {
  class Solution cal;
  ListNode *l1 = convert(vector<int>({2,4,3}));
  ListNode *l2 = convert(vector<int>({5,6,4}));
  ListNode *ret = cal.addTwoNumbers(l1, l2);
  
  free_listNode(ret);
  free_listNode(l1);   free_listNode(l2);
  return 0;
}
