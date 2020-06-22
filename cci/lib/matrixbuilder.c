#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>

#include "matrixbuilder.h"

p_matrix matrix_create(int row, int col) {
  p_matrix m = NULL;
  do {
    if(row <= 0 || col <= 0)
      break;
    m = malloc(sizeof(matrix));
    m->val = calloc(row*col, sizeof(int));
    m->row = row;
    m->col = col;
  } while(0);
  return m;
}

p_matrix matrix_create_random(int row, int col, int mod) {
  p_matrix matrix = matrix_create(row, col);
  unsigned* val = matrix->val;
  for(int i = 0; i < row*col; ++i) {
    val[i] = rand()%mod;
  }
  return matrix;
}

#ifdef DEBUG
void dump_matrix(p_matrix m) {
  printf("the matrix is:\r\n");
  for(unsigned i = 0; i < m->row; ++i) {
    for(unsigned j = 0; j < m->col; ++j) {
      printf("%02u ", matrix_val(m, i, j));
    }
    printf("\r\n");
  }
  return;
}
#endif

void matrix_set(p_matrix m, int row, int col, int v) {
  if((unsigned)row > (unsigned)m->row || (unsigned)col > (unsigned)m->col)
    return;
  int *p = matrix_ref(m, row, col);
  *p = v;
  return;
}

void matrix_free(p_matrix m) {
  free(m->val);
  free(m);
  m = NULL;
  return;
}
