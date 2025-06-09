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

void dezalocarePC(PC *pc)
{
    if (pc->brand != NULL)
    {
        free(pc->brand);
        pc->brand = NULL;
        printf("\nfree pc....\n");
    }
}

// implementare struct Liste simple inlantuite;
typedef struct Nod
{
    PC info;
    struct Nod *next;

} Nod;

void inserareLaInceput(Nod **cap, PC pc)
{
    Nod *nou = (Nod *)malloc(sizeof(Nod));
    nou->info = pc; // shallow copy;
    nou->next = (*cap);
    (*cap) = nou;
}

void inserareLaSfarsit(Nod **cap, PC pc)
{
    Nod *nouNod = (Nod *)malloc(sizeof(Nod));
    nouNod->info = pc; // shallow copy;
    nouNod->next = NULL;
    if ((*cap) != NULL)
    {
        Nod *p = (*cap);
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

void stergereNod(Nod **cap, int id)
{
    if ((*cap) != NULL)
    {
        if ((*cap)->info.id == id)
        {
            Nod *p = (*cap);
            (*cap) = (*cap)->next;
            free(p->info.brand);
            free(p);
        }
        else
        {
            Nod *p = (*cap);
            while (p->next != NULL && p->next->info.id != id)
            {
                p = p->next;
            }
            if (p->next == NULL)
            {
                return;
            }
            Nod *aux = p->next;
            p->next = p->next->next; // sterge nod;
            free(aux->info.brand);
            free(aux);
        }
    }
}

void parcuregeLista(Nod *cap)
{
    printf("\nLista simpla inlantuita are elemente: ");
    Nod *p = cap;
    while (p != NULL)
    {
        afisarePC(p->info);
        p = p->next;
        printf("\n");
    }
}

void stergereLista(Nod **cap)
{
    while ((*cap) != NULL)
    {
        Nod *p = (*cap);
        (*cap) = (*cap)->next;
        if (p->info.brand != NULL)
        {
            free(p->info.brand);
            printf("\nFree liste.....\n");
        }
        free(p);
    }
    (*cap) = NULL;
}
float calculeazaPretMediu(Nod *cap)
{

    float suma = 0;
    int contor = 0;
    while (cap != NULL)
    {
        suma += cap->info.pret;
        contor++;
        cap = cap->next;
    }
    if (contor > 0)
    {
        return suma / contor;
    }
    return 0;
}

PC getPCdinLista(Nod *cap, const char *brand)
{
    PC pc;
    pc.id = -1;
    while (cap && strcmp(cap->info.brand, brand) != 0)
    {
        cap = cap->next;
    }
    if (cap)
    {
        pc = cap->info;
        pc.brand = (char *)malloc((strlen(cap->info.brand) + 1) * sizeof(char));
        strcpy(pc.brand, cap->info.brand);
    }
    return pc;
}
PC getPCbyId(Nod *cap, int idCautat)
{
    Nod *temp = cap;
    while (temp != NULL)
    {
        if (temp->info.id == idCautat)
        {
            return temp->info; // shallow copy;
        }
        else
        {
            temp = temp->next;
        }
    }
    PC pc;
    pc.id = -1;
    return pc;
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

    // initializare Liste;
    Nod *head = NULL;

    inserareLaInceput(&head, pc1);
    inserareLaInceput(&head, pc2);
    inserareLaInceput(&head, pc3);
    inserareLaSfarsit(&head, pc4);
    inserareLaSfarsit(&head, pc5);
    inserareLaSfarsit(&head, pc6);
    inserareLaSfarsit(&head, pc7);
    inserareLaInceput(&head, pc8);

    parcuregeLista(head);
    float pretMediu = calculeazaPretMediu(head);
    printf("\nPretul Mediu este: [ %.2f ] lei. \n", pretMediu);

    PC pcCautat = getPCdinLista(head, "Alienware");
    if (pcCautat.id != -1)
    {
        printf("\nPC-ul cautat: \n");
        afisarePC(pcCautat);
        if (pcCautat.brand != NULL)
        {
            free(pcCautat.brand);
        }
    }
    else
    {
        printf("\nPC-ul nu a fost gasit!\n");
    }

    PC idPC = getPCbyId(head, 12);
    if (idPC.id != -1)
    {
        printf("\nId gasit in liste.\n");
        afisarePC(idPC);
    }
    else
    {
        printf("\nId-ul nu a fost gasit in sistem.\n");
    }
    // stergere nod-uri din liste;
    stergereNod(&head, 1);
    stergereNod(&head, 2);
    stergereNod(&head, 3);
    stergereNod(&head, 4);
    stergereNod(&head, 5);
    stergereNod(&head, 6);

    parcuregeLista(head);
    stergereLista(&head);

    return 0;
}