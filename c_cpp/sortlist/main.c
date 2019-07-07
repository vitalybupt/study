#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "uolist.h"
typedef struct{
  char name[8];
  char address[64];
} contact, *pContact;

static int contactCmp(void* p1, void* p2) {
  return strncmp(((pContact)p1)->name, ((pContact)p2)->name, 8);
}

static void insertContact(pUoList list, const char* name, const char* addr) {
  pContact p1 = malloc(sizeof(contact));
  memset(p1, 0,sizeof(contact));
  strncpy(p1->name, name, 8);
  strncpy(p1->address, addr, 64);
  pUoNode node1 = malloc(sizeof(uoNode));
  memset(node1, 0, sizeof(uoNode));
  node1->prev = node1->next = NULL;
  node1->data = p1;

  addList(list, node1);
  //dumpList(list);

  return;
}
void main()
{
  pUoList list = malloc(sizeof(uoList));
  memset(list, 0, sizeof(uoList));
  list->maxLength = 10000;
  list->cmp = contactCmp;
  dumpList(list);

  insertContact(list, "zjw", "beijing");
  insertContact(list, "phy", "beijing");
  insertContact(list, "zzz", "beijing");
  dumpList(list);
  freeList(list);

  insertContact(list, "phy", "beijing");
  insertContact(list, "zzz", "beijing");
  dumpList(list);
  freeList(list);

  int i = 0;
  do{
      char buf[32];
      memset(buf, 0, 32);
      snprintf(buf, 32, "zjw%d", i);
      insertContact(list, buf, "beijing");
      i++;
  }while(i<20000);
  dumpList(list);
  freeList(list);
  
  free(list);
  return;
}
