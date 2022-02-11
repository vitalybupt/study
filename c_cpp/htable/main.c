#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include "htable.h"
static struct node_hash* hash_find(uint64_t k);

DEFINE_HASHTABLE(ht1, 8);

struct node_hash {
	struct hlist_node node;
	uint64_t k;
	uint32_t v;
};

static struct node_hash* hash_find(uint64_t k)
{
	struct node_hash *nh;

	hash_for_each_possible(ht1, nh, node, k){
		if(nh->k == k)
			return nh;
	}
	return NULL;
}

int main()
{
	struct node_hash *nh;
	struct hlist_node *tmp;
	int i;

	for(int i = 0; i < 100; ++i) {
		struct node_hash *n1 = calloc(1, sizeof(*n1));
		n1->k = i; n1->v=i*10;
		hash_add(ht1, &n1->node, n1->k);
	}

	assert(hash_find(1) && hash_find(1)->v == 10);
	assert(hash_find(2) && hash_find(2)->v == 20);

	hash_for_each_safe(ht1, i, tmp, nh, node) {
		hash_del(&nh->node);
		free(nh);
	}
	return 0;
}
