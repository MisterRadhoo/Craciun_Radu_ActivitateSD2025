#define _CRT_SECURE_NO_WARNINGS
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Task 9.{Heap....};

typedef struct
{
    char *nume;
    int varsta;
    char *problema;
    int prioritate; // numarul de prioritate mare reprezinta urgenta/stare critica max:10;

} Pacient;

Pacient initializare(const char *nume, int varsta, const char *simptom, int prioritate)
{
    Pacient p;
    p.nume = (char *)malloc((strlen(nume) + 1) * sizeof(char));
    strcpy(p.nume, nume);
    p.varsta = varsta;
    p.problema = (char *)malloc((strlen(simptom) + 1) * sizeof(char));
    strcpy(p.problema, simptom);
    p.prioritate = prioritate;
    return p;
}

// dezalocare memorie pentru *pointer la struct Pacient;
void dezalocare(Pacient *p)
{
    if (p->nume != NULL)
    {
        free(p->nume);
        p->nume = NULL;
        printf("\nPacient dezalocat...\n");
    }
    if (p->problema != NULL)
    {
        free(p->problema);
        p->problema = NULL;
    }
}

// stuctura Heap;
typedef struct Heap
{
    Pacient *vector; // vector alocat dinamic, unde se vor stoca elementele/nodes;
    int size;        // arata dimensiunea curenta a heap-ului, cate elemente sunt stocate;
    int capacity;    // capacitatea maxima care o are heap-ul;

} Heap;

// functie care creaza Heap;
Heap *createHeap(int capacity)
{
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->vector = (Pacient *)malloc(capacity * sizeof(Pacient));
    return heap;
}
// functie pentru schimbare doua elemente de tip int; / doua obiecte de tip 'struct';
void swap(Pacient *a, Pacient *b)
{
    Pacient temp = *a;
    *a = *b;
    *b = temp;
}
// functie heapify node la un index i ; satisface proprietatea heap a structuri de date, mentine ordinea;
void heapify(Heap *heap, int i)
{
    int largest = i;       // largest current node;
    int left = 2 * i + 1;  // left child node;
    int right = 2 * i + 2; // right child node;

    if (left < heap->size && heap->vector[left].prioritate > heap->vector[largest].prioritate)
    {
        largest = left;
    }
    if (right < heap->size && heap->vector[right].prioritate > heap->vector[largest].prioritate)
    {
        largest = right;
    }
    if (largest != i)
    {
        swap(&(heap->vector[i]), &(heap->vector[largest]));
        heapify(heap, largest);
    }
}
// functie care construieste MaxHeap din vectorul/array existent;
void buildHeap(Heap *heap)
{
    int n = heap->size;
    // incepe sa parcurga pana la ultimul node non-leaf(parintele nodului leaf),
    //  si apeleaza functia heapify pentru toate nivelurile in sens invers, de la coada la cap;
    for (int i = (n - 1) / 2; i >= 0; --i)
    {
        heapify(heap, i);
    }
}
// functie care creste valoarea la un index dat;
void increaseKey(Heap *heap, int index, int newValue)
{
    if (index >= heap->size || heap->vector[index].prioritate >= newValue)
    {
        printf("\nInvalid index or new value is not greater. \n");
        return;
    }
    heap->vector[index].prioritate = newValue;
    while (index != 0 && heap->vector[(index - 1) / 2].prioritate < heap->vector[index].prioritate)
    {
        swap(&(heap->vector[index]), &(heap->vector[(index - 1) / 2]));
        index = (index - 1) / 2;
    }
}
// functie care inseareaza un element in heap;
void insertUPU(Heap *heap, Pacient pacient)
{
    if (heap->size == heap->capacity)
    {
        printf("\nHeap overflow.\n");
        return;
    }
    heap->size++;
    int i = heap->size - 1;
    heap->vector[i].nume = (char *)malloc((strlen(pacient.nume) + 1) * sizeof(char));
    strcpy(heap->vector[i].nume, pacient.nume);
    heap->vector[i].varsta = pacient.varsta;
    heap->vector[i].problema = (char *)malloc((strlen(pacient.problema) + 1) * sizeof(char));
    strcpy(heap->vector[i].problema, pacient.problema);
    heap->vector[i].prioritate = pacient.prioritate;
    // fix , daca proprietatea heap este incalcata;
    while (i != 0 && heap->vector[(i - 1) / 2].prioritate < heap->vector[i].prioritate)
    {
        swap(&(heap->vector[i]), &(heap->vector[(i - 1) / 2]));
        i = (i - 1) / 2;
    }
}
// functie care iti stege un element din heap, la index dat;
void deleteKey(Heap *heap, int index)
{
    if (index >= heap->size)
    {
        printf("\nInvalid index. \n");
        return;
    }
    // Daca elementul care trebuie sters, este ultimul element, reducem dimensiuea heap-ului;
    if (index == heap->size - 1)
    {
        heap->size--;
        return;
    }
    // Mutam ultimul element la index-ul ultimul element care va fi sters;
    heap->vector[index] = heap->vector[heap->size - 1];
    heap->size--;
    // apelam functia heapify, pentru a satisface proprietatea heap si a mentine ordinea;
    heapify(heap, index);
}
// functie de extrage radacina root(elementul maxim);
Pacient extractMax(Heap *heap)
{
    if (heap->size <= 0)
    {
        Pacient p = {NULL, 0, NULL, 0};
        return p; // restrictioneaza la un tip de variabila int , -21722424....
    }
    if (heap->size == 1)
    {
        heap->size--;
        return heap->vector[0];
    }

    // stocare valoare maxima si dupa o stergem;
    Pacient root = heap->vector[0];
    heap->vector[0] = heap->vector[heap->size - 1];
    heap->size--;
    heapify(heap, 0);
    return root;
}
// Free memory heap;
void freeHeap(Heap **heap)
{
    if ((*heap))
    {
        if ((*heap)->vector != NULL)
        {
            for (int i = 0; i < (*heap)->size; i++)
            {
                free((*heap)->vector[i].nume);
                free((*heap)->vector[i].problema);
                printf("\nfree\n");
            }
        }
        free((*heap)->vector);
        (*heap)->vector = NULL;
        (*heap)->size = 0;
        (*heap)->capacity = 0;
        free(*heap);
        *heap = NULL;
        printf("\nHeap free.....\n");
    }
}
const char *getString(int prioritate)
{
    if (prioritate >= 4)
    {
        return "Stare Critica";
    }
    else if (prioritate >= 3)
    {
        return "Urgent";
    }
    else if (prioritate >= 2)
    {
        return "Non-urgent";
    }
    else if (prioritate >= 1)
    {
        return "Consult + Analize";
    }
}

// afiseaza elementele din heap;
void printHeap(Heap *heap)
{
    for (int i = 0; i < heap->size; ++i)
    {
        printf("Nume pacient: %s, \n", heap->vector[i].nume);
        printf("Varsta pacient: %d de ani,\n", heap->vector[i].varsta);
        printf("Problema pacient: %s,\n", heap->vector[i].problema);
        printf("Nivel prioritate [%d] - [%s], sa fie preluat de UPU. \n ", heap->vector[i].prioritate, getString(heap->vector[i].prioritate));
        printf("\n");
    }
}

int main()
{
    Pacient p = initializare("Tudor Arghezii", 89, "Durere simpla cot", 1);
    Pacient p1 = initializare("Mihaila Anca", 48, "Insarcinata/Dureri", 6);
    Pacient p2 = initializare("Ispase Andrei", 19, "Mana rupta", 2);
    Pacient p3 = initializare("Petre Gigel", 39, "Accident de masina", 8);
    Pacient p4 = initializare("Manea Laura", 66, "Raceala", 1);
    Pacient p5 = initializare("Gheorghe Cristian", 72, "Dureri torace", 3);
    Pacient p6 = initializare("Cornelia Bradet", 18, "Migrene", 2);
    Pacient p7 = initializare("Ion Chirpici", 59, "Dureri de spate", 2);
    Pacient p8 = initializare("Mihnea Andrei", 37, "Coma Alcolica", 6);
    Pacient p9 = initializare("Florin Andreea", 26, "Insarcinata/Rupt Apa", 6);
    Pacient p10 = initializare("Serban Mihai", 78, "Dureri in gat", 1);
    Pacient p11 = initializare("Remus Bogdan", 44, "Ruptura de ligamente", 3);
    Heap *heap = createHeap(12);

    insertUPU(heap, p);
    insertUPU(heap, p1);
    insertUPU(heap, p2);
    insertUPU(heap, p3);
    insertUPU(heap, p4);
    insertUPU(heap, p5);
    insertUPU(heap, p6);
    insertUPU(heap, p7);
    insertUPU(heap, p8);
    insertUPU(heap, p9);
    insertUPU(heap, p10);
    insertUPU(heap, p11);
    increaseKey(heap, 2, 5);
    printHeap(heap);

    printf("\nPersonalul de la UPU vor preluat prioritatile cu nr.4 - Stare-Critica.\n");
    printf("\nPacientul P3 a fost adus cu ambulanta\n");
    Pacient max = extractMax(heap);
    printf("\nPreluat de medici UPU: --->> %s, prioritate: %d\n", max.nume, max.prioritate);
    Pacient max1 = extractMax(heap);
    Pacient max2 = extractMax(heap);
    Pacient max3 = extractMax(heap);
    Pacient max4 = extractMax(heap);
    Pacient max5 = extractMax(heap);
    printf("\nPacientul dus in sala 1 (Nasteri): --->> %s, prioritate: %d", max1.nume, max1.prioritate);
    printf("\nPacientul dus in sala 2 , venit cu ambulanta: --->> %s, prioritate: %d \n", max2.nume, max2.prioritate);
    printf("\nPreluat de medici UPU: --->> %s, prioritate: %d \n", max3.nume, max3.prioritate);
    printf("\nDus la camera de garda, pentru a face injectie: --->> %s, prioritate %d \n", max4.nume, max4.prioritate);
    printf("\nPregatit pentru sala de operatii de catre medicii UPU: %s, prioritate [%d] \n", max5.nume, max5.prioritate);
    printf("\n");
    printHeap(heap);
    deleteKey(heap, 2);
    deleteKey(heap, 3);
    printf("\nLista cu pacieti UPU: \n");
    printHeap(heap);
    dezalocare(&p);
    freeHeap(&heap);

    return 0;
}