#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "graph.h"

p_graph graph_create(int number) {
  p_graph g = malloc(sizeof(graph));
  g->nodes = malloc(sizeof(p_list)*number);
  g->node_number = number;
  for(int i = 0; i < number; ++i) {
    g->nodes[i] = list_create(LIST_TYPE_INTEGER);
  }
  return g;
}
void graph_free(p_graph g) {
  for(int i = 0; i < g->node_number; ++i) {
    list_free(g->nodes[i]);
    free(g->nodes[i]);
    g->nodes[i] = NULL;
  }
  free(g->nodes);
  free(g);
  return;
}
p_graph graph_insert_neigh(p_graph g, int node, int other) {
  p_list t = g->nodes[node];
  list_push_back_integer(t, other);
  return g;
}

p_list graph_get_neighs(p_graph g, int node)  {
  return g->nodes[node];
}

