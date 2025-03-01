#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    int value;
    struct Node *next;
};

void printLikedList(struct Node *p)
{
    while (p != NULL)
    {
        printf(" %d ", p->value);
        p = p->next;
    }
}
int main()
{ // Initializare noduri;
    struct Node *head;
    struct Node *one = NULL;
    struct Node *two = NULL;
    struct Node *three = NULL;
    // alocare de memorie;
    one = (struct Node *)malloc(sizeof(struct Node));
    two = (struct Node *)malloc(sizeof(struct Node));
    three = (struct Node *)malloc(sizeof(struct Node));
    // assign values;
    one->value = 1;
    two->value = 2;
    three->value = 3;
    // connect nodes;
    one->next = two;
    two->next = three;
    three->next = NULL;
    // printare node-value;
    head = one;
    printLikedList(head);
    return 0;
}