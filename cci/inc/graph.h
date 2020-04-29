#include "list.h"

typedef struct {
  p_list *nodes;
  int node_number;
} graph, *p_graph;

p_graph graph_create(int number);
void graph_free(p_graph g);
p_graph graph_insert_neigh(p_graph g, int node, int other);
p_list graph_get_neighs(p_graph g, int node);
