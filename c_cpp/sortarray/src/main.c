#include <sortarray.h>

#define ARRAY_SIZE 100

typedef struct{
  char name[8];
  char address[64];
} contact, *pContact;

static int contactCmp(void* p1, void* p2) {
    return strncmp(((pContact)p1)->name, ((pContact)p2)->name, 8);
}

static void dumpArray(pArray array) {
  if(array->length == 0) {
    printf("empty array\r\n");
    return;
  }
  printf("begin dump array with length %d:\r\n", array->length);
  for(int i = 0; i < array->length; ++i) {
      printf("%s\r\n", ((pContact)(array->data[i]))->name);
  }
  printf("\r\n");
  return;
}

static void insertContact(pArray array, const char* name, const char* addr) {
    pContact p1 = malloc(sizeof(contact));
    memset(p1, 0, sizeof(contact));
    strncpy(p1->name, name, 8);
    strncpy(p1->address, addr, 64);
    addArray(array, p1);
	//dumpArray(array);
    return;
}



int main(){
    pArray array = createArray(ARRAY_SIZE);
    setCmpAlgo(array, contactCmp);
    int i = 0;
    do{
	char buf[32];
	memset(buf, 0, 32);
      snprintf(buf, 32, "zjw%d", i);
      insertContact(array, buf, "beijing");
      i++;
    }while(i<20000);
    emptyArray(array);
    deleteArray(array);

    return 0;
}
