#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sortarray.h>

#define ARRAY_SIZE 100

typedef struct{
  char name[8];
  char address[64];
} contact, *pContact;

static int contactCmp(void* p1, void* p2) {
    return strncmp(((pContact)p1)->name, ((pContact)p2)->name, 8);
}

static void insertContact(pArray array, const char* name, const char* addr) {
    void* node;
    pContact p1 = malloc(sizeof(contact));
    memset(p1, 0,sizeof(contact));
    strncpy(p1->name, name, 8);
    strncpy(p1->address, addr, 64);
    node = p1;
    addArray(array, node);
	/* dumpList(list); */
    return;
}

int main(){
    pArray array = createArray(ARRAY_SIZE);
    setCmpAlgo(array, contactCmp);

    return 0;
}
