#ifndef MATRIXBUILDER_H
#define MATRIXBUILDER_H
void* create_matrix(unsigned int row, unsigned col);
void* create_random_matrix(unsigned int row, unsigned int col);
void dump_matrix(void *matrix, unsigned row, unsigned col);
void free_matrix(void* matrix);
#endif
