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
    printf("id:-->> { %d }; \nBrand: -->> { %s }; \nMasura: -->> { %.1f }; \nPret unitar:-->> { %.2f } lei.\n", adidas.id, adidas.brand, adidas.masura, adidas.pretUnitar);
}

void freeAdidas(A *a)
{
    if (a->brand != NULL)
    {
        free(a->brand);
        printf("\nEliberare memorie struct Adidas: \n");
        a->brand = NULL;
    }
}
void afisareVector(A *vectorAdidas, int dimensiune)
{
    for (int i = 0; i < dimensiune; i++)
    {
        printAdidas(vectorAdidas[i]);
        printf("\n");
    }
}
void dezalocareVector(A **a, int *nrElemente)
{
    for (int i = 0; i < *nrElemente; i++)
    {
        free((*a)[i].brand);
        printf("\nFree vector memory.... \n");
    }

    free((*a));
    (*nrElemente) = 0;
    (*a) = NULL;
}

// calculare pret mediul al produselor;
float calculeazaPretMediu(A *adidas, int nrElemente)
{
    float suma = 0;
    for (int i = 0; i < nrElemente; i++)
    {
        suma += adidas[i].pretUnitar;
    }
    return suma / nrElemente;
}
// get adidas dupa brand;
A getAdidasBrand(A *adidas, int nrElemente, const char *brandCautat)
{
    A a;
    for (int i = 0; i < nrElemente; i++)
    {
        if (strcmp(adidas[i].brand, brandCautat) == 0)
        {
            a = adidas[i];
            a.brand = (char *)malloc((strlen(adidas[i].brand) + 1) * sizeof(char));
            strcpy(a.brand, adidas[i].brand);
            return a;
        }
    }
}

// stocare intr-un vector, produsele cu pret = 799.99;
A *copiazaAdidasPretMare(A *adidasVector, int nrElemente, float pret, int *dimensiune)
{
    // Initializare vector bazata pe o conditie;
    (*dimensiune) = 0;
    for (int i = 0; i < nrElemente; i++)
    {
        if (adidasVector[i].pretUnitar == pret)
        {
            (*dimensiune)++;
        }
    }

    A *vectorNou = (A *)malloc(sizeof(A) * (*dimensiune));
    int index = 0;
    for (int i = 0; i < nrElemente; i++)
    {
        if (adidasVector[i].pretUnitar == pret)
        {
            vectorNou[index] = adidasVector[i];
            vectorNou[index].brand = (char *)malloc((strlen(adidasVector[i].brand) + 1) * sizeof(char));
            strcpy(vectorNou[index].brand, adidasVector[i].brand);
            index++;
        }
    }
    return vectorNou;
}

// Liste simpla inlantuita;

// Implemetare Structura Lista;
typedef struct Node
{
    A data;
    struct Node *next; // self-referencial with a same data-type;

} Node; // alias;

void inserareLaInceput(Node **cap, A adidas)
{
    Node *nou = (Node *)malloc(sizeof(Node));
    nou->data = adidas; // shallow copy;
    nou->data.brand = (char *)malloc((strlen(adidas.brand) + 1) * sizeof(char));
    strcpy(nou->data.brand, adidas.brand);
    nou->next = (*cap);
    (*cap) = nou;
}

void inserareLaSfarsit(Node **cap, A adidas)
{
    Node *nouNode = (Node *)malloc(sizeof(Node));
    nouNode->data = adidas;
    nouNode->data.brand = (char *)malloc((strlen(adidas.brand) + 1) * sizeof(char));
    strcpy(nouNode->data.brand, adidas.brand);
    nouNode->next = NULL;
    if ((*cap) != NULL)
    {
        Node *aux = (*cap);
        while (aux->next)
        {
            aux = aux->next;
        }
        aux->next = nouNode;
    }
    else
    {
        (*cap) = nouNode;
    }
}

void printLista(Node *cap)
{
    printf("\nLista are urmatoarele elemente: \n");
    Node *p = cap;
    while (p != NULL)
    {
        printAdidas(p->data);
        p = p->next;
        printf("\n");
    }
}

void stergereLista(Node **cap)
{
    while ((*cap) != NULL)
    {
        Node *p = (*cap);
        (*cap) = (*cap)->next;
        if (p->data.brand != NULL)
        {
            free(p->data.brand);
            printf("\nfree....\n");
        }
        free(p);
    }
}

int main()
{
    A a = initializare(1111, "Nike Sb", 42.5, 799.99);
    printAdidas(a);
    A a2 = initializare(2222, "Nike Sb x Riot", 45.5, 649.00);
    A a3 = initializare(3333, "Nike Sb x Futura", 42.5, 1899.99);
    A a4 = initializare(4444, "Nike Sb Asparagus", 42.5, 799.99);
    A a5 = initializare(8888, "Nike Sb x Parra", 42.5, 2000.15);
    // sa se initialize un vector alocat dinamic.
    int nrAdidasi = 4;
    A *adidasi;
    adidasi = (A *)malloc(sizeof(A) * nrAdidasi);
    adidasi[0] = initializare(1, "Nike Sb Rodeo", 43.5, 699.99);
    adidasi[1] = initializare(2, "Air jordan low OG", 42.5, 799.99);
    adidasi[2] = initializare(3, "Nike Air force 1", 44.5, 649.99);
    adidasi[3] = initializare(4, "Nike Sb Orange Lobster", 42.5, 799.99);
    printf("\nAfisare vector\n");
    afisareVector(adidasi, nrAdidasi);
    float pretMediu = calculeazaPretMediu(adidasi, nrAdidasi);
    printf("\nPretul Mediu al adidasilor este: [ %.2f ] lei \n", pretMediu);

    A brand = getAdidasBrand(adidasi, nrAdidasi, "Nike Sb Rodeo");
    printAdidas(brand);
    freeAdidas(&brand);

    int dimensiune = 0;
    A *a1 = copiazaAdidasPretMare(adidasi, nrAdidasi, 799.99, &dimensiune);
    printf("\nAdidasi cu pret de: 799.99 lei. \n");
    afisareVector(a1, dimensiune);
    dezalocareVector(&adidasi, &nrAdidasi);
    dezalocareVector(&a1, &dimensiune);

    Node *head = NULL;

    inserareLaInceput(&head, a);
    inserareLaInceput(&head, a2);
    inserareLaInceput(&head, a3);
    inserareLaInceput(&head, a4);
    inserareLaSfarsit(&head, a5);
    printLista(head);

    return 0;
}