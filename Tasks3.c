#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// Task.8{HashTable.....};

typedef struct Cladire
{
    int idUnic;
    int anulConstruirii;
    char *numeCladire;
    int numarEtaje;

} C;

C initializare(int id, int an, const char *numeCladire, int nrEtaje)
{
    C cladire;
    cladire.idUnic = id;
    cladire.anulConstruirii = an;
    cladire.numeCladire = (char *)malloc((strlen(numeCladire) + 1) * sizeof(char));
    strcpy(cladire.numeCladire, numeCladire);
    cladire.numarEtaje = nrEtaje;
    return cladire;
}
void afisareCladire(C c)
{
    printf("Cladire id:-->> { %d }, Anul in care s-a construit cladirea: -->>[ %d ] \n", c.idUnic, c.anulConstruirii);
    printf("Nume cladire: -->> { %s }, Numar etaje cladire: -->>[ %d ] etaj/e. \n", c.numeCladire, c.numarEtaje);
}

typedef struct Nod
{
    C info;
    struct Nod *next;

} Nod;

typedef struct HashTable
{
    int dimensiune;
    Nod **vector; // array;

} HT;

// afisare lista inlantuita simpla;
void afisareLista(Nod *cap)
{
    // printf("\n Lista simplu inlantuire are elementele: \n");
    while (cap != NULL)
    {
        afisareCladire(cap->info);
        cap = cap->next;
        printf("\n");
    }
}

void inserareInceputLista(Nod **cap, C c)
{
    Nod *nou = (Nod *)malloc(sizeof(Nod));
    nou->info = c; // shallow copy
    nou->next = (*cap);
    (*cap) = nou;
}
// functie numai pentru coliziuni, pe acelasi index in Hash table;
void inserareSfarsitLista(Nod **cap, C c)
{
    Nod *nouNod = (Nod *)malloc(sizeof(Nod));
    nouNod->info = c; // shallow copy;
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
HT initializareHashTable(int dimensiune)
{
    HT ht;
    ht.dimensiune = dimensiune;
    ht.vector = (Nod **)malloc(dimensiune * sizeof(Nod *));
    for (int i = 0; i < dimensiune; i++)
    {
        ht.vector[i] = NULL;
    }
    return ht;
}
// cheie: anul constructie Cladire;
int calculeazaHash(int anConstructie, int dimensiune)
{
    return (anConstructie % dimensiune);
}

// functie de inserare elemente in HashTable + solutie la coliziuni;
void inserareHashTable(HT ht, C cladire)
{
    int index = calculeazaHash(cladire.anulConstruirii, ht.dimensiune);
    // creare nou 'node', data HashTable e null;
    if (index >= 0 && index < ht.dimensiune)
    {
        if (ht.vector[index] == NULL)
        {
            ht.vector[index] = (Nod *)malloc(sizeof(Nod));
            ht.vector[index]->info = cladire;
            ht.vector[index]->next = NULL;
        }
        else
        { // in caz de coliziuni (acelasi index din cluster, are stocate mai multe elemente);
            inserareSfarsitLista(&(ht.vector[index]), cladire);
        }
    }
}

void afisareHashTable(HT ht)
{
    for (int i = 0; i < ht.dimensiune; i++)
    {
        printf("\n Cluster avand index: -->>> [%d]. \n", i);
        afisareLista(ht.vector[i]);
    }
}

void stergereLista(Nod **cap)
{
    while ((*cap) != NULL)
    {
        Nod *p = (*cap);
        (*cap) = p->next;
        if (p->info.numeCladire != NULL)
        {
            free(p->info.numeCladire);
        }
        free(p);
        p->info.numeCladire = NULL;
    }
}

void stergeHashTableMemory(HT *ht)
{
    for (int i = 0; i < ht->dimensiune; i++)
    {
        stergereLista(&(ht->vector[i]));
        printf("\n HT memory free !! \n");
    }
    free(ht->vector);
    ht->vector = NULL;
    ht->dimensiune = 0;
}
void afisareCladiriListeAn(Nod *cap, int anCladire)
{
    Nod *p = cap;
    while (p != NULL)
    {
        if (p->info.anulConstruirii == anCladire)
        {
            afisareCladire(p->info);
        }
        else
        {
            printf("\n NULL \n");
        }

        p = p->next;
    }
}
void afisareCladiriClusterDupaAn(HT ht, int an)
{
    int pozitie = calculeazaHash(an, ht.dimensiune);
    if (ht.vector[pozitie] != NULL)
    {
        afisareCladiriListeAn(ht.vector[pozitie], an);
    }
}

int main()
{

    C c = initializare(11, 1907, "Taverna Racilor", 1);
    C c1 = initializare(12, 1907, "Palatul Ghica", 2);
    C c2 = initializare(13, 1916, "Palatul Victoriei", 3);
    C c3 = initializare(14, 1939, "Hotel Ambasador", 12);
    C c4 = initializare(15, 1820, "Casa Vernescu", 1);
    C c5 = initializare(16, 1947, "Muzeul Zambaccian", 1);
    C c6 = initializare(17, 2012, "Sky Tower Bucuresti", 37);
    C c7 = initializare(18, 2018, "Global Worth Bucuresti", 25);
    C c8 = initializare(19, 1957, "Casa Presei", 20);
    C c9 = initializare(20, 1808, "Hanul lui Manuc", 1);
    C c10 = initializare(21, 1989, "Casa Poporului", 3);

    HT ht = initializareHashTable(10);
    inserareHashTable(ht, c);
    inserareHashTable(ht, c2);
    inserareHashTable(ht, c1);
    inserareHashTable(ht, c3);
    inserareHashTable(ht, c4);
    inserareHashTable(ht, c5);
    inserareHashTable(ht, c6);
    inserareHashTable(ht, c7);
    inserareHashTable(ht, c8);
    inserareHashTable(ht, c9);
    inserareHashTable(ht, c10);
    // afisareHashTable(ht);

    afisareCladiriClusterDupaAn(ht, 1989);
    stergeHashTableMemory(&ht);
    // afisareHashTable(ht);

    return 0;
}