#ifndef VARRAY_H
#define VARRAY_H

#define INIT_SIZE 20

typedef struct {
  char *val;
  unsigned int len;
  unsigned int cap;
} varray, *p_varray;

p_varray varray_create();
p_varray varray_clone();

inline char* varray_get_string(p_varray a) {
  return a->val;
}

void varray_append_char(p_varray a, char v);
void varray_modify(p_varray a, unsigned int pos, char v);
void varray_free(p_varray a);
#endif
