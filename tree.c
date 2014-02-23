#include <stdio.h>
#include <stdlib.h>
#include "tree.h"



/** Recursively adds given value to the tree
 *
 * @param root
 * @param value
 *
 */

void addNode(Node **root, int value) {

    Node *temp;
    ///check statement to avoid infinite loop in adding
    if(*root == NULL) {
        temp = (Node*)malloc(sizeof(Node));
        temp->data = value;
        temp->left = temp->right = NULL;
        *root = temp;
        return;
    }
    ///recursively check where to add node
    ///if smaller than the root add to the left
    ///if bigger than the root add to the right
    else {
        temp = *root;
        if(value < temp->data) {
            addNode(&(temp->left), value);
        } else {
            addNode(&(temp->right), value);
        }
        return;
    }
}

/** Recursively searches for Node with given value
 *
 * @param root
 * @param value
 * @return Node or NULL (if Node was not found)
 *
 */

Node* findNode(Node *root, int value) {

    Node *temp;
    ///check statement to avoid infinite loop in searching
    ///if it reachese that point given value is not in the tree
    if(root == NULL) {
        printf("Given value is not in the tree\n");
        return NULL;
    }
    temp = root;
    if(temp->data == value) {
        printf("Searched value is: %i\n", temp->data);
        return temp;
    } else if(value < temp->data) {
        findNode(temp->left, value);
    } else {
        findNode(temp->right, value);
    }
}

/** Recursively searches for Node with max value
 *
 * @param root the starting point
 * @return Node or NULL if tree is empty
 *
 */

Node* findMaxNode(Node *root) {

    ///first check if tree isn't empty
    if(root == NULL) {
        //printf("The tree is empty!\n");
        return NULL;
    }
    ///now go to the right-most node to get the max value
    if (root->right) {
        return findMaxNode(root->right);
    }
    ///there is no node left root is the last leaf of the tree
    else {
        //printf("The max value is: %i\n", root->data);
        return root;
    }
}

/** Recursively searches for Node with min value
 *
 * @param root starting point
 * @return Node or NULL if tree is empty
 *
 */

Node* findMinNode(Node *root) {

    ///first check if tree isn't empty
    if(root == NULL) {
        //printf("The tree is empty!\n");
        return NULL;
    }
    ///now to the left-most node to get the min value
    if(root->left) {
        return findMinNode(root->left);
    }
    ///there is no node left root is the last leaf of the tree
    else {
        //printf("The min value is: %i\n", root->data);
        return root;
    }
}


/** Deletes node with given value
 *
 * @param root starting node
 * @param value value that is going to be delete
 *
 */

void delNode(Node **root, int value) {

    Node *temp;
    ///check if given value is in tree
    if(*root == NULL){
        //printf("Given value is not in the tree\n");
        return;
    }
    temp = *root;
    ///now recirsively get to the proper node in the tree
    if((*root)->data > value) {
        delNode(&((*root)->left), value);
    }
    else if((*root)->data < value) {
        delNode(&((*root)->right), value);
    }
    ///finally we get to the proper node root->data == value
    else {
        ///case 1:
        ///given node has two children
        ///we need to switch the node with the left-most node (minNode)
        if((*root)->left != NULL && (*root)->right != NULL) {
            temp = findMinNode((*root)->right);
            (*root)->data = temp->data;
            delNode(&(*root)->right, temp->data);
        }
        ///case 2:
        ///given node has one child, either on the left or right, or has no
        ///children is only a leaf
        else{
            ///if no children simply set that node to NULL
            if((*root)->left == NULL && (*root)->right == NULL) {
                *root = NULL;
            }
            ///if one child make a conection between parent and that child
            else {
                temp = *root;
                if(temp->left != NULL) {
                    *root = (*root)->left;
                } else {
                    *root = (*root)->right;
                }
                free(temp);
                temp = NULL;
            }
        }
        return;
    }
}

/** Prints out all tree nodes in preorder type
 *
 * @param root starting node
 *
 */

void printAllNodes(Node *root) {

    if(root){
        printf("%d\n", root->data);
        printAllNodes(root->left);
        printAllNodes(root->right);
    }
}

/** Recursively realeses memory by free all nodes from the tree
 *
 * @param root starting node
 *
 */

void realiseMemory(Node *root) {

    if(root) {
        realiseMemory(root->left);
        realiseMemory(root->right);
        free(root);
    }
}

void testerTree() {

    int num;
    Node *root = NULL;
    FILE *file = fopen("even_numbers1.txt", "r");
    while(fscanf(file, "%i", &num)!=EOF) {
        addNode(&root, num);
    }
    fclose(file);
    findNode(root, 11832);
    findNode(root, 11835);
    realiseMemory(root);
}



