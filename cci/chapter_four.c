#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "hashtable.h"
#include "graph.h"
#include "chapter_four.h"



static bool graph_routable(p_graph g, phashtable h, int from, int to) {
  if(from == to) return true;
  if(hashtable_ismember_set(h, from)) return false;

  hashtable_insert_set(h, from);
  
  p_list neighs = graph_get_neighs(g,from);
  for(unsigned i = 1; i <= neighs->len; ++i) {
    int neigh = list_get_integer_value(neighs, i);
    if(graph_routable(g, h, neigh, to)) {
      hashtable_remove_set(h, from);
      return true;
    }
  }
  hashtable_remove_set(h, from);
  return false;
}
void test_route_search() {
    p_graph g = graph_create(6);
    assert(g != NULL && g->node_number == 6);
    graph_insert_neigh(g, 0, 1); graph_insert_neigh(g, 0, 4); graph_insert_neigh(g, 0, 5);
    graph_insert_neigh(g, 1, 3); graph_insert_neigh(g, 1, 4);
    graph_insert_neigh(g, 2, 1);
    graph_insert_neigh(g, 3, 2); graph_insert_neigh(g, 3, 4);

    phashtable hset = hashtable_create();
    assert(graph_routable(g, hset, 0, 3));
    assert(hashtable_empty(hset));
    
    assert(!graph_routable(g, hset, 3, 0));
    assert(hashtable_empty(hset));
    
    assert(!graph_routable(g, hset, 2, 0));
    assert(hashtable_empty(hset));

    hashtable_free(hset);
    free(hset);
    graph_free(g);
}
