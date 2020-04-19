#ifndef VARRAY_H
#define VARRAY_H

#define INIT_SIZE 20

typedef struct {
  char *val;
  unsigned int len;
  unsigned int cap;
} varray, *pvarray;

pvarray create_varray();
void pushback_varray(pvarray a, char v);
void modifyat_varray(pvarray a, unsigned int pos, char v);
void free_varray(pvarray a);
#endif
