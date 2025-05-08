#define _CRT_SERCURE_NO_WARNINGS
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

// implementare Lista simpla inlantuita;
typedef struct Node
{
    S data;
    struct Node *next;

} Node;

void inserareLaInceput(Node **cap, S sticla)
{
    Node *nou = (Node *)malloc(sizeof(Node));
    nou->data = sticla;
    nou->data.nume = (char *)malloc((strlen(sticla.nume) + 1) * sizeof(char));
    strcpy(nou->data.nume, sticla.nume);
    nou->next = (*cap);
    (*cap) = nou;
}
void inserareLaSfarsit(Node **cap, S sticla)
{
    Node *nouNod = (Node *)malloc(sizeof(Node));
    nouNod->data = sticla;
    nouNod->data.nume = (char *)malloc((strlen(sticla.nume) + 1) * sizeof(char));
    strcpy(nouNod->data.nume, sticla.nume);
    nouNod->next = NULL;
    if ((*cap) != NULL)
    {
        Node *p = (*cap);
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = nouNod;
    }
    else
    {
        (*cap) = nouNod;
    }
}
void inserareLaMijloc(Node **nodAnterior, S sticla)
{
    if ((*nodAnterior) == NULL)
    {
        printf("Nodul anterior nu poate fi NULL.");
        return;
    }

    Node *nou = (Node *)malloc(sizeof(Node));
    nou->data = sticla;
    nou->data.nume = (char *)malloc((strlen(sticla.nume) + 1) * sizeof(char));
    strcpy(nou->data.nume, sticla.nume);
    nou->next = (*nodAnterior)->next;
    (*nodAnterior)->next = nou;
}

void stergereNode(Node **cap, int id)
{
    if ((*cap))
    {
        if ((*cap)->data.id == id)
        {
            Node *p = (*cap);
            (*cap) = (*cap)->next;
            free(p->data.nume);
            free(p);
        }
        else
        {
            Node *p = (*cap);
            while (p->next != NULL && p->next->data.id != id)
            {
                p = p->next;
            }
            if (p->next == NULL)
            {
                printf("id-ul: -->> [ %d ] nu exista. \n", id);
                return;
            }
            Node *aux = p->next;
            p->next = p->next->next;
            free(aux->data.nume); // sterge Nod;
            free(aux);
        }
    }
}

// parcurgere lista;
void printLista(Node *cap)
{
    printf("\nLista simpla inlatuita are urmatoarele elemente: \n");
    Node *p = cap;
    while (p != NULL)
    {
        printSticla(p->data);
        p = p->next;
        printf("\n");
    }
}

void stergereLista(Node **cap)
{
    while ((*cap) != NULL)
    {
        Node *aux = (*cap);
        (*cap) = (*cap)->next;
        if (aux->data.nume != NULL)
        {
            free(aux->data.nume);
            printf("\nFree....\n");
        }
        free(aux);
    }
    (*cap) = NULL;
}

float calculeazaMediaCap(Node *cap)
{
    float suma = 0;
    int contor = 0;
    while (cap != NULL)
    {
        suma += cap->data.capacitate;
        contor++;
        cap = cap->next;
    }
    if (contor > 0)
    {
        return suma / contor;
    }
    return 0;
}
// schimbare cap. sticla;
void modificaCapSticla(Node *cap, int id, float newCap)
{
    Node *temp = cap;
    while (temp != NULL)
    {
        if (temp->data.id == id)
        {
            temp->data.capacitate = newCap;
            printf("Sticla cu id:  [ %d ], \nAre o noua capacitate de: -->> [ %.2f ] ml. \n", id, newCap);
        }
        temp = temp->next;
    }
}

// get id bootle;
S getByBootle(Node *cap, int id)
{
    while (cap != NULL)
    {
        if (cap->data.id == id)
        {
            return cap->data;
        }
        else
        {
            cap = cap->next;
        }
    }
    S sticla = {-1, NULL, 0, 0};
    printf("\nId sticlei nu a fost gasit. \n");
    printSticla(sticla);
    return sticla;
}

int main()
{
    S s = initializare(1, "Greey Goose", "Vodka", 0.70);
    S s1 = initializare(2, "Ciroc", "Vodka", 0.77);
    S s2 = initializare(3, "Beluga", "Vodka", 0.75);
    S s3 = initializare(4, "Old Jack", "wiskey", 1.25);
    S s4 = initializare(5555, "Pirate Black John", "Rum", 0.75);
    // printSticla(s);
    //  dezalocareSticla(&s);

    Node *head = NULL;
    inserareLaInceput(&head, s);
    inserareLaInceput(&head, s1);
    inserareLaInceput(&head, s2);
    inserareLaSfarsit(&head, s3);
    inserareLaMijloc(&head->next->next, s4);
    stergereNode(&head, 6);
    printLista(head);

    float sticlaCapMedie = calculeazaMediaCap(head);
    printf("\nMedia capacitati sticlelor este:  [%.2f] ml, \n", sticlaCapMedie);
    modificaCapSticla(head, 2, 1.52);
    printLista(head);

    S idSticla = getByBootle(head, 9);

    return 0;
}