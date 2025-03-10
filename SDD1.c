#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    int value;
    struct Node *next;
};
// struct Node *insertAtBeginning(struct Node *head, int newData)   // test;
// {
//     struct Node *newNode = head;
//     newNode = (struct Node *)malloc(sizeof(struct Node));
//     newNode->value = newData;
//     newNode->next = head;
//     head = newNode;
// }

void deleteAtBeginning(struct Node *head)
{
}
void printLinkedList(struct Node *p)
{
    while (p != NULL)
    {
        printf(" %d -->> ", p->value);
        p = p->next;
    }
}
void traversalLinkedList(struct Node *head)
{
    struct Node *temp = head;
    printf("\nList elements are: \n");
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

    // printLinkedList(head);

    // insertAtBeginning elements;
    struct Node *newNode;
    newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->value = 13;
    newNode->next = head;
    head = newNode;
    traversalLinkedList(head);
    // insertAtEnd;
    struct Node *lastNode;
    lastNode = (struct Node *)malloc(sizeof(struct Node));
    lastNode->value = 13;
    lastNode->next = NULL;

    struct Node *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = lastNode;
    traversalLinkedList(head);

    // insertAtMiddle;
    struct Node *middleNode;
    middleNode = (struct Node *)malloc(sizeof(struct Node));
    middleNode->value = 14;

    struct Node *temporary = head;
    int position = 3;
    for (int i = 1; i < position; i++)
    {
        if (temporary->next != NULL)
        {
            temporary = temporary->next;
        }
    }
    middleNode->next = temporary->next;
    temporary->next = middleNode;
    traversalLinkedList(head);

    return 0;
}