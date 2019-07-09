/* type declare */
typedef struct Node Node,*pNode;
typedef struct SortList SortList, *pSortList;

typedef int (*cmpData)(void*, void*);
typedef pNode (*searchAlgo)(pSortList list, pNode target);

struct Node {
  pNode next;
  void* data;
};
  
struct SortList {
  pNode head;
  pNode tail;
  unsigned int length;
  unsigned int maxLength;
  cmpData cmp;
  searchAlgo search;
};

typedef enum {
      linear,
      binary
} SearchAlgo;

/* function declare */  
unsigned int addList(pSortList, pNode);
void setAlgo(pSortList, SearchAlgo);
unsigned int freeList(pSortList list);
void dumpList(pSortList);
void validateList(pSortList list, unsigned length);
