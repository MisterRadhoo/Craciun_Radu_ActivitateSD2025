#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// Task.8{HashTable};

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
void afisareVecor(C *cladiri, int dimensiune)
{
    for (int i = 0; i < dimensiune; i++)
    {
        afisareCladire(cladiri[i]);
        printf("\n");
    }
}
void dezalocareVector(C **c, int *dimensiune)
{
    for (int i = 0; i < *dimensiune; i++)
    {
        free((*c)[i].numeCladire);
        printf("\nFree vector cladire.\n");
    }
    free((*c));
    (*c) = NULL;
    *dimensiune = 0;
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
    nou->info.numeCladire = (char *)malloc((strlen(c.numeCladire) + 1) * sizeof(char));
    strcpy(nou->info.numeCladire, c.numeCladire);
    nou->next = (*cap);
    (*cap) = nou;
}
// functie numai pentru coliziuni, pe acelasi index in Hash table;
void inserareSfarsitLista(Nod **cap, C c)
{
    Nod *nouNod = (Nod *)malloc(sizeof(Nod));
    nouNod->info = c; // shallow copy;
    nouNod->info.numeCladire = (char *)malloc((strlen(c.numeCladire) + 1) * sizeof(char));
    strcpy(nouNod->info.numeCladire, c.numeCladire);
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
// stergere Nod lista dupa id+anConstructie;
void stergeNodLista(Nod **cap, int id, int anConstructie)
{
    if ((*cap) != NULL)
    {
        if ((*cap)->info.idUnic == id && (*cap)->info.anulConstruirii == anConstructie)
        {
            Nod *p = (*cap);
            (*cap) = (*cap)->next;
            free(p->info.numeCladire);
            free(p);
        }
        else
        {
            Nod *p = (*cap);
            while (p->next != NULL && (p->next->info.idUnic != id || p->next->info.anulConstruirii != anConstructie))
            {
                p = p->next;
            }
            if (p->next == NULL)
            {
                printf("Cladirea cu Id si an constructie: --->> [%d], [%d] NU EXISTA. \n", id, anConstructie);
                return;
            }
            Nod *aux = p->next;
            p->next = p->next->next;
            free(aux->info.numeCladire);
            free(aux);
        }
    }
}
// functie care sterge Nod din lista dupa'id';
void removeNodById(Nod **cap, int id)
{
    if ((*cap) != NULL)
    {
        if ((*cap)->info.idUnic == id)
        {
            Nod *p = (*cap);
            (*cap) = (*cap)->next;
            free(p->info.numeCladire);
            free(p);
        }
        else
        {
            Nod *p = (*cap);
            while (p->next != NULL && p->next->info.idUnic != id)
            {
                p = p->next;
            }
            if (p->next == NULL)
            {
                printf("Node Id: -->> [%d] nu exista. \n", id);
                return;
            }
            Nod *aux = p->next;
            p->next = p->next->next;
            free(aux->info.numeCladire);
            free(aux);
        }
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
            ht.vector[index]->info.idUnic = cladire.idUnic;
            ht.vector[index]->info.anulConstruirii = cladire.anulConstruirii;
            ht.vector[index]->info.numeCladire = (char *)malloc((strlen(cladire.numeCladire) + 1) * sizeof(char));
            strcpy(ht.vector[index]->info.numeCladire, cladire.numeCladire);
            ht.vector[index]->info.numarEtaje = cladire.numarEtaje;
            // ht.vector[index]->info = cladire;  // shallow copy;
            ht.vector[index]->next = NULL;
        }
        else
        { // in caz de coliziuni (acelasi index din cluster, are stocate mai multe elemente);
            inserareSfarsitLista(&(ht.vector[index]), cladire);
        }
    }
}
// stergere Element HT, dupa id+anConstructie;
void stergereElementHashTable(HT ht, int id, int an)
{
    int index = calculeazaHash(an, ht.dimensiune);
    if (index < 0 || index >= ht.dimensiune)
    {
        printf("\nIndex de negasit.\n");
    }
    else
    {
        stergeNodLista(&(ht.vector[index]), id, an);
    }
}
// stergere Element HT, dupa id;
void removeElementFromHTbyId(HT ht, int id)
{
    for (int i = 0; i < ht.dimensiune; i++)
    {
        if (ht.vector[i] != NULL)
        {
            removeNodById(&(ht.vector[i]), id);
        }
    }
}

C *initObiecteLista(Nod *cap, int anConstructie, int *dimensiune)
{
    (*dimensiune) = 0;
    Nod *p = cap;
    while (p != NULL)
    {
        if (p->info.anulConstruirii == anConstructie)
        {
            (*dimensiune)++;
        }
        p = p->next;
    }
    C *vectorCladiri = (C *)malloc(sizeof(C) * (*dimensiune));
    int contor = 0;
    p = cap;
    while (p != NULL)
    {
        if (p->info.anulConstruirii == anConstructie)
        {
            vectorCladiri[contor] = p->info;
            vectorCladiri[contor].numeCladire = (char *)malloc((strlen(p->info.numeCladire) + 1) * sizeof(char));
            strcpy(vectorCladiri[contor].numeCladire, p->info.numeCladire);
            contor++;
        }
        p = p->next;
    }
    return vectorCladiri;
}
// functie care modifica anulConstructiei initial, cu un nou An de constructie;
void modificaAnCladire(Nod *cap, int idC, int anNou)
{
    Nod *p = cap;
    while (p != NULL)
    {
        if (p->info.idUnic == idC)
        {
            p->info.anulConstruirii = anNou;
            printf("Cladirea cu Id [%d] a fost modificat la anul [%d].  \n", idC, anNou);
        }
        p = p->next;
    }
}

void modificaAnCladireHashTable(HT ht, int idCladire, int anConstruireVechi, int anNou)
{
    if (ht.vector == NULL)
    {
        return;
    }
    int pozitie = calculeazaHash(anConstruireVechi, ht.dimensiune);
    if (ht.vector[pozitie] != NULL)
    {
        modificaAnCladire(ht.vector[pozitie], idCladire, anNou);
    }
    else
    {
        printf("\n Cladirea nu s-a gazit in cluster. \n");
    }
}

void afisareHashTable(HT ht)
{
    printf("\n Structura de date HASH TABLE are elementele: \n");
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

void afisareCladiriListaAn(Nod *cap, int anCladire)
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
            printf("\n Nu s-a gasit. \n");
        }

        p = p->next;
    }
}

void afisareCladiriClusterDupaAn(HT ht, int an)
{
    int pozitie = calculeazaHash(an, ht.dimensiune);
    if (ht.vector[pozitie] != NULL)
    {
        afisareCladiriListaAn(ht.vector[pozitie], an);
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

    printf("\nAfisare cladire dupa an de constructie. \n");
    afisareCladiriClusterDupaAn(ht, 2012);
    printf("\n Stergere elemente din HashTable dupa //id + anConstructie// cladire: \n");
    stergereElementHashTable(ht, 21, 1989);
    stergereElementHashTable(ht, 20, 1808);
    stergereElementHashTable(ht, 10, 1478);
    afisareHashTable(ht);
    printf("\n Stergere element din Hash Table dupa // id //....\n");
    removeElementFromHTbyId(ht, 15);
    removeElementFromHTbyId(ht, 16);
    removeElementFromHTbyId(ht, 17);
    removeElementFromHTbyId(ht, 18);
    afisareHashTable(ht);

    int dimensiune = 0;
    int index = calculeazaHash(1907, ht.dimensiune);
    Nod *listaCluster = ht.vector[index];
    C *cladiri = initObiecteLista(listaCluster, 1907, &dimensiune);
    printf("\nVectori cu cladiri ce au celasi an de constructie: [%d] \n", cladiri->anulConstruirii);
    afisareVecor(cladiri, dimensiune);
    printf("\n");
    printf("\nModificare anul constructiei unei cladiri. \n");
    modificaAnCladireHashTable(ht, 14, 1939, 2015);
    modificaAnCladireHashTable(ht, 19, 1957, 2021);
    inserareHashTable(ht, c3);
    inserareHashTable(ht, c8);
    afisareHashTable(ht);
    dezalocareVector(&cladiri, &dimensiune);
    stergeHashTableMemory(&ht);
    // afisareHashTable(ht);

    return 0;
}

// Functia care sterge un element dupa (id+anConstructie) cladire din structura de date HashTable, are timp de complexitate constant, adica O(1);
// nu trebuie sa parcurgi tot vectorul pana la index-ul specificat dupa key si valoare;
// Functia care sterge un element dupa 'id' cladire din HashTable, are timp de complexitate O(n), pentru ca trebuie sa traverseze tot vectorul,
// pana gaseste (id-ul cladirei) in structura;