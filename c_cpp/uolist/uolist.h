/* type declare */
typedef int (*uoNodeCmp)(void*, void*);

typedef struct uoNode uoNode,*pUoNode;

struct uoNode {
  pUoNode prev;
  pUoNode next;

  void* data;
};
  
typedef struct {
  pUoNode head;
  pUoNode tail;

  unsigned int length;
  unsigned int maxLength;
  uoNodeCmp cmp;
} uoList, *pUoList;

/* function declare */  
unsigned int addList(pUoList, pUoNode);
unsigned int freeList(pUoList list);
void dumpList(pUoList);
