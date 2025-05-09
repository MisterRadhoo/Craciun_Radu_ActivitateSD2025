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
        // printf("\nFree sticla memory..... \n");
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
    nouNode->data.id = sticla.id;
    nouNode->data.nume = (char *)malloc((strlen(sticla.nume) + 1) * sizeof(char));
    strcpy(nouNode->data.nume, sticla.nume);
    strncpy(nouNode->data.tipBautura, sticla.tipBautura, 40);
    nouNode->data.tipBautura[39] = '\0';
    nouNode->data.capacitate = sticla.capacitate;
    nouNode->next = (*cap);
    (*cap) = nouNode;
}

void inserareLaSfarsit(Node **cap, S sticla)
{
    Node *nouNode = (Node *)malloc(sizeof(Node));
    nouNode->data.id = sticla.id;
    nouNode->data.nume = (char *)malloc((strlen(sticla.nume) + 1) * sizeof(char));
    strcpy(nouNode->data.nume, sticla.nume);
    strncpy(nouNode->data.tipBautura, sticla.tipBautura, 40);
    nouNode->data.tipBautura[39] = '\0';
    nouNode->data.capacitate = sticla.capacitate;
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
    nouNode->data.id = sticla.id;
    nouNode->data.nume = (char *)malloc((strlen(sticla.nume) + 1) * sizeof(char));
    strcpy(nouNode->data.nume, sticla.nume);
    strncpy(nouNode->data.tipBautura, sticla.tipBautura, 40);
    nouNode->data.tipBautura[39] = '\0';
    nouNode->data.capacitate = sticla.capacitate;
    nouNode->next = nodAnterior->next; // se fac legaturile;
    nodAnterior->next = nouNode;
}

void stergereNod(Node **cap, int id)
{
    if ((*cap) != NULL)
    {
        if ((*cap)->data.id == id)
        {
            Node *p = (*cap);
            (*cap) = (*cap)->next; // sterge Node;
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
                printf("\nId: -->> [ %d ] nu exista. \n", id);
                return;
            }
            Node *aux = p->next;
            p->next = p->next->next; // stergere Nod;
            free(aux->data.nume);
            free(aux);
        }
    }
}

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
            p->data.nume = NULL;
            // printf("\nFree memory lista......\n");
        }
        free(p);
    }
    (*cap) = NULL;
}

float medieCap(Node *cap)
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
// implementare HashTable;

typedef struct HashTable
{
    int dimensiune;
    Node **vector; // array;

} HT;

// initializare HashTable;
HT initializareHT(int dimensiune)
{
    HT ht;
    ht.dimensiune = dimensiune;
    ht.vector = (Node **)malloc(dimensiune * sizeof(Node *));
    for (int i = 0; i < ht.dimensiune; i++)
    {
        ht.vector[i] = NULL;
    }
    return ht;
}

void printHT(HT ht)
{
    for (int i = 0; i < ht.dimensiune; i++)
    {

        printf("\nHasHTable Cluster [ %d ]: --->> \n", i);
        printLista(ht.vector[i]);
    }
}

void dezalocareHT(HT *ht)
{
    for (int i = 0; i < ht->dimensiune; i++)
    {
        stergereLista(&(ht->vector[i]));
        printf("\nHT free. \n");
    }
    free(ht->vector);
    ht->vector = NULL;
    ht->dimensiune = 0;
}
// functie hash 1: id + dimensiune;
int hashOneHT(int id, int dimensiune)
{
    return (id % dimensiune);
}

// functie hash 2:  id + char*nume;
int hashTwoHT(const char *nume, int id, int dimensiune)
{
    int suma = 0;
    for (int i = 0; i < strlen(nume); i++)
    {
        suma += nume[i];
    }
    suma += id;
    return (dimensiune > 0 ? (suma % dimensiune) : -1);
}

// inserare noduri in HashTable;
void inserareNodHT(HT ht, S sticla)
{
    int index = hashTwoHT(sticla.nume, sticla.id, ht.dimensiune);
    if (index >= 0 && index < ht.dimensiune)
    {
        if (ht.vector[index] == NULL)
        {
            ht.vector[index] = (Node *)malloc(sizeof(Node));
            ht.vector[index]->data.id = sticla.id;
            ht.vector[index]->data.nume = (char *)malloc((strlen(sticla.nume) + 1) * sizeof(char));
            strcpy(ht.vector[index]->data.nume, sticla.nume);
            strncpy(ht.vector[index]->data.tipBautura, sticla.tipBautura, 40);
            ht.vector[index]->data.tipBautura[39] = '\0';
            ht.vector[index]->data.capacitate = sticla.capacitate;
            ht.vector[index]->next = NULL;
        }
        else
        { // coliziuni;
            inserareLaInceput(&(ht.vector[index]), sticla);
        }
    }
}
S getNumeSticla(Node *cap, const char *numeCautat)
{
    Node *p = cap;
    while (p != NULL)
    {
        if (strcmp(p->data.nume, numeCautat) == 0)
        {
            return p->data;
        }
        p = p->next;
    }
    S s = {-1, NULL, "/", 0};
    printSticla(s);
    return s;
}

S getNumeSticlaHT(HT ht, const char *numeCautat)
{
    S sticla;
    for (int i = 0; i < ht.dimensiune; i++)
    {
        sticla = getNumeSticla(ht.vector[i], numeCautat);
        if (sticla.nume != NULL && strcmp(sticla.nume, numeCautat) == 0)
        {
            return sticla;
        }
    }

    return sticla;
}

S *getSticleCuCapMica(Node *cap, int *dimensiune, float capacitate)
{

    // initializare;
    (*dimensiune) = 0;
    Node *p = cap;
    while (p != NULL)
    {
        if (p->data.capacitate < capacitate)
        {
            (*dimensiune)++;
        }
        p = p->next;
    }
    S *rezultateVector = (S *)malloc((*dimensiune) * sizeof(S));
    int index = 0;
    p = cap;
    while (p != NULL)
    {
        if (p->data.capacitate < capacitate)
        {
            rezultateVector[index] = p->data;
            rezultateVector[index].nume = (char *)malloc((strlen(p->data.nume) + 1) * sizeof(char));
            strcpy(rezultateVector[index].nume, p->data.nume);
            index++;
        }
        p = p->next;
    }

    return rezultateVector;
}

void afisareVector(S *vectorSticle, int dimensiune)
{
    for (int i = 0; i < dimensiune; i++)
    {
        printSticla(vectorSticle[i]);
        printf("\n");
    }
}

float **mediaCapPeClustere(HT ht, int *nrClustere)
{
    (*nrClustere) = 0;
    for (int i = 0; i < ht.dimensiune; i++)
    {
        if (ht.vector[i] != NULL)
        {
            (*nrClustere)++;
        }
    }
    float **matrix = (float **)malloc(sizeof(float *) * 2);
    matrix[0] = (float *)malloc(sizeof(float) * (*nrClustere));
    matrix[1] = (float *)malloc(sizeof(float) * (*nrClustere));
    int index = 0;
    for (int i = 0; i < ht.dimensiune; i++)
    {
        if (ht.vector[i] != NULL)
        {
            matrix[0][index] = i;
            matrix[1][index] = medieCap(ht.vector[i]);
            index++;
        }
    }
    return matrix;
}

void afisareMatrice(float **matrix, int nrCol, int nrLinii)
{
    for (int i = 0; i < nrLinii; i++)
    {
        for (int j = 0; j < nrCol; j++)
        {
            printf("  [ %.2f ]  ", matrix[i][j]);
        }
        printf("\n");
    }
}

void dezalocareMatrice(float ***matrix, int *nrLinii, int *nrCol)
{
    for (int i = 0; i < *nrLinii; i++)
    {
        free((*matrix)[i]);
        printf("\nMatrix free... \n");
    }
    free((*matrix));
    *matrix = NULL;
    *nrLinii = 0;
    *nrCol = 0;
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

    HT ht = initializareHT(10);
    // printHT(ht);

    inserareNodHT(ht, s);
    inserareNodHT(ht, s1);
    inserareNodHT(ht, s2);
    inserareNodHT(ht, s3);
    inserareNodHT(ht, s4);
    inserareNodHT(ht, s5);
    inserareNodHT(ht, s6);
    printHT(ht);

    // dezalocareHT(&ht);

    Node *head = NULL;

    inserareLaInceput(&head, s);
    inserareLaInceput(&head, s1);
    inserareLaInceput(&head, s2);
    inserareLaMijloc(head->next->next, s3);
    inserareLaMijloc(head->next, s4);
    inserareLaSfarsit(&head, s5);
    inserareLaSfarsit(&head, s6);
    printLista(head);
    float mediaCap = medieCap(head);
    printf("\nMedia [ %.2f ] ml \n", mediaCap);

    S getNume = getNumeSticla(head, "Burn Sun");
    printSticla(getNume);

    S getNumeHT = getNumeSticlaHT(ht, "Burn Sun");
    printSticla(getNumeHT);

    printf("\nVector ce contine sticle cu cap. mica: \n");
    int dimensiune = 0;
    S *vectorCapMici = getSticleCuCapMica(head, &dimensiune, 0.85);
    afisareVector(vectorCapMici, dimensiune);

    int nrClustere = 2;
    int nrLinii = 2;
    float **matrice = mediaCapPeClustere(ht, &nrClustere);
    afisareMatrice(matrice, nrClustere, nrLinii);
    dezalocareMatrice(&matrice, &nrLinii, &nrClustere);

    stergereLista(&head);
    dezalocareSticla(&s);
    dezalocareSticla(&s1);
    dezalocareSticla(&s3);

    return 0;
}