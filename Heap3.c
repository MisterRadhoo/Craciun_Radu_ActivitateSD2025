#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Hanorac
{
    int id;
    char *brand;
    float pret;

} H;

H init(int id, const char *brand, float pret)
{
    H hanorac;
    hanorac.id = id;
    hanorac.brand = (char *)malloc(sizeof(char) * (strlen(brand) + 1));
    strcpy(hanorac.brand, brand);
    hanorac.pret = pret;
    return hanorac;
}

void afisareHanorac(H hanorac)
{
    printf("\nid: [ %d ]; Brand: [ %s ]; Pret: [ %.2f ] lei. \n", hanorac.id, hanorac.brand, hanorac.pret);
}

void dezalocareHanorac(H *h)
{
    if (h->brand != NULL)
    {
        free(h->brand);
        h->brand = NULL;
        printf("\nFree Hoodie...\n");
    }
}

// structura heap;
typedef struct Heap
{
    H *vector;
    int dimensiune;
    int nrElemente;

} Heap;

Heap initializare(int dimensiune)
{
    Heap heap;
    heap.vector = (H *)malloc(sizeof(H) * dimensiune);
    for (int i = 0; i < dimensiune; i++)
    {
        heap.vector[i].id = -1;
        heap.vector[i].brand = NULL;
        heap.vector[i].pret = 0.00f;
    }
    heap.nrElemente = 0;
    return heap;
}

void filteazaHeap(Heap heap, int pozNod)
{
    int st = 2 * pozNod + 1;
    int dr = 2 * pozNod + 2;
    int pozMax = pozNod;
    if (st < heap.nrElemente && heap.vector[pozMax].id < heap.vector[st].id)
    {
        pozMax = st;
    }
    if (dr < heap.nrElemente && heap.vector[pozMax].id < heap.vector[dr].id)
    {
        pozMax = dr;
    }
    if (pozMax != pozNod)
    {
        H aux = heap.vector[pozMax];
        heap.vector[pozMax] = heap.vector[pozNod];
        heap.vector[pozNod] = aux;
        if (pozMax < (heap.nrElemente - 1) / 2)
        {
            filteazaHeap(heap, pozMax);
        }
    }
}

void inserareHeap(Heap *heap, H hanorac)
{
    if (heap->nrElemente < heap->dimensiune)
    {
        heap->vector[heap->nrElemente] = hanorac; // inserare la pozitie libera;
        int i = heap->nrElemente;

        // filtrare inversa (bubble up);
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
        printf("\nHeap Ascuns.\n");
    }
}

void dezalocareHeap(Heap *heap)
{
    for (int i = 0; i < heap->dimensiune; i++)
    {
        free(heap->vector[i].brand);
        printf("\nFree Heap....\n");
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

    for (int i = (heap->nrElemente - 2) / 2; i >= 0; i--)
    {
        filteazaHeap(*heap, i);
    }
    temp.brand = (char *)malloc((strlen(heap->vector[heap->nrElemente].brand) + 1) * sizeof(char));
    strcpy(temp.brand, heap->vector[heap->nrElemente].brand);
    return temp;
}

int main()
{

    H hanorac1 = init(1, "Nike Sail", 329.99);
    H hanorac2 = init(2, "Nike Green", 329.99);
    H hanorac3 = init(3, "Nike Coral", 329.99);
    H hanorac4 = init(4, "Nike Burgundy", 329.99);
    H hanorac5 = init(5, "Nike Apricot", 329.99);
    H hanorac6 = init(6, "Nike Malachite", 329.99);
    H hanorac7 = init(7, "Nike Red", 329.99);

    // afisareHanorac(hanorac1);

    Heap heap = initializare(10);
    inserareHeap(&heap, hanorac1);
    inserareHeap(&heap, hanorac2);
    inserareHeap(&heap, hanorac3);
    inserareHeap(&heap, hanorac4);
    inserareHeap(&heap, hanorac5);
    inserareHeap(&heap, hanorac6);
    inserareHeap(&heap, hanorac7);

    afisareHeap(heap);
    H max = extrageMax(&heap);
    printf("\nExtragere Max id: \n");
    afisareHanorac(max);
    free(max.brand);

    extrageMax(&heap);
    printf("\nAfisare elemente extrase din vector(valori ascunse),dar nefolosite ( garbage values): \n");
    afisareHeapAscuns(heap);

    dezalocareHeap(&heap);
    return 0;
}