#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    int value;
    struct Node *next;
};

void printLinkedList(struct Node *p)
{
    while (p != NULL)
    {
        printf(" %d ", p->value);
        p = p->next;
    }
}
void traverseLinkedList(struct Node *head)
{
    struct Node *temp = head;
    printf("\n \n List elements are -->> \n");
    while (temp != NULL)
    {
        printf("%d --->> ", temp->value);
        temp = temp->next;
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
    // connecting nodes;
    one->next = two;
    two->next = three;
    three->next = NULL;

    // printare nodes-values;
    head = one;
    printLinkedList(head);
    traverseLinkedList(head);

    return 0;
}