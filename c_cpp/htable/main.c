#include "htable.h"

struct node_hash {
	struct hlist_node node;
	uint64_t k;
};

int main()
{
	DEFINE_HASHTABLE(ht1, 8);
	struct node_hash n1 = {.k = 1};
	hash_add(ht1, &n1.node, n1.k);
	return 0;
}
