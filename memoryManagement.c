#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Node {   
    /* data */           
    int id;                     // process id
    int size;                   // process size
    bool isfree;
    struct Node *next;
}node;

node *start = NULL;

void initialBlock () {
    start = (node *)malloc (sizeof (node));         // allocate memory for operating system
    start->id = -1;         // operating system id
    start->size = 400;          // operating system size
    start->isfree = 0;          // memory is allocated

    start->next = (node *)malloc (sizeof (node));       // allocate memory for free block
    start->next->id = -2;           // initial free space id 
    start->next->size = 2560;       // size of initial free space
    start->next->isfree = 1;     // memory is free

    start->next->next = NULL;

}

void memoryAllocation () {
    int processId, processSize;
    printf ("Process Id : ");
    scanf ("%d", &processId);
    printf ("Process Size : ");
    scanf ("%d", &processSize);
    
    node * current = start;         // begining of the free space
    node * previous = start;        // previous block 
    node * newNode = NULL;          // allocated memory for the process

    int sizeMatch = 0;         // whether current free space is sufficient or not

    while (current != NULL) {
        if (current->isfree) {
            if (current->size - previous->size > processSize) {         // available more than required space
                break;

            }
            else if (current->size - previous->size == processSize) {   // equal to the required space
                /* code */
                sizeMatch = 1;
                break;

            }
        }
        previous = current;
        current = current->next;

    }

    if (current == NULL) {                  // if block has no required space 
        /* code */
        printf ("No memory to allocate\n");

    }else {
        if (sizeMatch == 1) {           // if free space is equal to the required process size
            /* code */
            current->isfree = 0; // memory is allocated by the process
            current->id = processId;
            printf("\nMemory is allocated to process %d\n", processId);
            printf ("The free space is over\n\n");

        }else {                                         // if there are more space than required
            /* code */
            newNode = (node *) malloc (sizeof (node));      // allocate
            previous->next = newNode;
            newNode->next = current;
            newNode->size = previous->size + processSize;
            newNode->id = processId;
            newNode->isfree = 0;
            printf("\nMemory is allocated to process %d\n\n", processId);

        }
    }  
}

void freeMemory () {
    int processId;
    printf ("Id of the teminating process : ");
    scanf ("%d", &processId);

    node * current = start;
    node * previous = start;
    node * next = start;

    while (current->id != processId && current->next != NULL) {
        previous = current;
        current = current->next;
        next = current->next;

    }

    if (current->id != processId && next == NULL) {
        /* code */
        printf ("Process id was not found");
        
    }else if (current->id == processId && next == NULL) {
        /* code */
        if (previous->isfree) {
            /* code */
            previous->size = current->size;
            previous->next = NULL;
            free (current);
            printf ("The memory is free\n");

        }else {
            current->isfree = 1;

        }

    }else {
        if (previous->isfree == 1 && next->isfree == 0) {
            /* code */
            previous->size = current->size;
            previous->next = next;
            free (current);
            printf("The memory is free\n");

        }else if (previous->isfree == 1 && next->isfree == 1) {
            /* code */
            previous->size = next->size;
            previous->next = next->next;
            free (current);
            free (next);
            printf("The memory is free\n");

        }else if (previous->isfree == 0 && next->isfree == 1) {
            /* code */
            current->next = next->next;
            current->size = next->size;
            current->isfree == 1;
            free (next);
            printf("The memory is free\n");
            
        }else {
            current->isfree = 1;

        }
    }    
}

void displayBlock () {
    printf("\n0K\t____________________________\n\n");
    node * temp = start;
    while (temp != NULL) {
        printf ("\t|");
        if (temp->id == -1) {
            printf ("\tOperating system     |\n");
            printf("\t____________________________\n");
            printf ("%dK\n", temp->size);

        }else if (temp->isfree) {
            /* code */
            printf("\tfree               |\n"); 
            printf("\t____________________________\n");
            printf("%dK\n", temp->size);

        }else {
            printf("\tP%d                 |\n", temp->id);
            printf("\t____________________________\n");
            printf("%dK\n", temp->size);

        }

        temp = temp->next;

    }
    printf ("\n");

}

int main () {
    int opId;

    initialBlock ();

    do {
        /* code */
        printf ("-----Operations------\n");
        printf ("1. Allocate memory.\n");
        printf ("2. Terminate a process.\n");
        printf ("3. Graphical view of memory block.\n");
        printf ("4. Exit.\n");
        printf ("\nInsert Operation Number : ");
        scanf ("%d", &opId);

        switch (opId) {
            case 1:
            /* code */
                memoryAllocation ();
                break;

            case 2:
                freeMemory ();
                break;

            case 3:
                displayBlock ();
                break;

            default:
                break;

        }

    } while (opId != 4);
}