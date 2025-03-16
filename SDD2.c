#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Creare Laptop de tip Struct;
struct Laptop
{
    int id;
    int RAM;
    char tipCPU[30];
    float rezolutieEcran;
    int nrTaste;
    int *nrApasariTasta;
};

struct Laptop initializare(int id, int RAM, const char *tipCPU, float rez, int nrTaste)
{
    struct Laptop laptop1;
    laptop1.id = id;
    laptop1.RAM = RAM;
    strncpy(laptop1.tipCPU, tipCPU, 30);
    laptop1.tipCPU[29] = '\0';
    laptop1.rezolutieEcran = rez;
    laptop1.nrTaste = nrTaste;
    laptop1.nrApasariTasta = (int *)malloc(nrTaste * sizeof(int));
    if (laptop1.nrApasariTasta == NULL)
    {
        printf("Nu s-a putut aloca spatiu de memorie !!! \n");
        exit(1); // iesire din program in caz de esec/eroare;
    }
    // initializare valori cu 0;
    for (int i = 0; i < nrTaste; i++)
    {
        laptop1.nrApasariTasta[i] = 0; // cand incepe executia (for loop-ului) , fiecare elemente este setat la 0, asigurande-se ca nu avem valorii aleatorii (garbage values) in memorie si ca fiecare nrTasta incepe de la valoarea setata 0;
    }
    return laptop1;
}

struct Laptop display(struct Laptop l)
{
    printf("ID Laptop: --->> %d \n", l.id);
    printf("Laptop RAM: -->> %d GBytes \n", l.RAM);
    printf("Laptop tip procesor: --->> %s \n", l.tipCPU);
    printf("Rezolutie Laptop: --->> %.2f pixeli \n", l.rezolutieEcran);
    printf("Numar taste laptop: --->> %d \n", l.nrTaste);
    for (int i = 0; i < l.nrTaste; i++)
    {
        printf("nr. apasari de tasta: %d  %d apasari \n", i + 1, l.nrApasariTasta[i]);
    }
}

// Create a node;
struct Node
{
    int data;
    struct Node *next;
};

// insert at beginning;
void insertAtBeginnig(struct Node **head_ref, int newData)
{
    // Alocacare spatiu de memorie pentru noul node, care se insereaza;
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    // insert data item/element;
    newNode->data = newData;
    newNode->next = *head_ref;
    // Move head spre noul node inserat;
    *head_ref = newNode;
}

// insert node dupa alt node;
void insertAfter(struct Node *prev_node, int newData)
{
    if (prev_node == NULL)
    {
        printf(" Node-ul anterior, nu poate fi de valoare NULL: ");
        return;
    }

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    // initializare noul node;
    newNode->data = newData;         // stocam valoarea in noul node,accesand membru de data al struct;
    newNode->next = prev_node->next; // stocam noul node la restul listei, pastrand referinta catre urmatorul node;
    prev_node->next = newNode;       // ponter-ul next al struct Node* next, arata catre adresa de memorie a noului Node;
}

// insert at end, new node;
void insertAtEnd(struct Node **headRef, int newData)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    struct Node *lastNode = *headRef; // used in step 5;
    newNode->data = newData;
    newNode->next = NULL;
    if (*headRef == NULL)
    {
        *headRef = newNode;
        return;
    }
    while (lastNode->next != NULL)
        lastNode = lastNode->next;
    lastNode->next = newNode;
    return;
}

// delete a node;
void deleteNode(struct Node **head, int key)
{
    struct Node *temp = *head, *prev;
    if (temp != NULL && temp->data == key)
    {
        *head = temp->next;
        free(temp); // dezaloca spatiu de memorie pentru pointer-ul temp;
        return;
    }
    // Gasire key,care este selectata sa fie stearsa;
    while (temp != NULL && temp->data != key)
    {
        prev = temp;
        temp = temp->next;
    }
    // if the key is not present in Linked List;
    if (temp == NULL)
        return;
    // remove node;
    prev->next = temp->next;
    free(temp);
}

// Search node in linked List;
int searchNode(struct Node **head, int key)
{
    struct Node *current = *head;
    while (current != NULL)
    {
        if (current->data == key)
            return 1;
        current = current->next;
    }
    return 0;
}
// Sort the linked list in ascending order;
void sortLinkedList(struct Node **head)
{
    struct Node *current = *head, *index = NULL;
    int temp;
    if (*head == NULL)
    {
        return;
    }
    else
    {
        while (current != NULL)
        {
            // index arata(stocheaza) catre pointer-ul next al nodului current;
            index = current->next;
            while (index != NULL)
            {
                if (current->data > index->data)
                {
                    temp = current->data;
                    current->data = index->data;
                    index->data = temp;
                }
                index = index->next;
            }
            current = current->next;
        }
    }
}

// printare Linked List;
void printList(struct Node *node)
{
    printf("\nElementele din Linked List sunt:  \n");
    while (node != NULL)
    {

        printf(" [ %d ]-->> ", node->data);
        node = node->next;
    }
}

int main()
{

    struct Laptop l = initializare(1001, 16, "Intel I7", 77.88, 5);
    // display(l);
    l.nrApasariTasta[0] = 4;
    l.nrApasariTasta[2] = 5;

    display(l);
    free(l.nrApasariTasta);
    l.nrApasariTasta = NULL;

    struct Node *head = NULL;

    insertAtBeginnig(&head, 13);
    insertAtBeginnig(&head, 14);
    insertAtEnd(&head, 21);
    insertAtEnd(&head, 1);
    insertAfter(head->next, 101);
    insertAfter(head->next, 102);

    printList(head);

    int findNode = 4;
    searchNode(&head, findNode);
    if (searchNode(&head, findNode))
    {
        printf("\n %d -->> Element found ", findNode);
    }
    else
    {
        printf(" \n %d -->> Element not found ", findNode);
    }

    insertAtBeginnig(&head, 400);
    printList(head);
    deleteNode(&head, 400);
    printList(head);

    // sortare elemente din Linked list
    sortLinkedList(&head);
    printf("\nSorted Linked List in ascending order: ");
    printList(head);

    return 0;
}