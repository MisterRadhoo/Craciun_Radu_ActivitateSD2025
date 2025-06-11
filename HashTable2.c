#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nod Nod;
typedef struct Hashtable HT;
typedef struct Vagon
{
    int id;
    char *tip;

} V;

V initializare(int id, const char *tip)
{
    V vagon;
    vagon.id = id;
    vagon.tip = (char *)malloc((strlen(tip) + 1) * sizeof(char));
    strcpy(vagon.tip, tip);
    return vagon;
}

void afisareVagon(V vagon)
{
    printf("\nId: [ %d ]; Tip Vagon: [ %s ]. \n", vagon.id, vagon.tip);
}

void dezalocareVagon(V *vagon)
{
    if (vagon->tip != NULL)
    {
        free(vagon->tip);
        vagon->tip = NULL;
        printf("\n.....vagon free....\n");
    }
}

// Lista simpla intlantuita;
struct Nod
{
    V info;
    Nod *next;
};

// structura HashTable;
struct Hashtable
{
    Nod **vagoane;
    int capacitate;
};

HT init(int capacitate)
{
    HT ht;
    ht.capacitate = capacitate;
    ht.vagoane = (Nod **)malloc(sizeof(Nod *) * capacitate);
    for (int i = 0; i < capacitate; i++)
    {
        ht.vagoane[i] = NULL;
    }
    return ht;
}

// functia hash: 1;
int hash(int id, int capacitate)
{
    return (id % capacitate);
}

// functia hash: 2
int hash2(const char *tip, int capacitate)
{
    int suma = 0;
    for (int i = 0; i < strlen(tip); i++)
    {
        suma += tip[i];
    }
    return suma % capacitate;
}

void inserareLaInceputLista(Nod **cap, V vagon)
{
    Nod *nou = (Nod *)malloc(sizeof(Nod));
    nou->info = vagon;
    nou->next = (*cap);
    (*cap) = nou;
}

void inserareLaSfaritLista(Nod **cap, V vagon)
{
    Nod *nouNod = (Nod *)malloc(sizeof(Nod));
    nouNod->info = vagon;
    nouNod->next = NULL;
    if ((*cap))
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

void inserareHT(HT ht, V vagon)
{
    int index = hash2(vagon.tip, ht.capacitate);
    if (index >= 0 && index < ht.capacitate)
    {
        if (ht.vagoane[index] == NULL)
        {
            ht.vagoane[index] = (Nod *)malloc(sizeof(Nod));
            ht.vagoane[index]->info = vagon; // shallow copy;
            ht.vagoane[index]->next = NULL;
        }
        else
        {
            inserareLaSfaritLista(&(ht.vagoane[index]), vagon);
        }
    }
}

void afisareLista(Nod *cap)
{
    Nod *p = cap;
    while (p != NULL)
    {
        afisareVagon(p->info);
        p = p->next;
        printf("\n");
    }
}

void afisareHT(HT ht)
{
    for (int i = 0; i < ht.capacitate; i++)
    {
        if (ht.vagoane[i] != NULL)
        {
            printf("\nVagoane de pe pozitia [ %d ] sunt: \n", i);
            afisareLista(ht.vagoane[i]);
        }
        else
        {
            printf("\nPe pozitia [ %d ] nu avem vagoane. \n", i);
        }
    }
}

void stergeLista(Nod **cap)
{
    Nod *p = (*cap);
    while (p != NULL)
    {
        Nod *temp = p;
        p = p->next;
        if (temp->info.tip != NULL)
        {
            free(temp->info.tip);
        }
        free(temp);
    }
    (*cap) = NULL;
}

void dezalocareHT(HT *ht)
{
    for (int i = 0; i < ht->capacitate; i++)
    {
        stergeLista(&(ht->vagoane[i]));
        printf("\nHT.....free..\n");
    }
    free(ht->vagoane);
    ht->vagoane = NULL;
    ht->capacitate = 0;
}

V getVagonDinLista(Nod *cap, const char *tip)
{
    V vagon;
    vagon.id = -1;
    while (cap && strcmp(cap->info.tip, tip) != 0)
    {
        cap = cap->next;
    }
    if (cap)
    {
        vagon = cap->info;
        vagon.tip = (char *)malloc((strlen(cap->info.tip) + 1) * sizeof(char));
        strcpy(vagon.tip, cap->info.tip);
    }
    return vagon;
}

V getVagonDinHT(HT ht, const char *tipCautat)
{
    V vagon;
    vagon.id = -1;
    int pozitie = hash2(tipCautat, ht.capacitate);
    if (pozitie >= 0 && pozitie < ht.capacitate)
    {
        return getVagonDinLista(ht.vagoane[pozitie], tipCautat);
    }
    return vagon;
}

int main()
{
    V v = initializare(1, "tramvai");
    V v1 = initializare(2, "Locomotiva");
    V v2 = initializare(3, "Embargou");
    V v3 = initializare(4, "Calatori");
    V v4 = initializare(5, "Armament");
    V v5 = initializare(6, "Express");

    HT ht = init(9);
    inserareHT(ht, v);
    inserareHT(ht, v1);
    inserareHT(ht, v2);
    inserareHT(ht, v3);
    inserareHT(ht, v4);
    inserareHT(ht, v5);
    afisareHT(ht);

    V vagon = getVagonDinHT(ht, "Express");
    if (vagon.id != -1)
    {
        printf("\nTip vagon cautat: \n");
        afisareVagon(vagon);
        if (vagon.tip != NULL)
        {
            free(vagon.tip);
        }
    }
    else
    {
        printf("\nTipul vagonului nu a fost gasit!");
    }

    dezalocareHT(&ht);
    return 0;
}