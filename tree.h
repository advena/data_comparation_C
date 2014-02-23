typedef struct Node {

    int data;
    struct Node *left, *right;
} Node;

void addNode(Node **root, int value);
Node* findNode(Node *root, int value);
Node* findMaxNode(Node *root);
Node* findMinNode(Node *root);
void delNode(Node **root, int value);
void printAllNodes(Node *root);
void testerTree();
