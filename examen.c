#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Adidas
{
    int id;
    char *brand;
    float masura;
    float pretUnitar;

} A;

A initializare(int id, const char *brand, float masura, float pret)
{
    A adidas;
    adidas.id = id;
    adidas.brand = (char *)malloc((strlen(brand) + 1) * sizeof(char));
    strcpy(adidas.brand, brand);
    adidas.masura = masura;
    adidas.pretUnitar = pret;
    return adidas;
}

void printAdidas(A adidas)
{
    printf("id:-->> { %d }; \nBrand: -->> { %s }; \nMasura: -->> { %.1f }; \nPret unitar:-->> { %.2f } lei.\n", adidas.id, (adidas.brand ? adidas.brand : NULL), adidas.masura, adidas.pretUnitar);
}

void dezalocareAdidas(A *adidas)
{
    if (adidas->brand != NULL)
    {
        free(adidas->brand);
        adidas->brand = NULL;
        printf("\nDezalocare memorie adidas struct..... \n");
    }
}

// Implementare Lista simpla inlantuita;

typedef struct Nod
{
    A data;
    struct Nod *next;

} Nod;

// implementare strutura Hash Table;
typedef struct HashTable
{
    int dimensiune;
    Nod **vector;

} HT;

void inserareLaInceput(Nod **cap, A adidas)
{
    Nod *nouNod = (Nod *)malloc(sizeof(Nod));
    nouNod->data = adidas; // shallow copy;
    nouNod->data.brand = (char *)malloc((strlen(adidas.brand) + 1) * sizeof(char));
    strcpy(nouNod->data.brand, adidas.brand);
    nouNod->next = (*cap);
    (*cap) = nouNod;
}

void inserareLaSfarsit(Nod **cap, A adidas)
{
    Nod *nou = (Nod *)malloc(sizeof(Nod));
    nou->data = adidas;
    nou->data.brand = (char *)malloc((strlen(adidas.brand) + 1) * sizeof(char));
    strcpy(nou->data.brand, adidas.brand);
    nou->next = NULL;
    if ((*cap) != NULL)
    {

        Nod *p = (*cap);
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = nou;
    }
    else
    {
        (*cap) = nou;
    }
}

void inseraLaMijloc(Nod *nodAnterior, A adidas)
{
    if (nodAnterior == NULL)
    {
        printf("\nNodul anterior nu poate fi NULL. \n");
        return;
    }
    Nod *nouNod = (Nod *)malloc(sizeof(Nod));
    nouNod->data = adidas;
    nouNod->data.brand = (char *)malloc((strlen(adidas.brand) + 1) * sizeof(char));
    strcpy(nouNod->data.brand, adidas.brand);
    nouNod->next = nodAnterior->next;
    nodAnterior->next = nouNod;
}

void stergeNodLista(Nod **cap, int id)
{
    if ((*cap) != NULL)
    {

        if ((*cap)->data.id == id)
        {
            Nod *p = (*cap);
            (*cap) = (*cap)->next; // sterge nod;
            free(p->data.brand);
            free(p);
        }
        else
        {
            Nod *p = (*cap);
            while (p->next != NULL && p->next->data.id != id)
            {
                p = p->next;
            }
            if (p->next == NULL)
            {
                printf("\nid nu exista: [ %d ], \n", id);
                return;
            }
            Nod *aux = p->next;
            p->next = p->next->next; // sterge nod;
            free(aux->data.brand);
            free(aux);
        }
    }
}

// afisare lista;
void printLista(Nod *cap)
{
    printf("\nLista simpla inlantuita are nodurile: \n");
    Nod *p = cap;
    while (p != NULL)
    {
        printAdidas(p->data);
        printf("\n");
        p = p->next;
    }
}

// dezalocare spatiu de memorie pentru lista;
void stergeLista(Nod **cap)
{
    while ((*cap) != NULL)
    {
        Nod *p = (*cap);
        (*cap) = (*cap)->next;
        if (p->data.brand != NULL)
        {
            free(p->data.brand);
            p->data.brand = NULL;
            printf("\nDezalocare memorie lista.....\n");
        }
        free(p);
    }
    (*cap) = NULL;
}
// get adidas by id;
A getAdidasId(Nod *cap, int id)
{
    Nod *temp = cap;
    while (temp != NULL)
    {
        if (temp->data.id == id)
        {
            return temp->data;
        }
        temp = temp->next;
    }
    A empty = {-1, NULL, 0.00, 0};
    printAdidas(empty);
    return empty;
}
// modificare pret articol dupa id;
void modificarePret(Nod *cap, int id, float pretNou)
{
    Nod *aux = cap;
    while (aux != NULL)
    {
        if (aux->data.id == id)
        {
            aux->data.pretUnitar = pretNou;
            printf("\nPretul articolului cu id: [ %d ], a fost modificat, are un pret nou de [ %.2f ] lei. \n", id, pretNou);
        }
        aux = aux->next;
    }
}

float sumaMediePret(Nod *cap)
{
    float suma = 0;
    int contor = 0;
    while (cap != NULL)
    {
        suma += cap->data.pretUnitar;
        contor++;
        cap = cap->next;
    }
    if (contor > 0)
    {
        return suma / contor;
    }
    return 0;
}

// initializare HT;
HT initHT(int dimensiune)
{
    HT ht;
    ht.dimensiune = dimensiune;
    ht.vector = (Nod **)malloc(sizeof(Nod *) * dimensiune);
    for (int i = 0; i < ht.dimensiune; i++)
    {
        ht.vector[i] = NULL;
    }
    return ht;
}
// functia Hash Id+char*brand;
int hash(const char *brand, int id, int dimensiune)
{
    int suma = 0;
    for (int i = 0; i < strlen(brand); i++)
    {
        suma += brand[i];
    }
    suma += id;
    return (dimensiune > 0 ? (suma % dimensiune) : -1);
}

void printHT(HT ht)
{
    for (int i = 0; i < ht.dimensiune; i++)
    {
        printf("\nHashTable Cluster [ %d ]: --->> \n", i);
        printLista(ht.vector[i]);
    }
}

void dezalocareHT(HT *ht)
{
    for (int i = 0; i < ht->dimensiune; i++)
    {
        stergeLista(&(ht->vector)[i]);
        printf("\nHT memory free....\n");
    }
    free(ht->vector);
    ht->vector = NULL;
    ht->dimensiune = 0;
}

void inserareNodHT(HT ht, A adidas)
{
    int index = hash(adidas.brand, adidas.id, ht.dimensiune);
    if (index >= 0 && index < ht.dimensiune)
    {
        if (ht.vector[index] == NULL)
        {
            ht.vector[index] = (Nod *)malloc(sizeof(Nod));
            ht.vector[index]->data = adidas; // shallow copy;
            ht.vector[index]->data.brand = (char *)malloc((strlen(adidas.brand) + 1) * sizeof(char));
            strcpy(ht.vector[index]->data.brand, adidas.brand);
            ht.vector[index]->next = NULL;
        }
        else
        { // avem coliziuni;
            inserareLaSfarsit(&(ht.vector[index]), adidas);
        }
    }
}

void stergeNodHT(HT ht, A adidas)
{
    int index = hash(adidas.brand, adidas.id, ht.dimensiune);
    if (index <= 0 || index > ht.dimensiune)
    {
        printf("\nNod nu exista. \n");
    }
    else
    {
        stergeNodLista(&(ht.vector[index]), adidas.id);
    }
}

float **mediaPretPeCluster(HT ht, int *nrClustere)
{
    (*nrClustere) = 0;
    for (int i = 0; i < ht.dimensiune; i++)
    {
        if (ht.vector[i] != NULL)
        {
            (*nrClustere)++;
        }
    }

    float **medii = (float **)malloc(sizeof(float *) * 2);
    medii[0] = (float *)malloc(sizeof(float) * (*nrClustere));
    medii[1] = (float *)malloc(sizeof(float) * (*nrClustere));
    int index = 0;
    for (int i = 0; i < ht.dimensiune; i++)
    {
        if (ht.vector[i] != NULL)
        {
            medii[0][index] = i;
            medii[1][index] = sumaMediePret(ht.vector[i]);
            index++;
        }
    }
    return medii;
}

void afisareMatrice(float **matrice, int nrCol, int nrLinii)
{
    for (int i = 0; i < nrLinii; i++)
    {
        for (int j = 0; j < nrCol; j++)
        {
            printf(" [ %.2f ] ", matrice[i][j]);
        }
        printf("\n");
    }
}

void dezalocareMatrice(float ***matrice, int *nrCol, int *nrLinii)
{
    for (int i = 0; i < *nrLinii; i++)
    {
        free((*matrice)[i]);
        printf("\nMatrice free.....\n");
    }
    free((*matrice));
    (*matrice) = NULL;
    *nrCol = 0;
    *nrLinii = 0;
}

A getIdAdidas(HT ht, int id)
{
    A adidas;
    for (int i = 0; i < ht.dimensiune; i++)
    {
        adidas = getAdidasId(ht.vector[i], id);
        if (adidas.id == id)
        {
            return adidas;
        }
    }
    A empty = {-1, NULL, 0.00, 0};
    printAdidas(empty);
    return empty;
}

int main()
{
    A a = initializare(1111, "Nike Sb", 42.5, 799.99);
    A a2 = initializare(2222, "Nike Sb x Riot", 45.5, 649.00);
    A a3 = initializare(3333, "Nike Sb x Futura", 42.5, 1899.99);
    A a4 = initializare(4444, "Nike Sb Asparagus", 42.5, 799.99);
    A a5 = initializare(8888, "Nike Sb x Parra", 42.5, 2000.15);
    A a6 = initializare(9999, "Air Jordan Low OG", 43.0, 899.00);
    A a7 = initializare(7777, "Nike Sb Chicago", 42.5, 1099.99);
    A a8 = initializare(5555, "Nike Sb x Carhartt", 41.5, 1399.99);
    A a9 = initializare(11111, "Nike Sb Purple Lobster", 42.5, 3399.99);
    // printAdidas(a2);

    Nod *head = NULL;
    inserareLaInceput(&head, a);
    inserareLaInceput(&head, a2);
    inserareLaSfarsit(&head, a3);
    inserareLaSfarsit(&head, a4);
    inseraLaMijloc(head->next, a5);
    inseraLaMijloc(head->next->next, a6);
    stergeNodLista(&head, 9999);
    printLista(head);

    A idAdidas = getAdidasId(head, 9999);
    modificarePret(head, 4444, 1499.99);
    printLista(head);

    float pretMediu = sumaMediePret(head);
    printf("\nPret mediu: -->> [ %.2f ] lei.\n", pretMediu);

    printf("\n-------------------Hash table data structure.-------------------------- \n");

    HT ht = initHT(9);
    inserareNodHT(ht, a);
    inserareNodHT(ht, a2);
    inserareNodHT(ht, a3);
    inserareNodHT(ht, a4);
    inserareNodHT(ht, a5);
    inserareNodHT(ht, a6);
    inserareNodHT(ht, a7);
    inserareNodHT(ht, a8);
    inserareNodHT(ht, a9);
    stergeNodHT(ht, a);
    printHT(ht);

    A id = getIdAdidas(ht, 11111);
    printAdidas(id);
    printf("\n");
    int nrClustere = 2;
    int nrLinii = 2;
    float **pretMediuMatrice = mediaPretPeCluster(ht, &nrClustere);
    afisareMatrice(pretMediuMatrice, nrClustere, nrLinii);
    dezalocareMatrice(&pretMediuMatrice, &nrClustere, &nrLinii);

    return 0;
}