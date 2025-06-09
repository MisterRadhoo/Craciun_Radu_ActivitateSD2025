#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Masina
{
    int id;
    char *model;
    char *numeSofer;
    float pret;

} M;

M initializare(int id, const char *model, const char *numeSofer, float pret)
{
    M masina;
    masina.id = id;
    masina.model = (char *)malloc((strlen(model) + 1) * sizeof(char));
    strcpy(masina.model, model);
    masina.numeSofer = (char *)malloc((strlen(numeSofer) + 1) * sizeof(char));
    strcpy(masina.numeSofer, numeSofer);
    masina.pret = pret;
    return masina;
}

void afisareMasina(M masina)
{
    printf("\nId masina: [ %d ]", masina.id);
    printf("\nModel masina: [ %s ]", masina.model);
    printf("\nNume sofer: [ %s ]", masina.numeSofer);
    printf("\nPret masina: [ %.2f ] $\n", masina.pret);
}

void dezalocareMasina(M *masina)
{
    if (masina->model != NULL)
    {
        free(masina->model);
        masina->model = NULL;
    }
    if (masina->numeSofer != NULL)
    {
        free(masina->numeSofer);
        masina->numeSofer = NULL;
        printf("\nfree car.......\n");
    }
}

// implentare structuri Graf-uri;
// stocare in liste de liste;
// lista principala cu Nod-uri;
typedef struct NodPrincipal
{
    M info;
    struct NodSecundar *vecini; // lista simpla inlantuita ce are stocat nodurile adiacente/vecinii ale unui NodPrincipal;
    struct NodPrincipal *next;

} NodPrincipal;

// lista secundara cu Nod-uri;
typedef struct NodSecundar
{
    NodPrincipal *nodInfo; // contine adresa de memorie a unui NodPrincipal din lista principala, pointer la un nod din lista principala;(info);
    struct NodSecundar *next;

} NodSecundar;

// 1. inserarea se face la sfarsitul liste;
void inserareListaPrincipala(NodPrincipal **cap, M masina)
{
    NodPrincipal *nou = (NodPrincipal *)malloc(sizeof(NodPrincipal));
    nou->info = masina; // shallow copy;
    nou->next = NULL;
    nou->vecini = NULL;
    if ((*cap) != NULL)
    {
        NodPrincipal *p = (*cap);
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

// 2. inserarea in lista secundara la inceputul liste simple inlantuite;
void inserareListaSecundara(NodSecundar **cap, NodPrincipal *nodInfo)
{
    NodSecundar *nou = (NodSecundar *)malloc(sizeof(NodSecundar));
    nou->nodInfo = nodInfo;
    nou->next = (*cap);
    (*cap) = nou;
}

// 3. functie care cauta nod dupa ID in lista principala;
NodPrincipal *cautaNodDupaId(NodPrincipal *cap, int id)
{
    while (cap && cap->info.id != id)
    {
        cap = cap->next;
    }
    return cap;
}

// 4. inserare muchie graf;
void inserareMuchie(NodPrincipal *graf, int idStart, int idStop)
{
    NodPrincipal *nodStart = cautaNodDupaId(graf, idStart);
    NodPrincipal *nodStop = cautaNodDupaId(graf, idStop);
    if (nodStart != NULL && nodStop != NULL)
    {
        inserareListaSecundara(&(nodStart->vecini), nodStop); // muchia 1-2;
        inserareListaSecundara(&(nodStop->vecini), nodStart); // muchia 2-1;
    }
}

void dezalocareListaSecundara(NodSecundar **cap)
{
    while (*cap != NULL)
    {
        NodSecundar *aux = (*cap);
        (*cap) = (*cap)->next;
        free(aux);
    }
}

void dezalocareGraf(NodPrincipal **graf)
{
    while ((*graf) != NULL)
    {
        NodPrincipal *temp = (*graf);
        (*graf) = (*graf)->next;
        dezalocareListaSecundara(&(temp->vecini));
        if (temp->info.model != NULL)
        {
            free(temp->info.model);
            temp->info.model = NULL;
        }
        if (temp->info.numeSofer != NULL)
        {
            free(temp->info.numeSofer);
            temp->info.numeSofer = NULL;
        }
        free(temp);
    }
}
// parcurgere in adancime , stocam nodu-urile vizitate adiacente nodului principal [Stiva];
// functii push() & pop() Stiva;

typedef struct NodStiva
{
    int id;
    struct NodStiva *next;

} NodStiva;

// inserare la inceput de lista;
void push(NodStiva **stiva, int id)
{
    NodStiva *nou = (NodStiva *)malloc(sizeof(NodStiva));
    nou->id = id;
    nou->next = (*stiva);
    (*stiva) = nou;
}

int pop(NodStiva **stiva)
{
    if ((*stiva) != NULL)
    {

        NodStiva *p = (*stiva);
        (*stiva) = (*stiva)->next;
        int id = p->id;
        free(p);
        return id;
    }
    else
    {
        return -1;
    }
}

int calculeazaNrNoduriGraf(NodPrincipal *graf)
{
    int count = 0;
    while (graf != NULL)
    {
        count++;
        graf = graf->next;
    }
    return count;
}

void afisareGrafInAdancime(NodPrincipal *graf, int idPlecare)
{
    /*
    1. Este luata o STIVA si un vector de vizitate
    2. Marcam nodul de plecare ca fiind vizitat si il adaugam in STIVA noastra
    3. Pornim parcurgerea care va rula cat timp avem noduri in STIVA
    4.1 Extragem un nod din STIVA
    4.2 Procesam nodul extras din STIVA - il afisam
    4.3. identificam toti vecinii nodului extras care nu sunt vizitati si ii marcam ca vizitati, adugandu-i in STIVA
    4.4 reluam procesul
    */

    // 1.
    int nrNoduri = calculeazaNrNoduriGraf(graf);
    unsigned char *vizitate = (unsigned char *)malloc(sizeof(unsigned char) * nrNoduri);
    for (int i = 0; i < nrNoduri; i++)
    {
        vizitate[i] = 0;
    }
    // 2.
    NodStiva *stiva = NULL;
    vizitate[idPlecare - 1] = 1; // marcam nodul ca fiind vizitat;
    push(&stiva, idPlecare);
    // 3.
    while (stiva != NULL)
    {
        int idNod = pop(&stiva);
        NodPrincipal *nodCurent = cautaNodDupaId(graf, idNod);
        afisareMasina(nodCurent->info);
        NodSecundar *p = nodCurent->vecini;
        while (p)
        {
            if (vizitate[p->nodInfo->info.id - 1] == 0)
            {
                push(&stiva, p->nodInfo->info.id);
                vizitate[p->nodInfo->info.id - 1] = 1;
            }
            p = p->next;
        }
    }
}

// parcurgerea in latime, stocam nodurile vizitate intr-o coada (Queue);
//  implementare functiile enqueue() si dequeue();

typedef struct NodCoada
{
    int id;
    struct NodCoada *next;

} NodCoada;

// inserare la sfarsit de lista;
void enqueue(NodCoada **q, int id)
{
    NodCoada *nouNod = (NodCoada *)malloc(sizeof(NodCoada));
    nouNod->id = id;
    nouNod->next = NULL;
    if (*q)
    {
        NodCoada *p = (*q);
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = nouNod;
    }
    else
    {
        (*q) = nouNod;
    }
}

int dequeue(NodCoada **q)
{
    if ((*q))
    {
        NodCoada *temp = (*q);
        (*q) = (*q)->next;
        int id = temp->id;
        free(temp);
        return id;
    }
    else
    {
        return -1;
    }
}

void afisareGrafInLatime(NodPrincipal *graf, int idPlecare)
{
    int nrNoduri = calculeazaNrNoduriGraf(graf);
    unsigned char *vizitate = (unsigned char *)malloc(sizeof(unsigned char) * nrNoduri);
    for (int i = 0; i < nrNoduri; i++)
    {
        vizitate[i] = 0;
    }
    NodCoada *queue = NULL;
    vizitate[idPlecare - 1] = 1;
    enqueue(&queue, idPlecare);
    while (queue != NULL)
    {
        int idNod = dequeue(&queue);
        NodPrincipal *nodCurent = cautaNodDupaId(graf, idNod);
        afisareMasina(nodCurent->info);
        NodSecundar *p = nodCurent->vecini;
        while (p != NULL)
        {
            if (vizitate[p->nodInfo->info.id - 1] == 0)
            {
                enqueue(&queue, p->nodInfo->info.id);
                vizitate[p->nodInfo->info.id - 1] = 1;
            }
            p = p->next;
        }
    }
}

int main()
{

    M m1 = initializare(1, "Audi A3", "Popescu Virgil", 20000.00);
    M m2 = initializare(2, "Audi A8 GTS", "Popescu Virgil", 110000.00);
    M m3 = initializare(3, "Porsche 911 GT3 RS", "Radu", 235000.99);
    M m4 = initializare(4, "Ferrari F8", "Ana Paun", 250000.00);
    M m5 = initializare(5, "Dacia 1310", "Ion Radu", 15999.00);
    M m6 = initializare(6, "Skoda", "Barbu Ioana", 37888.00);
    M m7 = initializare(7, "Seat", "Popescu Lavinia", 40000.00);
    M m8 = initializare(8, "Lastun", "Ceausescu Marin", 10000.00);
    M m9 = initializare(9, "Dacia Logan", "Andy Preda", 29999.80);
    M m10 = initializare(10, "BMW M3 GTR", "Razvan Marin", 145000.00);

    printf("\nGraf\n");

    NodPrincipal *graf = NULL;
    inserareListaPrincipala(&graf, m1);
    inserareListaPrincipala(&graf, m2);
    inserareListaPrincipala(&graf, m3);
    inserareListaPrincipala(&graf, m4);
    inserareListaPrincipala(&graf, m5);
    inserareListaPrincipala(&graf, m6);
    inserareListaPrincipala(&graf, m7);
    inserareListaPrincipala(&graf, m8);
    inserareListaPrincipala(&graf, m9);
    inserareListaPrincipala(&graf, m10);

    inserareMuchie(graf, 1, 10);
    inserareMuchie(graf, 1, 2);
    inserareMuchie(graf, 1, 3);
    inserareMuchie(graf, 10, 7);
    inserareMuchie(graf, 2, 4);
    inserareMuchie(graf, 3, 5);
    inserareMuchie(graf, 3, 6);
    inserareMuchie(graf, 3, 4);
    inserareMuchie(graf, 7, 8);
    inserareMuchie(graf, 4, 8);
    inserareMuchie(graf, 8, 5);
    inserareMuchie(graf, 5, 9);

    afisareGrafInAdancime(graf, 1);

    printf("\nParcurgere in Latime graf: \n");

    afisareGrafInLatime(graf, 1);

    return 0;
}