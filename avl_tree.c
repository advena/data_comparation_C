#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "avl_tree.h"

//helper functions
/** Gets the height of the given node
 *
 * @param root node that height we want get
 * @return 0 or height of the node
 *
 */

int getHeight(AvlNode *root) {

    if(root == NULL) {
        return 0;
    }
    else {
        return root->height;
    }
}
/** Takes two integers and returns the bigger one from comparation of that two
 *
 * @param heightOne first height
 * @param heightTwo second height
 * @return heightOne or heightTwo bigger one
 *
 */

int biggerHeight(int heightOne, int heightTwo) {

    if(heightOne < heightTwo) {
        return heightTwo;
    }
    return heightOne;
}

/** Computes the balance between left and right node
 *
 * @param parent node
 * @return difference between heights of children
 *
 */

int balanceFactor(AvlNode *parent) {

    ///check if parent isn't empty
    if(parent == NULL){
        return 0;
    }
    else {
        return getHeight(parent->left) - getHeight(parent->right);
    }
}


/** Creates new node with given value
 *
 * @param value that will be the data of node
 * @return node with childrens as NULL
 *
 */

AvlNode* newNode(int value) {

    AvlNode* node = (AvlNode*)malloc(sizeof(node));
    node->data = value;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}
/** Adds node to the tree, after adding is doing self-balancing to keep the
 *  tree as the AVL tree
 *
 * @param root starting point
 * @param value node data
 *
 */
AvlNode* addAvlNode(AvlNode* root, int value) {


    int balance;
    ///check if the tree is empty if so add the first node
    if(root == NULL) {
        return newNode(value);
    }

    ///recursively check where to add new node

    if(root->data > value) {
        root->left = addAvlNode(root->left, value);
    }
    else {
        root->right = addAvlNode(root->right, value);
    }

    ///now update the height of the parent node
    ///it's the bigger height of his children + 1
    root->height = biggerHeight(getHeight(root->left),
                                getHeight(root->right)) + 1;

    ///find balance to check wheather this node is unbalanced
    balance = balanceFactor(root);

    ///if node is not balanced there are four cases:

    ///rightRotation case
    if(balance > 1 && value < root->left->data){
        return rightRotation(root);
    }

    ///leftRotation case
    if(balance < -1 && value > root->right->data) {
        return leftRotation(root);
    }
    ///leftRightRotation case
    if(balance > 1 && value > root->left->data) {
        return leftRightRotation(root);
    }
    ///rightLeftRotation case
    if(balance < -1 && value < root->right->data) {
        return rightLeftRotation(root);
    }

    ///return the root pointer
    return root;

}



/** Rotates in left. Right child of node now becomes parent node. Previous
 *  parent now becomes left child of new parent with left child of node as
 *  right child. To see details look into the diagram
 *
 * @param parent starting point of the rotation
 *
 */

AvlNode* rightRotation(AvlNode *parent) {

    AvlNode *newParent = parent->left;
    AvlNode *childTree = newParent->right;
    newParent->right = parent;
    parent->left = childTree;

    parent->height = biggerHeight(getHeight(parent->left),
                                       getHeight(parent->right)) + 1;
    newParent->height = biggerHeight(getHeight(newParent->left),
                                     getHeight(newParent->right)) + 1;


    return newParent;
}


/** Rotates in right. Left child of the node now becomes parent node. Previous
 *  parent now becomes right child of new parent with right child of node as
 *  left child. To see details look into the diagram.
 *
 * @param parent staring point of the rotation
 *
 */

AvlNode* leftRotation(AvlNode *parent) {

    AvlNode *newParent = parent->right;
    AvlNode *childTree = newParent->left;
    newParent->left = parent;
    parent->right = childTree;


    parent->height = biggerHeight(getHeight(parent->left),
                                    getHeight(parent->right)) + 1;
    newParent->height = biggerHeight(getHeight(newParent->left),
                                     getHeight(newParent->right)) + 1;


    return newParent;
}

/** Rotates in right and then in left. First rotate left child in right
 *  after that rotate all in left.
 *
 * @param parent starting point of the rotation
 *
 */

AvlNode* leftRightRotation(AvlNode *parent) {

    parent->left = leftRotation(parent->left);
    return rightRotation(parent);
}

/** Rotates in left and then in right. First rotate right child in left
 * after that rotete all in right
 *
 * @param parent statring point of the rotation
 *
 */

AvlNode* rightLeftRotation(AvlNode *parent) {

    parent->right = rightRotation(parent->right);
    return leftRotation(parent);
}

/** Deletes proper node form the tree and get rebalancing
 *
 * @param root starting point
 * @param value that is going to be delete
 *
 */

AvlNode* delAvlNode(AvlNode **root, int value) {

    int balance;
    ///first normal tree deletion to delete the proper node
    delNode(&(*root), value);
    ///check if tree isn't empty after deletion
    if((*root) == NULL) {
        return;
    }

    ///update the height of the root
    (*root)->height = biggerHeight(getHeight((*root)->left),
                                getHeight((*root)->right)) + 1;

    ///get the balance factor for that node
    balance = balanceFactor(*root);

    ///now we need to check if tree need to be rebalanced again there are four
    ///cases:

    ///rotate in right direction
    if(balance > 1 && balanceFactor((*root)->left) >=0) {
        rightRotation(*root);
    }

    ///rotate in left direction
    if(balance < -1 && balanceFactor((*root)->right) <= 0) {
        leftRotation(*root);
    }

    ///rotate in left, right direction
    if(balance > 1 && balanceFactor((*root)->left) < 0) {
        leftRightRotation(*root);
    }

    ///rotate in right, left direction
    if(balance < -1 && balanceFactor((*root)->right) > 0) {
        rightLeftRotation(*root);
    }
}

void printAllAvlNodes(AvlNode *root) {

    if(root != NULL) {
        printf("%d ", root->data);
        printAllAvlNodes(root->left);
        printAllAvlNodes(root->right);
    }
}


void testerAvlTree() {

//    AvlNode *root = NULL;
//    root = addAvlNode(root, 9);
//    root = addAvlNode(root, 12);
//    printAllNodes(root);
//    printf("\n");
//    root = addAvlNode(root, 1);
//    root = addAvlNode(root, 3);
//    printAllNodes(root);
//    printf("\n");
//    root = addAvlNode(root, 6);
//    printAllNodes(root);
//    printf("\n");
//    root = addAvlNode(root, 23);
//    root = addAvlNode(root, 4);
//    root = addAvlNode(root, 8);
//    root = addAvlNode(root, 7);
//    root = addAvlNode(root, 17);
//    root = addAvlNode(root, 13);
//    printAllNodes(root);
//    delAvlNode(&root, 6);
//    delAvlNode(&root, 12);
//    printf("\n");
//    printAllNodes(root);
//    return;
    int i, num;
    clock_t start;
    AvlNode *root = NULL;
    FILE *file = fopen("even_numbers.txt", "r");

    while(fscanf(file, "%i", &num)!=EOF) {
        root = addAvlNode(root, num);
    }
    fclose(file);

    //printAllAvlNodes(root);
    start = clock();
    findNode(root, 11832);
    printf("%.10fd\n", clock() - start);
    start = clock();
    findNode(root, 11835);
    printf("%.10fd\n", clock() - start);
    return;
//}

}
