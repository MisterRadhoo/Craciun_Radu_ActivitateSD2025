#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Hanorac
{
    int id;
    char *nume;
    unsigned char masura;
    float pret;

} H;

H init(int id, const char *nume, unsigned char masura, float pret)
{
    H hanorac;
    hanorac.id = id;
    hanorac.nume = (char *)malloc((strlen(nume) + 1) * sizeof(char));
    strcpy(hanorac.nume, nume);
    hanorac.masura = masura;
    hanorac.pret = pret;
    return hanorac;
}

void afisareHanorac(H h)
{
    printf("id Hanorac: [ %d ],\n", h.id);
    printf("Nume Hanorac: -->> [ %s ], \n", h.nume);
    printf("Masura hanorac: -->> [ %c ], \n", h.masura);
    printf("Pret hanorac: -->> [ %.2f] lei. \n", h.pret);
}
void dezalocareHanorac(H *h)
{
    if (h->nume != NULL)
    {
        free(h->nume);
        h->nume = NULL;
        printf("\n free hoodie....\n");
    }
}

typedef struct Heap
{
    H *vector;
    int nrElemente;
    int dimensiune;

} Heap;

Heap initializareHeap(int dimensiune)
{
    Heap heap;
    heap.vector = (H *)malloc(sizeof(H) * dimensiune);
    heap.nrElemente = 0;
    heap.dimensiune = dimensiune;
    return heap;
}

void filtreazaHeap(Heap heap, int pozNod)
{ // filtreaza heap-ul pentru nodul a carei pozitie o primeste ca parametru;
    int pozLC = 2 * pozNod + 1;
    int pozRC = 2 * pozNod + 2;
    int pozMax = pozNod;
    if (pozLC < heap.nrElemente && heap.vector[pozMax].id < heap.vector[pozLC].id)
    {
        pozMax = pozLC;
    }
    if (pozRC < heap.nrElemente && heap.vector[pozMax].id < heap.vector[pozRC].id)
    {
        pozMax = pozRC;
    }
    if (pozMax != pozNod)
    {
        H aux = heap.vector[pozMax];
        heap.vector[pozMax] = heap.vector[pozNod];
        heap.vector[pozNod] = aux;

        if (pozMax < (heap.nrElemente - 1) / 2)
        {
            filtreazaHeap(heap, pozMax);
        }
    }
}

void inserareHeap(Heap *heap, H hanorac)
{
    if (heap->nrElemente < heap->dimensiune)
    {
        heap->vector[heap->nrElemente] = hanorac; // inserare la pozitia libera;
        int i = heap->nrElemente;

        // filtrare inversa ( bubble up);
        while (i > 0 && heap->vector[i].id > heap->vector[(i - 1) / 2].id)
        {
            H aux = heap->vector[i];
            heap->vector[i] = heap->vector[(i - 1) / 2];
            heap->vector[(i - 1) / 2] = aux;
            i = (i - 1) / 2;
        }
        heap->nrElemente++;
    }
    else
    {
        printf("\nHeap-ul este plin!\n");
    }
}

void afisareHeap(Heap heap)
{
    for (int i = 0; i < heap.nrElemente; i++)
    {
        afisareHanorac(heap.vector[i]);
        printf("\n");
    }
}

void afisareHeapAscuns(Heap heap)
{
    for (int i = heap.nrElemente; i < heap.dimensiune; i++)
    {
        afisareHanorac(heap.vector[i]);
        printf("\n");
    }
}

void dezalocareHeap(Heap *heap)
{
    for (int i = 0; i < heap->dimensiune; i++)
    {
        free(heap->vector[i].nume);
    }
    free(heap->vector);
    heap->vector = NULL;
    heap->nrElemente = 0;
    heap->dimensiune = 0;
}

H extrageMax(Heap *heap)
{
    H temp = heap->vector[0];
    heap->vector[0] = heap->vector[heap->nrElemente - 1];
    heap->vector[heap->nrElemente - 1] = temp;
    heap->nrElemente--;

    // face loop de la ultimul node non-leaf (care are copii);
    for (int i = (heap->nrElemente - 2) / 2; i >= 0; i--)
    {
        filtreazaHeap(*heap, i);
    }

    temp.nume = (char *)malloc((strlen(heap->vector[heap->nrElemente].nume) + 1) * sizeof(char));
    strcpy(temp.nume, heap->vector[heap->nrElemente].nume);
    return temp;
}

int main()
{

    H hanorac = init(1111, "Polo Ralph Lauren bear", 'M', 979.00);
    H hanorac1 = init(2222, "MK Hanorac", 'S', 779.00);
    H hanorac2 = init(3333, "CK Hanorac Tree print", 'M', 579.00);
    H hanorac3 = init(4444, "Nike Club Hoodie", 'S', 329.00);
    H hanorac4 = init(4444, "Nike Club Hoodie", 'M', 329.00);
    H hanorac5 = init(5555, "Lacoste", 'L', 499.99);
    H hanorac6 = init(6666, "Pull & Bear oversized", 'S', 139.49);
    H hanorac7 = init(7777, "Nike Club Hoodie washed coral", 'L', 349.15);
    H hanorac8 = init(8888, "Urban Hoodie", 'L', 229.89);

    Heap heap = initializareHeap(12);
    inserareHeap(&heap, hanorac);
    inserareHeap(&heap, hanorac1);
    inserareHeap(&heap, hanorac2);
    inserareHeap(&heap, hanorac3);
    inserareHeap(&heap, hanorac4);
    inserareHeap(&heap, hanorac5);
    inserareHeap(&heap, hanorac6);
    inserareHeap(&heap, hanorac7);
    inserareHeap(&heap, hanorac8);

    H max = extrageMax(&heap);
    printf("\nExtragere Max id: \n");
    afisareHanorac(max);
    free(max.nume);

    extrageMax(&heap);

    printf("\nElemente/Nod-uri ramase in Heap: -->>\n");
    afisareHeap(heap);
    printf("\nAfisare elemente extrase din vector(valori ascunse),dar nefolosite ( garbage values): \n");
    afisareHeapAscuns(heap);

    dezalocareHeap(&heap);

    return 0;
}