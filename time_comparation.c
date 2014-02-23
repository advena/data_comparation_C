#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "tree.h"
#include "avl_tree.h"
#include "linked_list.h"
#include "random_number_generator.h"


#define SIZE 5000000
#define LEN 100000

/** Adds all numbers from files to three data types linked list, binary tree
 *  and avl tree. Measures times of adding
 *
 *  @param nums empty list
 */

void addFromFile(int nums[]) {

    FILE *file;
    int i, num;


    ///open file where numbers are stored
    file = fopen("numbers3.txt", "r");
    ///now iterate over all numbers and add them to the nums array
    i = 0;
    while(fscanf(file, "%i", &num) != EOF) {
        nums[i] = num;
        i++;
    }
    fclose(file);
    return;
}

/** Measure the time for finding elements in linked list
 *
 * @param nums empty list
 *
 */

void listMeasuring(int nums[]) {

    FILE *file;
    Elem *head = NULL;
    Elem *current;
    int step1, step2, step3, step4;
    int findedNodes[LEN];
    int i, j, k, index;
    struct timespec start_for_finding, stop_for_finding;

    step1 = 5000; step2 = step1*10; step3 = step2*10; step4 = (step3*10)-1;
    //open file to save the times
    file = fopen("list_times1.txt", "w");
    //iterate trough all elements in nums and add them to the linked list
    fprintf(file, "LINKED LIST");
    k = 0; //iterator to track findedNode index
    for (i=0; i<SIZE; i++) {
        //check if proper step is reached
        if(i == step1 || i == step2 || i == step3 || i == step4) {
            fprintf(file, "\nFor %i elements: ", i);
            //make 100 iterations for random picked number from nums in range
            //to proper step, measure the time and approximate it
            clock_gettime(CLOCK_MONOTONIC, &start_for_finding);
            for (j=0; j<1000; j++) {
                index = rand()%i;
                current = findElem(head, nums[index]);
                //findedNodes[k] = current->data;
                k++;
            }
            clock_gettime(CLOCK_MONOTONIC, &stop_for_finding);
            fprintf(file, "\nFinding positive: %.5f", (double)
                                             ((stop_for_finding.tv_nsec -
                                              start_for_finding.tv_nsec)/j)/
                                              10000000);
            //now find negative numbers
            clock_gettime(CLOCK_MONOTONIC, &start_for_finding); //reset timer
            for(j=0;j<1000;j++) {
                index = rand()%i;
                current = findElem(head, nums[index] + 1);
                //findedNodes[k] = 0;
                k++;
            }
            clock_gettime(CLOCK_MONOTONIC, &stop_for_finding);
            fprintf(file, "\nFinding negative: %.5f", (double)
                                             ((stop_for_finding.tv_nsec -
                                              start_for_finding.tv_nsec)/j)/
                                              10000000);
        }
        addElem(&head, nums[i]);
    }
    fclose(file);
    //release memory
    realiseMemory(head);
    return;
}

/** Measure the time for finding elements in binary tree
 *
 * @param nums empty list
 *
 */

void treeMeasuring(int nums[]) {

    FILE *file;
    Node *root = NULL;
    Node *current;
    int step1, step2, step3, step4;
    int findedNodes[LEN];
    int i, j, k, index;
    struct timespec start_for_finding, stop_for_finding;

    step1 = 5000; step2 = step1*10; step3 = step2*10; step4 = (step3*10)-1;
    //open file to save the times
    file = fopen("tree_times1.txt", "w");
    //iterate trough all elements in nums and add them to the linked list
    fprintf(file, "BINARY TREE");
    k = 0; //iterator to track findedNode index
    for (i=0; i<SIZE; i++) {
        //check if proper step is reached
        if(i == step1 || i == step2 || i == step3 || i == step4) {
            printf("Step: %d", i);
            fprintf(file, "\nFor %i elements: ", i);
            //make 100 iterations for random picked number from nums in range
            //to proper step, measure the time and approximate it
            clock_gettime(CLOCK_MONOTONIC, &start_for_finding);
            for (j=0; j<1000; j++) {
                index = rand()%i;
                current = findNode(root, nums[index]);
                //findedNodes[k] = current->data;
                k++;
            }
            clock_gettime(CLOCK_MONOTONIC, &stop_for_finding);
            fprintf(file, "\nFinding positive: %.5f", (double)
                                             ((stop_for_finding.tv_nsec -
                                              start_for_finding.tv_nsec)/j)/
                                              10000000);
            //now find negative numbers
            clock_gettime(CLOCK_MONOTONIC, &start_for_finding); //reset timer
            for(j=0;j<1000;j++) {
                index = rand()%i;
                current = findNode(root, nums[index] + 1);
                //findedNodes[k] = 0;
                k++;
            }
            clock_gettime(CLOCK_MONOTONIC, &stop_for_finding);
            fprintf(file, "\nFinding negative: %.5f", (double)
                                             ((stop_for_finding.tv_nsec -
                                              start_for_finding.tv_nsec)/j)/
                                              10000000);
        }
        addNode(&root, nums[i]);
    }
    fclose(file);
    //realise memory
    realiseMemory(root);
    return;
}


/** Measure the time for finding elements in avl tree
 *
 *  @param nums empty list
 *
 */

void avlMeasuring(int nums[]) {

    FILE *file;
    AvlNode *root = NULL;
    AvlNode *current;
    int step1, step2, step3, step4;
    int findedNodes[LEN];
    int i, j, k, index;
    struct timespec start_for_finding, stop_for_finding;

    step1 = 5000; step2 = step1*10; step3 = step2*10; step4 = (step3*10)-1;
    //open file to save the times
    file = fopen("avl_times1.txt", "w");
    fprintf(file, "AVL TREE");
    k = 0; //iterator to track findedNode index
    for (i=0; i<SIZE; i++) {
        //check if proper step is reached
        if(i == step1 || i == step2 || i == step3 || i == step4) {
            printf("Step: %d", i);
            fprintf(file, "\nFor %i elements: ", i);
            //make 100 iterations for random picked number from nums in range
            //to proper step, measure the time and approximate it
            clock_gettime(CLOCK_MONOTONIC, &start_for_finding);
            for (j=0; j<1000; j++) {
                index = rand()%i;
                current = findNode(root, nums[index]);
                //findedNodes[k] = current->data;
                k++;
            }
            clock_gettime(CLOCK_MONOTONIC, &stop_for_finding);
            fprintf(file, "\nFinding positive: %.5f", (double)
                                             ((stop_for_finding.tv_nsec -
                                              start_for_finding.tv_nsec)/j)/
                                              10000000);
            //now find negative numbers
            clock_gettime(CLOCK_MONOTONIC, &start_for_finding); //reset timer
            for(j=0;j<1000;j++) {
                index = rand()%i;
                current = findNode(root, nums[index] + 1);
                //findedNodes[k] = 0;
                k++;
            }
            clock_gettime(CLOCK_MONOTONIC, &stop_for_finding);
            fprintf(file, "\nFinding negative: %.5f", (double)
                                             ((stop_for_finding.tv_nsec -
                                              start_for_finding.tv_nsec)/j)/
                                              10000000);
        }
        root = addAvlNode(root, nums[i]);
    }
    fclose(file);
    //realise memory
    realiseMemory(root);
    return;
}




void timeMeasuring() {

    //create array to keep SIZE of numbers
    static int nums[SIZE];
    //add elements to the array
    addFromFile(nums);
    //measure time for linked list
    listMeasuring(nums);
    //measure time for binary tree
    treeMeasuring(nums);
    //measure time for avl tree
    avlMeasuring(nums);
    printf("done!");
    return;
}

