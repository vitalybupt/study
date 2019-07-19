typedef struct Node Node, *pNode;

struct Node {
    pNode left;
    pNode right;
    void* value;
};

unsigned int verifyBinaryTree(pNode root);
