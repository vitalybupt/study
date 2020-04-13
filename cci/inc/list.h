#ifndef LIST_H
#define LIST_H
typedef struct node {
  struct node *next;
  char *val;
} node, *pnode;

typedef struct list {
  pnode head;
  unsigned int len;
} list, *plist;

plist create_list();
pnode pushback_list(plist l, char* val);
void dump_list(plist l);
void free_list(plist l);

#endif
