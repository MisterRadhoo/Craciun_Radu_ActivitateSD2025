#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Calculator
{

    char *OS;
    int RAM;
    int capacitate;
    float pret;
};
typedef struct Calculator PC;

PC initializare(const char *OS, int RAM, int cap, float pret)
{
    PC pc;
    if (OS != NULL)
    {
        pc.OS = (char *)malloc((strlen(OS) + 1) * sizeof(char));
        if (pc.OS == NULL)
        {
            printf("Alocare de memorie esuata. \n");
            exit(1);
        }
        strcpy(pc.OS, OS);
    }
    else
    {
        pc.OS = NULL;
    }
    pc.RAM = RAM;
    pc.capacitate = cap;
    pc.pret = pret;
    return pc;
}

void display(PC c)
{
    printf("Sistem de operare PC: --->> %s; Memoria RAM %d GBytes. ", c.OS, c.RAM);
    printf("Capacitate de stocare date: -->>>> %d GB, Pretul PC-ul: --->>  %6.2f lei .", c.capacitate, c.pret);
}
void dezalocareMemorie(PC *calculator)
{
    if (calculator->OS != NULL)
    {
        free(calculator->OS);
        calculator->OS = NULL;
    }
}
float mediaPreturilor(PC *calculatoare, int numar)
{
    float suma = 0;
    for (int i = 0; i < numar; i++)
    {
        suma += calculatoare[i].pret;
    }
    return suma / numar;
}
void afisareVector(PC *vector, int nrElem)
{
    for (int i = 0; i < nrElem; i++)
    {
        display(vector[i]);
        printf("\n");
    }
}
void dezalocareVector(PC **vector, int *nrElemente)
{
    for (int i = 0; i < *nrElemente; i++)
    {
        free((*vector)[i].OS);
    }
    free(*vector);
    *nrElemente = 0;
    *vector = NULL;
}
PC getSistemDeOperareNume(PC *calculatorVector, int nrElemente, const char *numeOS)
{
    PC pc;
    for (int i = 0; i < nrElemente; i++)
    {
        if (strcmp(calculatorVector[i].OS, numeOS) == 0)
        {
            pc = calculatorVector[i];
            pc.OS = (char *)malloc((strlen(calculatorVector[i].OS) + 1) * sizeof(char));
            strcpy(pc.OS, calculatorVector[i].OS);
            return pc;
        }
    }
}
struct Nod
{
    PC info;
    struct Nod *next;
};
typedef struct Nod nod;

nod *inserare_inceput(nod *cap, PC c)
{
    // creare nod nod si aloc spatiu de memorie pentru noul node;
    nod *aux = (nod *)malloc(sizeof(nod));
    // atribui data cu parametrul primit;
    aux->info = c;
    // fac legatura catre primul nod al listei;
    aux->next = cap;
    // return primul nou nod ca(cap/HEAD) al listei simple inlantuite;
    return aux;
}
nod *inserare_sfarsit(nod *cap, PC c)
{
    nod *nou = (nod *)malloc(sizeof(nod));
    nou->info = c;
    nou->next = NULL;
    if (cap)
    {
        nod *p = cap;
        while (p->next)
        {
            p = p->next;
        }
        p->next = nou;
    }
    else
    {
        cap = nou;
    }
    return cap;
}
nod *inserare_crescatoare(nod *cap, PC c)
{
    nod *nou = (nod *)malloc(sizeof(nod));
    nou->info = c;
    if (cap)
    {
        if (cap->info.pret > c.pret)
        {
            cap = inserare_inceput(cap, c);
            return cap;
        }
        else
        {
            nod *p = cap;
            while (p->next && p->next->info.pret < c.pret)
            {
                p = p->next;
            }
            nou->next = p->next;
            p->next = nou;
            return cap;
        }
    }
    else
    {
        return nou;
    }
}
nod *stergere(nod *cap, float pret)
{
    if (cap)
    {
        if (cap->info.pret == pret)
        {
            nod *p = cap;
            cap = cap->next;
            free(p->info.OS);
            free(p);
        }
        else
        {
            nod *p = cap;
            while (p->next && p->next->info.pret != pret)
            {
                p = p->next;
            }
            nod *aux = p->next;
            p->next = p->next->next;
            free(aux->info.OS);
            free(aux);
        }
    }
    return cap;
}
nod *stergere_lista(nod *cap)
{

    while (cap)
    {
        nod *p = cap;
        cap = cap->next;
        free(p->info.OS);
        free(p);
        printf("Free\n");
    }
    return NULL;
}
void afisareLista(nod *cap)
{
    nod *p = cap;
    while (p)
    {
        printf("\nPC-ul cu OS -->> %s, costa %5.2f. \n ", p->info.OS, p->info.pret);
        p = p->next;
    }
}
int main()
{

    // Linked List;
    PC c1 = initializare("Windows XP", 8, 256, 1100.00);
    PC c2 = initializare("Ubuntu Linux", 16, 512, 950.77);
    PC c3 = initializare("Mac OS", 8, 128, 1500.99);
    PC c4 = initializare("windows 8", 32, 512, 1700.88);
    PC c5 = initializare("MS-DOS", 4, 64, 550.90);
    PC c6 = initializare("Linux RedHat", 16, 256, 2090.99);
    PC c7 = initializare("Chrome OS", 8, 64, 670.00);

    display(c4);
    printf("\n");
    nod *cap = NULL;

    cap = inserare_inceput(cap, c1);
    cap = inserare_sfarsit(cap, c3);
    cap = inserare_crescatoare(cap, c2);
    cap = inserare_crescatoare(cap, c4);
    cap = inserare_inceput(cap, c7);
    // afisareLista(cap);

    cap = stergere(cap, 1100.00);

    cap = stergere_lista(cap);
    afisareLista(cap);

    // vector alocat dinamic;
    int nrCalculatoare = 3;
    PC *pcs;
    pcs = (PC *)malloc(nrCalculatoare * sizeof(PC)); // Alocare dinamica vector;
    pcs[0] = initializare("Android OS", 16, 128, 2000.50);
    pcs[1] = initializare("Fedora Linux", 8, 64, 450.88);
    pcs[2] = initializare("Windows Vista", 16, 256, 1000.69);
    afisareVector(pcs, nrCalculatoare);

    // media preturilor Calculatoare;
    float mediaPc = mediaPreturilor(pcs, nrCalculatoare);
    printf("Media de preturi este: -->> %.2f lei ", mediaPc);
    PC gasit = getSistemDeOperareNume(pcs, nrCalculatoare, "Windows Vista");
    printf("\nSistem de operare.\n");
    display(gasit);

    dezalocareVector(&pcs, &nrCalculatoare);

    return 0;
}