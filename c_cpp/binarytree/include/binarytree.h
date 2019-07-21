typedef struct Node Node,*pNode;

struct Node {
    pNode left;
    pNode right;
    int value;
};

int verifyBinaryTree(pNode root);
pNode insertIntoBinaryTree(pNode root, int val);
