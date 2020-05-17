#ifndef MATRIXBUILDER_H
#define MATRIXBUILDER_H
/* macro and type defination */
typedef struct {
  void *val;
  int row;
  int col;
} matrix, *p_matrix;
  
#define matrix_val(m, r, c) *((int*)(m->val)+(r*(m->col)+c))
#define matrix_ref(m, r, c) ((int*)(m->val)+(r*(m->col)+c))

p_matrix matrix_create(int row, int col);
p_matrix matrix_create_random(int row, int col, int mod);
void matrix_set(p_matrix m, int row, int col, int v);
void free_matrix(p_matrix m);

#ifdef DEBUG
void dump_matrix(p_matrix m);
#else
#define dump_matrix(...) do{} while(0)
#endif
#endif
