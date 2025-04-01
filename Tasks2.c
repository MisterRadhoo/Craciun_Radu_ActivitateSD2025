#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Calculator
{
    int id;
    char *brand;
    // char *OS;         // Operating System;
    char CPU[50];
    int RAM;
    int capacitate;
    float pret;

} PC;

PC initializare(int id, char *brand, char *CPU, int RAM, int cap, float pret)
{
    PC calculator;
    calculator.id = id;
    calculator.brand = (char *)malloc((strlen(brand) + 1) * sizeof(char));
    strcpy(calculator.brand, brand);
    strncpy(calculator.CPU, CPU, 50);
    calculator.CPU[49] = '\0';
    calculator.RAM = RAM;
    calculator.capacitate = cap;
    calculator.pret = pret;
    return calculator;
}
void display(PC pc)
{
    printf("Calculator ID: %d \n", pc.id);
    printf("Calculator Brand: %s \n", pc.brand);
    printf("Calculator CPU: %s \n", pc.CPU);
    printf("Calculator RAM: %d Gbytes \n", pc.RAM);
    printf("Calculator, capacitate de stocare de: %d GB \n", pc.capacitate);
    printf("Calculator, pret: %.2f  $ \n", pc.pret);
}

// Nod Lista dublu inlantuita;
typedef struct Nod
{
    PC info;
    struct Nod *next;
    struct Nod *prev;

} Nod;
// Creare structura Lista dublu inlantuita;
typedef struct LDI
{
    Nod *prim;
    Nod *ultim;
    int nrNoduri;

} LDI;

void parcurgereLista(LDI *lista)
{
    printf("\nLista dublu inlantuita are elementele: -->> \n");
    Nod *p = lista->prim;
    int i = 0;
    while (p)
    {
        printf("\nNumar Nod: %d\n", i);
        i++;
        display(p->info);
        p = p->next;
    }
}

void parcurgereInversa(LDI *lista)
{
    printf("\nParcurgere inversa a Listei dublu inlantuite: -->>\n");
    Nod *p = lista->ultim;
    while (p)
    {
        display(p->info);
        p = p->prev;
        printf("\n");
    }
}

void inserareLaSfarsitLDI(LDI *lista, PC pc)
{
    Nod *nou = (Nod *)malloc(sizeof(Nod));
    nou->info = pc;
    nou->info.brand = (char *)malloc(sizeof(char) * (strlen(pc.brand) + 1));
    strcpy(nou->info.brand, pc.brand);
    nou->next = NULL;
    nou->prev = lista->ultim;
    if (lista->ultim != NULL)
    {
        lista->ultim->next = nou;
    }
    else
    {
        lista->prim = nou;
    }
    lista->ultim = nou;
    lista->nrNoduri++;
}

void inserareLaInceputLDI(LDI *lista, PC pc)
{
    Nod *nou = (Nod *)malloc(sizeof(Nod));
    nou->info = pc;
    nou->info.brand = (char *)malloc((strlen(pc.brand) + 1) * sizeof(char));
    strcpy(nou->info.brand, pc.brand);
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
// stergere nod dupa id;
void stergereNodLDIdupaId(LDI *lista, int id)
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
        lista->prim = p->next;
        if (lista->prim != NULL)
        {
            lista->prim->prev = NULL;
        }
    }
    else
    {
        p->prev->next = p->next;
    }
    if (p->next != NULL)
    {
        p->next->prev = p->prev;
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

void dezalocareMemorieLDI(LDI *lista)
{
    Nod *p = lista->prim;
    while (p != NULL)
    {
        Nod *aux = p;
        p = p->next;
        if (aux->info.brand != NULL)
        {
            free(aux->info.brand);
            printf("\nFree Memory LDI: \n");
        }
        free(aux);
    }
    lista->prim = NULL;
    lista->ultim = NULL;
    lista->nrNoduri = 0;
}
float calculeazaPretMediu(LDI *lista)
{
    if (lista->nrNoduri > 0)
    {
        float suma = 0;
        Nod *p = lista->prim;
        while (p != NULL)
        {
            suma += p->info.pret;
            p = p->next;
        }
        return suma / lista->nrNoduri;
    }
    return 0;
}
char *getBrandCelMaiScumpPC(LDI *lista)
{
    if (lista->prim != NULL)
    {
        Nod *max = lista->prim;
        Nod *p = lista->prim->next;

        while (p != NULL)
        {
            if (p->info.pret > max->info.pret)
            {
                max = p;
            }
            p = p->next;
        }

        char *brand1 = (char *)malloc((strlen(max->info.brand)) + 1 * sizeof(char));
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
    // Liste dublu inlantuite;
    PC pc1 = initializare(100, "Asus NoteBook 3T", "Intel I9", 16, 256, 520.34);
    PC pc2 = initializare(101, "Acer Nitro 5", "AMD Duron x8", 32, 512, 640.00);
    PC pc3 = initializare(102, "Dell Alienware", "Intel i9 Turbo", 64, 1024, 1282.89);
    PC pc4 = initializare(103, "Lenovo Legion", "AMD e15", 32, 512, 880.32);
    PC pc5 = initializare(104, "Dell", "Intel i3", 16, 256, 456.44);
    PC pc6 = initializare(204, "MacBook Pro 4P", "Apple M3", 32, 512, 1029.99);
    PC pc7 = initializare(205, "Lenovo Power Pro", "Inter i7 Turbo", 64, 1024, 1424.55);
    PC pc8 = initializare(206, "Toshiba Quad", "AMD Ryzen", 32, 1024, 724.85);

    LDI lista;
    lista.prim = NULL;
    lista.ultim = NULL;
    lista.nrNoduri = 0;
    inserareLaInceputLDI(&lista, pc1);
    inserareLaInceputLDI(&lista, pc2);
    inserareLaInceputLDI(&lista, pc3);
    inserareLaSfarsitLDI(&lista, pc4);
    inserareLaSfarsitLDI(&lista, pc5);
    inserareLaInceputLDI(&lista, pc6);
    inserareLaInceputLDI(&lista, pc7);
    inserareLaSfarsitLDI(&lista, pc8);
    parcurgereLista(&lista);
    stergereNodLDIdupaId(&lista, 206);
    printf("\nPretul mediu al PC-urilor %.3f $:\n", calculeazaPretMediu(&lista));
    parcurgereInversa(&lista);

    char *brandPC = getBrandCelMaiScumpPC(&lista);
    printf("\nBrand PC, cel mai scump:-->> %s \n", brandPC);
    if (brandPC != NULL)
    {
        free(brandPC);
    }
    dezalocareMemorieLDI(&lista);
    return 0;
}