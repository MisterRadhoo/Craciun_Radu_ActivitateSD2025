#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PC
{
    int id;
    char *nume;
    int RAM;

} PC;

PC initializare(int id, const char *nume, int RAM)
{
    PC pc;
    pc.id = id;
    pc.nume = (char *)malloc((strlen(nume) + 1) * sizeof(char));
    strcpy(pc.nume, nume);
    pc.RAM = RAM;
    return pc;
}

void afisarePC(PC pc)
{
    printf("\nid: [ %d ], Nume PC: [ %s ], RAM PC: [ %d ] GB. \n", pc.id, pc.nume, pc.RAM);
}

// implementare struct MaxHeap;
typedef struct Heap
{
    PC *vector;     // vector alocat dinamic;
    int dimensiune; // dimensiunea totala a Heap-ului;
    int nrElem;     // numarul de elemente curente in Heap;

} Heap;

void filtreazaHeap(Heap heap, int index)
{
    int st = 2 * index + 1; // left child node;
    int dr = 2 * index + 2; // right child node;
    int pozMax = index;     // largest node;
    if (st < heap.nrElem && heap.vector[pozMax].id < heap.vector[st].id)
    {
        pozMax = st;
    }
    if (dr < heap.nrElem && heap.vector[pozMax].id < heap.vector[dr].id)
    {
        pozMax = dr;
    }
    if (pozMax != index)
    {
        PC aux = heap.vector[pozMax];
        heap.vector[pozMax] = heap.vector[index];
        heap.vector[index] = aux;
        if (pozMax < (heap.nrElem - 1) / 2)
        {
            filtreazaHeap(heap, pozMax);
        }
    }
}

void inserareHeap(Heap *heap, PC pc)
{
    if (heap->nrElem < heap->dimensiune)
    {
        heap->vector[heap->nrElem] = pc; // inserare la index liber;
        int i = heap->nrElem;

        // filtrare inversa ( bubble-up);
        while (i > 0 && heap->vector[i].id > heap->vector[(i - 1) / 2].id)
        {
            PC temp = heap->vector[i];
            heap->vector[i] = heap->vector[(i - 1) / 2];
            heap->vector[(i - 1) / 2] = temp;
            i = (i - 1) / 2;
        }
        heap->nrElem++;
    }
    else
    {
        printf("\nHeap-ul este plin......\n");
    }
}

PC extrageMax(Heap *heap)
{
    PC empty = {-1, NULL, 0};

    if (heap->nrElem <= 0)
    {
        return empty;
    }

    if (heap->nrElem == 1)
    {
        heap->nrElem--;
        return heap->vector[0];
    }

    PC temp = heap->vector[0];
    heap->vector[0] = heap->vector[heap->nrElem - 1];
    heap->vector[heap->nrElem - 1] = temp;
    heap->nrElem--;

    for (int i = (heap->nrElem - 2) / 2; i >= 0; i--)
    {
        filtreazaHeap(*heap, i);
    }

    return temp; // shallow copy;
}

Heap initializareHeap(int dimensiune)
{
    Heap heap;
    heap.vector = (PC *)malloc(sizeof(PC) * dimensiune);
    for (int i = 0; i < dimensiune; i++)
    {
        heap.vector[i].id = -1;
        heap.vector[i].nume = NULL;
        heap.vector[i].RAM = 0;
    }
    heap.dimensiune = dimensiune;
    heap.nrElem = 0;
    return heap;
}

void afisareHeap(Heap heap)
{
    for (int i = 0; i < heap.nrElem; i++)
    {
        afisarePC(heap.vector[i]);
        printf("\nElement din heap......\n");
    }
}

void printHiddenHeap(Heap heap)
{
    for (int i = heap.nrElem; i < heap.dimensiune; i++)
    {
        printf("\nmax Value extracted from heap......\n");
        afisarePC(heap.vector[i]);
    }
}

void dezalocareHeap(Heap *heap)
{
    for (int i = 0; i < heap->dimensiune; i++)
    {
        free(heap->vector[i].nume);
        printf("\nfree heap.....\n");
    }
    free(heap->vector);
    heap->vector = NULL;
    heap->nrElem = 0;
    heap->dimensiune = 0;
}

int main()
{
    PC pc = initializare(45, "Lenovo", 32);
    PC pc1 = initializare(67, "Dell", 16);
    PC pc2 = initializare(88, "Toshiba", 16);
    PC pc3 = initializare(5, "Acer", 32);
    PC pc4 = initializare(12, "AlienWare", 64);
    PC pc5 = initializare(17, "Fujitsu", 16);
    // afisarePC(pc);
    // afisarePC(pc1);
    Heap heap = initializareHeap(6);
    inserareHeap(&heap, pc);
    inserareHeap(&heap, pc1);
    inserareHeap(&heap, pc2);
    inserareHeap(&heap, pc3);
    inserareHeap(&heap, pc4);
    inserareHeap(&heap, pc5);
    afisareHeap(heap);
    printf("\n");
    extrageMax(&heap);
    extrageMax(&heap);
    extrageMax(&heap);
    extrageMax(&heap);
    extrageMax(&heap);
    extrageMax(&heap);
    extrageMax(&heap);

    printHiddenHeap(heap);
    dezalocareHeap(&heap);
    return 0;
}