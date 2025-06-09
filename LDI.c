#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Calculator
{
    int id;
    char *brand;
    float pret;

} PC;

PC initializare(int id, const char *nume, float pret)
{
    PC pc;
    pc.id = id;
    pc.brand = (char *)malloc((strlen(nume) + 1) * sizeof(char));
    strcpy(pc.brand, nume);
    pc.pret = pret;
    return pc;
}

void afisarePC(PC pc)
{
    printf("\nId: [ %d ]; Brand PC: [ %s ]; Pret: -->> [ %.2f ] lei. \n", pc.id, pc.brand, pc.pret);
}

// implementare Liste dubla inlantuita;
typedef struct Nod Nod;
typedef struct LDI LDI;

struct Nod
{
    PC info;
    Nod *next;
    Nod *prev;
};

struct LDI
{
    Nod *prim;
    Nod *ultim;
    int nrNoduri;
};

void dezalocare(PC *pc)
{
    if (pc->brand != NULL)
    {
        free(pc->brand);
        pc->brand = NULL;
        printf("\nfree....PC...\n");
    }
}

void parcurgereLista(LDI *lista)
{
    printf("\nLista dubla inlantuita are elementele: \n");
    Nod *p = lista->prim;
    while (p != NULL)
    {
        afisarePC(p->info);
        p = p->next;
        printf("\n");
    }
}

void parcurgereInversa(LDI *lista)
{
    printf("\nParcurgere inversa LDI:  \n");
    Nod *p = lista->ultim;
    while (p != NULL)
    {
        afisarePC(p->info);
        p = p->prev;
        printf("\n");
    }
}

void inserareLaSfarsitLDI(LDI *lista, PC pc)
{
    Nod *nouNode = (Nod *)malloc(sizeof(Nod));
    nouNode->info = pc; // shallow copy;
    nouNode->next = NULL;
    nouNode->prev = lista->ultim;
    if (lista->ultim != NULL)
    {
        lista->ultim->next = nouNode;
    }
    else
    {
        lista->prim = nouNode;
    }
    lista->ultim = nouNode;
    lista->nrNoduri++;
}

void inserareLaInceputLDI(LDI *lista, PC pc)
{
    Nod *nou = (Nod *)malloc(sizeof(Nod));
    nou->info = pc; // shallow copy;
    nou->next = lista->prim;
    nou->prev = NULL;
    if (lista->prim != NULL)
    {
        lista->prim->prev = nou;
    }
    else
    {
        lista->ultim = nou;
    }
    lista->prim = nou;
    lista->nrNoduri++;
}
// sterge Nod dupa id din LDI;
void stergeNodLDI(LDI *lista, int id)
{
    if (lista->prim == NULL)
    {
        return;
    }
    Nod *p = lista->prim;
    while (p != NULL && p->info.id != id)
    {
        p = p->next;
    }
    if (p == NULL)
    {
        return;
    }

    // avem ce sa stergem ?
    if (p->prev == NULL)
    {
        lista->prim = p->next; // pointer next arata catre urmatorul nod; devine cap de lista;
        if (lista->prim != NULL)
        {
            lista->prim->prev = NULL; // pointer prev la nod cap LDI va fi nuLl;
        }
    }
    else
    {
        p->prev->next = p->next; // sterge nod la mijloc intre doua noduri;
    }
    if (p->next != NULL)
    {
        p->next->prev = p->prev; // legatura facuta in sens invers, daca *p nu este ultimul nod;
    }
    else
    {
        lista->ultim = p->prev;
    }
    if (p->info.brand != NULL)
    {
        free(p->info.brand);
    }
    free(p);
    lista->nrNoduri--;
}

float calculeazaPretMediu(LDI *lista)
{
    if (lista->nrNoduri > 0)
    {
        float suma = 0;
        Nod *p = lista->prim;
        while (p)
        {
            suma += p->info.pret;
            p = p->next;
        }
        return suma / lista->nrNoduri;
    }
    return 0;
}

void dezalocareLDI(LDI *lista)
{
    Nod *p = lista->prim;
    while (p != NULL)
    {
        Nod *aux = p;
        p = p->next;
        if (aux->info.brand != NULL)
        {
            free(aux->info.brand);
            printf("\nFree ldi....\n");
        }
        free(aux);
    }
    lista->prim = NULL;
    lista->ultim = NULL;
    lista->nrNoduri = 0;
}

char *getBrandScumpPC(LDI *lista)
{
    if (lista->prim != NULL)
    {
        Nod *max = lista->prim;
        Nod *p = lista->prim->next;
        while (p)
        {
            if (p->info.pret > max->info.pret)
            {
                max = p;
            }
            p = p->next;
        }
        char *brand1 = (char *)malloc((strlen(max->info.brand) + 1) * sizeof(char));
        strcpy(brand1, max->info.brand);
        return brand1;
    }
    else
    {
        return NULL;
    }
}

int main()
{
    PC pc1 = initializare(1, "Lenovo", 2599.99);
    PC pc2 = initializare(2, "Acer", 2999.99);
    PC pc3 = initializare(3, "Dell", 1599.99);
    PC pc4 = initializare(4, "Toshiba", 2199.99);
    PC pc5 = initializare(5, "Fujitsu", 4299.99);
    PC pc6 = initializare(6, "MSI", 5599.99);
    PC pc7 = initializare(7, "Alienware", 13200.99);
    PC pc8 = initializare(8, "Acer Nitro", 4599.99);

    LDI lista;
    lista.prim = NULL;
    lista.ultim = NULL;
    lista.nrNoduri = 0;

    inserareLaInceputLDI(&lista, pc1);
    inserareLaInceputLDI(&lista, pc2);
    inserareLaInceputLDI(&lista, pc3);
    inserareLaInceputLDI(&lista, pc4);
    inserareLaSfarsitLDI(&lista, pc8);
    inserareLaSfarsitLDI(&lista, pc5);
    inserareLaInceputLDI(&lista, pc6);
    inserareLaInceputLDI(&lista, pc7);

    parcurgereInversa(&lista);

    stergeNodLDI(&lista, 7);

    parcurgereLista(&lista);

    printf("\nPretul Mediu al PC-urilor: \n");
    float pretMediu = calculeazaPretMediu(&lista);
    printf("\n [ %.2f ] lei ", pretMediu);
    char *scump = getBrandScumpPC(&lista);
    printf("\nCel mai scump PC este: [ %s ].\n", scump);
    if (scump)
    {
        free(scump);
    }
    dezalocareLDI(&lista);
    return 0;
}