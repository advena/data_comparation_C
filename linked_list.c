#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

/** Initializes linked list, sets the given value as a data
*   for the head
*
* @param  head
* @param  value
*
*/

void initializeList(Elem **head, int value) {

    Elem *first = (Elem*)malloc(sizeof(Elem));
    first->data = value;
    first->next = NULL;
    *head = first;
}

/** Adds given value at the begin of the list, if list is empty initializes it
 *
 * @param  head
 * @param  value
 *
 */

void addElem(Elem **head, int value) {

    ///first check if head is set to NULL
    if(head == NULL) {
        initializeList(&head, value);
    }
    ///head already exists, add the element at the begining of the list - set it
    ///to the new head

    Elem *newHead = (Elem*)malloc(sizeof(Elem));
    newHead->data = value;
    newHead->next = *head;
    *head = newHead;
}

/** Searches for Elem with given value
 *
 * @param  head
 * @param  value
 * @return Elem or NULL (if value is not found)
 *
 */

Elem* findElem(Elem *head, int value) {

    Elem *start;
    int i;
    ///check if list isn't empty
    if (head == NULL) {
        printf("The list is empty!");
        return NULL;
    }

    ///search trough all elements from head to end
    ///set head to start and i to 1, as iterator to follow the index
    start = head;
    i=1;
    while(start->next != NULL) {
        if(start->data == value){
            printf("The searched value has been found at the position: %i\n", i);
            return start;
        }
        start = start->next;
        i++;
    }
    ///end has been reached value is not in the list
    printf("Given value is not in the list!\n");
    return NULL;
}


/** Searches for Elem with bigest value
 *
 * @param head starting point
 * @return Elem or NULL if list is empty
 *
 */

Elem* findMaxElem(Elem *head) {

    int currentMax;
    Elem *start, *current;
    ///check if list isn't empty
    if(head == NULL) {
        printf("The list is empty!\n");
        return NULL;
    }
    ///set head to start, and current max value as head value
    ///we need to iterate trough all list
    start = current = head;
    currentMax = head->data;
    while(start->next != NULL) {
        if(start->data > currentMax) {
            current = start;
            currentMax = current->data;
        }
        start = start->next;
    }
    printf("The max value is: %i\n", currentMax);
    return current;

}

/** Searches for Elem with smallest value
 *
 * @param head starting point
 * @return Elem or NULL if the list is empty
 *
 */

Elem* findMinElem(Elem *head) {

    int currentMin;
    Elem *start, *current;
    ///check if list isn't empty
    if(head == NULL) {
        printf("The list is empty!\n");
        return NULL;
    }
    ///set start and current to start, and min value as head value
    ///we need to iterate trough all list
    start = current = head;
    currentMin = head->data;
    while(start->next != NULL) {
        if(start->data < currentMin) {
            current = start;
            currentMin = current->data;
        }
        start = start->next;
    }
    printf("The min value is: %i\n", currentMin);
    return current;
}

/** Delate Elem from list that contain given value
 *
 * @param  head
 * @param  value
 *
 */

void delElem(Elem **head, int value) {

    ///first check if Elem to delete == head
    if((*head)->data == value) {
        ///set head to temporary container
        ///then assign next Elem as a head and free memory
        Elem *temp = *head;
        *head = temp->next;
        free(temp);
        temp = NULL;
        printf("Element with given value has been deleted\n");
        return;
    }
    ///if head isn't the Elem that need to be deleted search for proper one
    ///start from the beginning of the list
    ///keep track current and previous Elem to make correct connection
    ///after deleting
    else {
        Elem *previous = *head;
        Elem *current = (*head)->next;
        while (current != NULL) {
            if (current->data == value) {
                previous->next = current->next;
                free(current);
                current = NULL;
                printf("Element with given value has been deleted\n");
                return;
            }
            current = current->next;
            previous = previous->next;
        }
    }
    printf("Elem is not in the list!\n");
    return;

}

/** Prints out all Elems in list with proper index for that Elem starts form 1
 *
 * @param  head starting point
 *
 */


void printAll(Elem* head) {
    ///counter to track the index of Elem
	int i = 1;
	Elem *start = head;
    if (head == NULL)
        printf("The Elem list is empty\n");


    while (start!= NULL) {
        printf("Value at index %i: %i\n", i, start->data);
        i++; //increase index
        start = start->next; //go to next elem in list

    }
    return;
}

/** Realeses all memory by deleting all list Elems
 *
 * @param head starting Elem
 *
 */

void releaseMemory(Elem *head) {

    Elem *temp;
    while(head->next != NULL) {
        temp = head->next;
        head = head->next;
        free(temp);
    }
}

/**  Simple tester for the list
 */


void testerList() {

    int num;
    Elem *head = NULL;
    FILE *file = fopen("even_numbers1.txt", "r");
    while(fscanf(file, "%i", &num)!=EOF) {
        addElem(&head, num);
    }
    fclose(file);
    findElem(head, 11832);
    findElem(head, 11835);
    realiseMemory(head);
}
