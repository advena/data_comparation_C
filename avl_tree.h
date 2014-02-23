typedef struct AvlNode {

    int data;
    int height;
    struct AvlNode *left, *right;
} AvlNode;

AvlNode* newNode(int value);
AvlNode* addAvlNode(AvlNode *root, int data);
AvlNode* deleteAvlNode(AvlNode *root, int data);
AvlNode* leftRotation(AvlNode *parent);
AvlNode* rightRotation(AvlNode *parent);
AvlNode* leftRightRotation(AvlNode *parent);
AvlNode* rightLeftRotation(AvlNode *parent);
int balanceFactor(AvlNode *parent);
int biggerHeight(int heightOne, int heightTwo);

