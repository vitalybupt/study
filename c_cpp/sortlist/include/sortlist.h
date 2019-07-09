/* type declare */
typedef int (*cmpData)(void*, void*);

typedef struct Node Node,*pNode;

struct Node {
  pNode next;
  void* data;
};
  
typedef struct {
  pNode head;
  pNode tail;
  unsigned int length;
  unsigned int maxLength;
  cmpData cmp;
} SortList, *pSortList;

/* function declare */  
unsigned int addList(pSortList, pNode);
unsigned int freeList(pSortList list);
void dumpList(pSortList);

pNode searchInsert(pSortList list, pNode target);
void validateList(pSortList list, unsigned length);
