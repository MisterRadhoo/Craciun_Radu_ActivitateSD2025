#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Laptop
{
    int id;
    char *brand;
    int RAM;
    float capacitate;
    float rezolutie;
    int nrTaste;
    int *nrApasariTasta;
};

struct Laptop initializare(int id, const char *brand, int RAM, float capacitate, float rez, int nrTaste)
{

    struct Laptop laptop2;
    laptop2.id = id;
    laptop2.brand = (char *)malloc((strlen(brand) + 1) * sizeof(char));
    strcpy(laptop2.brand, brand);
    laptop2.RAM = RAM;
    laptop2.capacitate = capacitate;
    laptop2.rezolutie = rez;
    laptop2.nrTaste = nrTaste;
    laptop2.nrApasariTasta = (int *)malloc(nrTaste * sizeof(int));
    if (laptop2.nrApasariTasta == NULL)
    {
        printf("Memoria nu se poate aloca !!!");
        exit(1);
    }
    for (int i = 0; i < nrTaste; i++)
    {
        laptop2.nrApasariTasta[i] = 0;
    }
    return laptop2;
}
void display(struct Laptop l)
{
    printf("Laptop ID: --->> %d , Brand Laptop:-->> %s \n", l.id, l.brand);
    printf("Laptop RAM:-->> %d GB, Laptop Capacitate:-->> %.2f GBytes\n", l.RAM, l.capacitate);
    printf("Rezolutie Laptop:-->> %.2f pixeli \n", l.rezolutie);
    printf("Laptop numar taste:-->> %d taste \n", l.nrTaste);
    for (int i = 0; i < l.nrTaste; i++)
    {
        printf("Numar apasari taste: %d %d apasari \n", i + 1, l.nrApasariTasta[i]);
    }
}
void freeMemory(struct Laptop *laptop)
{
    if (laptop->nrApasariTasta != NULL)
    {
        free(laptop->nrApasariTasta);
        laptop->nrApasariTasta = NULL;
        printf("free memory !!!\n");
    }
    if (laptop->brand != NULL)
    {
        free(laptop->brand);
        laptop->brand = NULL;
        printf("free memory !\n");
    }
}
struct Node
{
    struct Laptop laptop;
    struct Node *next;
};
void insertAtBeginning(struct Node **head, struct Laptop l)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->laptop = l;
    newNode->next = *head;
    *head = newNode;
}
void insertAtEnd(struct Node **head, struct Laptop l)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    struct Node *lastNode = *head;
    newNode->laptop = l;
    newNode->next = NULL;
    if (*head == NULL)
    {
        *head = newNode;
        return;
    }
    while (lastNode->next != NULL)
        lastNode = lastNode->next;
    lastNode->next = newNode;
    return;
}

void deleteNode(struct Node **head, struct Laptop l)
{
    struct Node *temp = *head, *prev;
    if (temp != NULL && temp->laptop.id == l.id)
    {
        *head = temp->next;
        free(temp);
        return;
    }
    // Gasire id laptop, care sa fie sters;
    while (temp != NULL && temp->laptop.id != l.id)
    {
        prev = temp;
        temp = temp->next;
    }
    // Daca id, nu este prezent;
    if (temp == NULL)
        return;
    // Stergere node;
    prev->next = temp->next;
    free(temp);
}
void printList(struct Node *node)
{
    printf("Elements of Linked list: -->> \n");
    while (node != NULL)
    {
        display(node->laptop);
        node = node->next;
        printf("\n");
    }
}
// Dezalocare Memorie Linked List;
void freeLinkedList(struct Node **head)
{
    struct Node *temp;
    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

int main()
{
    struct Laptop laptop = initializare(101, "Acer Nitro", 32, 256.55, 120.56, 4);
    struct Laptop laptop2 = initializare(102, "MacBook Pro", 64, 512, 99.99, 5);
    struct Laptop laptop3 = initializare(103, "Lenovo", 32, 256.87, 88.99, 3);

    struct Node *head = NULL;
    insertAtBeginning(&head, laptop);
    insertAtBeginning(&head, laptop2);
    insertAtEnd(&head, laptop3);
    deleteNode(&head, laptop);
    printList(head);

    freeMemory(&laptop);
    freeMemory(&laptop2);
    freeMemory(&laptop3);
    freeLinkedList(&head);
    return 0;
}
