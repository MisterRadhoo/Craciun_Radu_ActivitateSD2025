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

void insertAfterNode(struct Node *previousNode, struct Laptop l)
{
    if (previousNode == NULL)
    {
        printf("Nodul anterior, nu poate fi NULL !!");
        return;
    }

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->laptop = l;
    newNode->next = previousNode->next;
    previousNode->next = newNode;
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
    {
        lastNode = lastNode->next;
    }
    lastNode->next = newNode;
    return;
}

void deleteNode(struct Node **head, int id)
{
    struct Node *temp = *head, *prev = NULL;
    if (temp != NULL && temp->laptop.id == id)
    {
        *head = temp->next;
        freeMemory(&temp->laptop);
        free(temp);
        return;
    }
    // Gasire id laptop, care sa fie sters;
    while (temp != NULL && temp->laptop.id != id)
    {
        prev = temp;
        temp = temp->next;
    }
    // Daca id, nu este prezent;
    if (temp == NULL)
        return;
    // Stergere node;
    prev->next = temp->next;
    freeMemory(&temp->laptop);
    free(temp);
}
int searchNode(struct Node **head, int id)
{
    struct Node *current = *head;
    while (current != NULL)
    {
        if (current->laptop.id == id)
            return 1;
        current = current->next;
    }
    return 0;
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
        freeMemory(&temp->laptop);
        free(temp);
        temp = NULL;
    }
}

int main()
{
    struct Laptop laptop = initializare(101, "Acer Nitro", 32, 256.55, 120.56, 4);
    struct Laptop laptop2 = initializare(102, "MacBook Pro", 64, 512, 99.99, 5);
    struct Laptop laptop3 = initializare(103, "Lenovo", 32, 256.87, 88.99, 3);
    struct Laptop laptop4 = initializare(104, "ASUS Rock", 64, 1024, 156.66, 4);

    laptop2.nrApasariTasta[0] = 8;
    laptop2.nrApasariTasta[2] = 9;
    laptop2.nrApasariTasta[3] = 2;

    laptop4.nrApasariTasta[0] = 3;
    laptop4.nrApasariTasta[1] = 4;
    laptop4.nrApasariTasta[2] = 8;
    laptop4.nrApasariTasta[3] = 12;

    struct Node *head = NULL;
    insertAtBeginning(&head, laptop);
    insertAtBeginning(&head, laptop2);
    insertAfterNode(head->next, laptop4);
    insertAtEnd(&head, laptop3);

    deleteNode(&head, 101);
    printList(head);

    // Cautare Node;
    if (searchNode(&head, 104))
    {
        printf("Gasit. %d \n", laptop4.id);
    }
    else
    {
        printf("Negasit. \n");
    }

    freeLinkedList(&head);
    return 0;
}
