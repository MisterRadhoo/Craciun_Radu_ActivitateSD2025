#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Calculator
{
    int id;
    char *nume;
    int RAM;
    int capacitate;
} PC;

PC initializare(int id, const char *nume, int RAM, int capacitate)
{
    PC pc;
    pc.id = id;
    // deep-copy pentru pointer *nume;
    if (nume != NULL)
    {
        pc.nume = (char *)malloc((strlen(nume) + 1) * sizeof(char));
        if (pc.nume == NULL)
        {
            printf("Nu s-a putut aloca memorie !\n");
            exit(1);
        }
        strcpy(pc.nume, nume);
    }
    else
    {
        pc.nume = NULL;
    }
    pc.RAM = RAM;
    pc.capacitate = capacitate;

    return pc;
}
void display(PC pc)
{
    printf("Calculator ID: --->> %d, Calculator nume: --->> %s \n", pc.id, pc.nume);
    printf("Calculator RAM: --->> %d GBytes, Calculator spatiu de stocare: --->> %d GB \n", pc.RAM, pc.capacitate);
}
void dezalocareMemorie(PC *pc)
{
    if (pc->nume != NULL)
    {
        free(pc->nume);
        pc->nume = NULL;
    }
}
// Creare Nod, Liste dublu inlantuite;
typedef struct nodLDI
{
    PC info;
    struct nodLDI *next;
    struct nodLDI *previous;
} nodLDI;

// Creare Structura, Liste dublu inlantuite;
typedef struct LDI
{
    nodLDI *primul;
    nodLDI *ultimul;
} LDI;
void inserare_inceput(LDI *lista, PC c)
{
    // Creare nou node LDI;
    nodLDI *nou = (nodLDI *)malloc(sizeof(nodLDI));
    nou->info = c;
    nou->next = nou->previous = NULL;
    if (lista->primul == NULL)
    {
        lista->primul = lista->ultimul = nou;
    }
    else
    {
        nou->next = lista->primul;
        lista->primul->previous = nou;
        lista->primul = nou;
    }
}

void inserare_sfarsit(LDI *lista, PC c)
{
    nodLDI *nou = (nodLDI *)malloc(sizeof(nodLDI));
    nou->info = c;
    nou->next = nou->previous = NULL;
    if (lista->primul == NULL)
    {
        lista->primul = lista->ultimul = nou;
    }
    else
    {
        nou->previous = lista->ultimul;
        lista->ultimul->next = nou;
        lista->ultimul = nou;
    }
}
// sterge primul Node din LDI;
PC extragereDeLaInceput(LDI *lista)
{
    if (lista->primul)
    {
        PC pc = lista->primul->info;
        nodLDI *p = lista->primul;
        lista->primul = lista->primul->next;
        if (lista->primul == NULL)
            lista->ultimul = NULL;
        free(p);
        return pc;
    }
}
void dezalocareLDCalculatoare(LDI *lista)
{
    while (lista->primul->next)
    {
        lista->primul = lista->primul->next;
        free(lista->primul->previous->info.nume);
        free(lista->primul->previous);
        printf("Memorie dezalocata.\n");
    }
    free(lista->ultimul->info.nume);
    free(lista->ultimul);
    lista->primul = NULL;
    lista->ultimul = NULL;
}

void parcurgereLista(LDI *lista)
{
    nodLDI *p = lista->primul;
    while (p)
    {
        printf("Calculatorul are %d RAM si %d spatiu de stocare \n", p->info.RAM, p->info.capacitate);
        p = p->next;
    }
}
void parcurgereInversa(LDI *lista)
{
    nodLDI *p = lista->ultimul;
    while (p)
    {
        printf("Calculatorul are %d RAM si %d spatiu de stocare \n", p->info.RAM, p->info.capacitate);
        p = p->previous;
    }
}
int main()
{
    PC c = initializare(10, "Lenovo PC", 64, 256);
    PC c1 = initializare(11, "MacBook Air", 32, 512);
    PC c2 = initializare(12, "Acer", 64, 1024);
    PC c3 = initializare(13, "Dell", 16, 256);
    PC c4 = initializare(14, "Alienware Dell", 128, 2048);
    PC c5 = initializare(15, "Sony Vaio", 16, 128);
    display(c2);
    LDI *lista = (LDI *)malloc(sizeof(LDI));
    lista->primul = NULL;
    lista->ultimul = NULL;
    inserare_inceput(lista, c5);
    inserare_inceput(lista, c);
    inserare_inceput(lista, c1);
    inserare_sfarsit(lista, c2);
    inserare_sfarsit(lista, c3);
    inserare_sfarsit(lista, c4);

    parcurgereInversa(lista);
    PC extragere = extragereDeLaInceput(lista);
    parcurgereLista(lista);
    dezalocareMemorie(&extragere);
    dezalocareLDCalculatoare(lista);
    return 0;
}