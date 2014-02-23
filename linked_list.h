#include <stdio.h>



typedef struct Elem {
    int data;
    struct Elem *next;
} Elem;

void initializeList(Elem **head, int value);
void addElem(Elem **head, int value);
void delElem(Elem **head, int value);
Elem* findElem(Elem *head, int value);
void printAll(Elem *head);
void releaseMemory();
void testerList();
