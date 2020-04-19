#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>

#include "matrixbuilder.h"

void* create_matrix(unsigned int row, unsigned col) {
  assert(row != 0 && col != 0);
  void* matrix = malloc(sizeof(unsigned int)*row*col);
  memset(matrix, 0, sizeof(unsigned int)*row*col);
  return matrix;
}

void* create_random_matrix(unsigned int row, unsigned int col) {
  void* matrix = create_matrix(row, col);
  srand(time(0));
  for(unsigned int i = 0; i < row*col; ++i) {
    ((unsigned int*)matrix)[i] = rand()%100;
  }
  return matrix;
}

void dump_matrix(void *matrix, unsigned row, unsigned col) {
  printf("the matrix is:\r\n");
  for(unsigned i = 0; i < row; ++i) {
    for(unsigned j = 0; j < col; ++j) {
      printf("%02u ", ((unsigned int*)matrix)[i*col+j]);
    }
    printf("\r\n");
  }
  return;
}
void free_matrix(void* matrix) {
  free(matrix);
  matrix = NULL;
  return;
}
