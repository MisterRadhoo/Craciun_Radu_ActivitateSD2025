#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Laptop
{
    int id;
    char *nume;
    int RAM;
    float pret;

} L;

L initializare(int id, const char *nume, int RAM, float pret)
{
    L laptop;
    laptop.id = id;
    laptop.nume = (char *)malloc((strlen(nume) + 1) * sizeof(char));
    strcpy(laptop.nume, nume);
    laptop.RAM = RAM;
    laptop.pret = pret;
    return laptop;
}

void printLaptop(L laptop)
{
    printf("\nId: -->> [ %d ], \nNume laptop: [ %s ], \nRAM laptop: -->> [ %d ] GB, \nPret laptop: -->> [ %.2f ] lei.\n", (laptop.id ? laptop.id : -1), laptop.nume, laptop.RAM, laptop.pret);
}

void dezalocareLaptop(L *laptop)
{
    if (laptop->nume != NULL)
    {
        free(laptop->nume);
        laptop->nume = NULL;
        printf("\nfree laptop.....\n");
    }
}

// implementare structura pentru Nod dintr-un ABC;
typedef struct Node
{
    L infoUtil;
    struct Node *st; // Node child left(stanga);
    struct Node *dr; // Node child right(dreapta)

} Node;

int inaltimeABC(Node *rad)
{
    if (rad != NULL)
    {
        int Hs = inaltimeABC(rad->st);
        int Hd = inaltimeABC(rad->dr);
        return 1 + (Hs > Hd ? Hs : Hd);
    }
    else
    {
        return 0;
    }
}

// calculare grad de echilibru; (arbori de echilibrare AVL)
int CGE(Node *rad)
{
    return inaltimeABC(rad->st) - inaltimeABC(rad->dr);
}

void rotireStanga(Node **rad)
{
    Node *aux = (*rad)->dr;
    (*rad)->dr = aux->st;
    aux->st = (*rad);
    (*rad) = aux;
}

void rotireDreapta(Node **rad)
{
    Node *aux2 = (*rad)->st;
    (*rad)->st = aux2->dr;
    aux2->dr = (*rad);
    (*rad) = aux2;
}

void inserareABC(Node **rad, L laptop)
{
    if ((*rad) != NULL)
    {
        if (laptop.id < (*rad)->infoUtil.id)
        {
            inserareABC(&(*rad)->st, laptop);
        }
        else
        {
            inserareABC(&(*rad)->dr, laptop);
        }
        // verificare grad de echilibru;
        int gradEchilibru = CGE(*rad);
        if (gradEchilibru == -2)
        {
            // dezechilibru in partea dreapta;
            if (CGE((*rad)->dr) == 1)
            {
                // dubla rotire;
                rotireDreapta(&(*rad)->dr);
            }
            rotireStanga(rad);
        }
        if (gradEchilibru == 2)
        {
            // dezechilibru in partea stanga;
            if (CGE((*rad)->st) == -1)
            { // dublu rotire;
                rotireStanga(&(*rad)->st);
            }
            rotireDreapta(rad);
        }
    }
    else
    {
        // creare node nou daca rad == NULL;
        Node *nouNode = (Node *)malloc(sizeof(Node));
        nouNode->st = NULL;
        nouNode->dr = NULL;
        nouNode->infoUtil = laptop; // shallow copy;
        nouNode->infoUtil.nume = (char *)malloc((strlen(laptop.nume) + 1) * sizeof(char));
        strcpy(nouNode->infoUtil.nume, laptop.nume);
        (*rad) = nouNode;
    }
}

// Stanga Radacina Dreapta;
void afisareInOrdineABC(Node *rad)
{
    if (rad != NULL)
    {
        afisareInOrdineABC(rad->st);
        printLaptop(rad->infoUtil);
        afisareInOrdineABC(rad->dr);
    }
}
// RSD  // afiseaza valori in ordine crescatoare;
void afisarePreOrdineABC(Node *rad)
{
    if (rad != NULL)
    {
        printLaptop(rad->infoUtil);
        afisarePreOrdineABC(rad->st);
        afisarePreOrdineABC(rad->dr);
    }
}
// SDR;
void afisarePostOrdineABC(Node *rad)
{
    if (rad != NULL)
    {
        afisarePostOrdineABC(rad->st);
        afisarePostOrdineABC(rad->dr);
        printLaptop(rad->infoUtil);
    }
}

void dezalocareABC(Node **rad)
{
    if ((*rad) != NULL)
    {
        dezalocareABC(&(*rad)->st);
        dezalocareABC(&(*rad)->dr);
        dezalocareLaptop(&(*rad)->infoUtil);
        free((*rad));
        (*rad) = NULL;
        printf("\nABC is free.......\n");
    }
}

L getLaptopId(Node *rad, int id)
{
    if (rad != NULL)
    {
        if (id < rad->infoUtil.id)
        {
            return getLaptopId(rad->st, id);
        }
        else if (id > rad->infoUtil.id)
        {
            return getLaptopId(rad->dr, id);
        }
        else
        {
            return rad->infoUtil;
        }
    }
    L empty = {-1, NULL, 0, 0.00};
    printLaptop(empty);
    return empty;
}

float pretTotal(Node *rad)
{
    if (rad == NULL)
    {
        return 0;
    }
    else
    {
        return (rad->infoUtil.pret + pretTotal(rad->st) + pretTotal(rad->dr));
    }
}

int main()
{
    L l1 = initializare(998, "Acer Nitro RX", 16, 3700.00);
    L l2 = initializare(1001, "Acer Nitro 5", 16, 3250.00);
    L l3 = initializare(999, "Lenovo", 32, 3800.59);
    L l4 = initializare(3003, "Dell", 32, 2780.00);
    L l5 = initializare(1007, "Retro PC", 64, 8700.00);
    L l6 = initializare(1005, "Acer Nitro 7", 64, 6500.00);
    L l7 = initializare(2222, "MacBook Air", 32, 5788.00);

    Node *root = NULL;

    inserareABC(&root, l2);
    inserareABC(&root, l1);
    inserareABC(&root, l3);
    inserareABC(&root, l6);
    inserareABC(&root, l5);
    inserareABC(&root, l4);
    inserareABC(&root, l7);

    printf("\nParcurgere ABC InOrdine.....\n");
    afisareInOrdineABC(root);

    printf("\nParcurgere ABC PreOrdine.....\n");
    // afisarePreOrdineABC(root);

    printf("\nParcurgere ABC PostOrdine.........\n");
    afisarePostOrdineABC(root);

    L getId = getLaptopId(root, 3003);
    printLaptop(getId);

    float total = pretTotal(root);
    printf("\nPretul total al laptop-urilor: [ %.2f ] lei \n", total);

    int h = inaltimeABC(root);
    printf("\nInaltime ABC -->> [ %d ] \n", h);

    dezalocareABC(&root);

    return 0;
}