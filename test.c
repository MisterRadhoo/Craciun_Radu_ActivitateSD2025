#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Sticla
{
    int id;
    char *nume;
    char tipBautura[40];
    float capacitate; // u.m. 'litru';

} S;

S initializare(int id, const char *nume, char *tipBautura, float cap)
{
    S sticla;
    sticla.id = id;
    sticla.nume = (char *)malloc((strlen(nume) + 1) * sizeof(char));
    strcpy(sticla.nume, nume);
    strncpy(sticla.tipBautura, tipBautura, 40);
    sticla.tipBautura[39] = '\0';
    sticla.capacitate = cap;
    return sticla;
}

void printSticla(S s)
{
    printf("id: -->> [ %d ], \nNume: -->> [ %s ], \n", s.id, s.nume);
    printf("Tip de bautura: -->> [ %s ], \nCapacitate sticla: -->> [ %.2f ] ml. \n", s.tipBautura, s.capacitate);
}
void dezalocareSticla(S *s)
{
    if (s->nume != NULL)
    {
        free(s->nume);
        s->nume = NULL;
        printf("\nFree sticla memory..... \n");
    }
}

// implemetare Liste simple intanlatuite;
typedef struct Node
{
    S data;
    struct Node *next;

} Node;

void inserareLaInceput(Node **cap, S sticla)
{
    Node *nouNode = (Node *)malloc(sizeof(Node));
    nouNode->data = sticla;
    nouNode->data.nume = (char *)malloc((strlen(sticla.nume) + 1) * sizeof(Node));
    strcpy(nouNode->data, sticla.nume);
    nouNode->next = (*cap);
    (*cap) = nouNode;
}
void inserareLaSfarsit(Node **cap, S sticla)
{
    Node *nouNode = (Node *)malloc(sizeof(Node));
    nouNode->data = sticla;
    nouNode->data.nume = (char *)malloc((strlen(sticla.nume) + 1) * sizeof(char));
    strcpy(nouNode->data.nume, sticla.nume);
    nouNode->next = NULL;
    if ((*cap) != NULL)
    {
        Node *p = (*cap);
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = nouNode;
    }
    else
    {
        (*cap) = nouNode;
    }
}
void inserareLaMijloc(Node *nodAnterior, S sticla)
{
    if (nodAnterior == NULL)
    {
        printf("\nNodul anterior nu poate fii NULL. \n");
        return;
    }
    Node *nouNode = (Node *)malloc(sizeof(Node));
    nouNode->data = sticla;
    nouNode->data.nume = (char *)malloc((strlen(sticla.nume) + 1) * sizeof(char));
    strcpy(nouNode->data.nume, sticla.nume);
    nouNode->next = nodAnterior->next; // se fac legaturile pointer-ilor;
    nodAnterior->next = nouNode;
}
void stergereNod(Node **cap, int id) {}

// parcurgere Lista;
void printLista(Node *cap)
{
    printf("\nLista simpla inlantuita are elementele: \n");
    Node *p = cap;
    while (p != NULL)
    {
        printSticla(p->data);
        printf("\n");
        p = p->next;
    }
}

void stergereLista(Node **cap)
{
    while ((*cap) != NULL)
    {
        Node *p = (*cap);
        (*cap) = (*cap)->next;
        if (p->data.nume != NULL)
        {
            free(p->data.nume);
            printf("\nFree memory lista......\n");
        }
        free(p);
    }
    (*cap) = NULL;
}

int main()
{
    S s = initializare(1, "Greey Goose", "Vodka", 0.70);
    S s1 = initializare(2, "Ciroc", "Vodka", 0.77);
    S s2 = initializare(3, "Beluga", "Vodka", 0.75);
    S s3 = initializare(4, "Old Jack", "wiskey", 1.25);
    S s4 = initializare(5555, "Pirate Black John", "Rum", 0.75);
    S s5 = initializare(6, "Burn Sun", "Tequila", 1.59);
    S s6 = initializare(8888, "Bacardi", "Gin", 0.88);
    // printSticla(s);
    //  dezalocareSticla(&s);

    return 0;
}