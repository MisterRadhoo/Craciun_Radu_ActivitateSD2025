#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Task.6 {Liste dublu inlantuite};
typedef struct Calculator
{
    int id;
    char *brand;
    // char *OS;         // Operating System;
    char CPU[50];
    int RAM;
    int capacitate;
    float pret;

} PC;

PC initializare(int id, char *brand, char *CPU, int RAM, int cap, float pret)
{
    PC calculator;
    calculator.id = id;
    calculator.brand = (char *)malloc((strlen(brand) + 1) * sizeof(char));
    strcpy(calculator.brand, brand);
    strncpy(calculator.CPU, CPU, 50);
    calculator.CPU[49] = '\0';
    calculator.RAM = RAM;
    calculator.capacitate = cap;
    calculator.pret = pret;
    return calculator;
}
void display(PC pc)
{
    printf("Calculator ID: %d \n", pc.id);
    printf("Calculator Brand: %s \n", pc.brand);
    printf("Calculator CPU: %s \n", pc.CPU);
    printf("Calculator RAM: %d Gbytes \n", pc.RAM);
    printf("Calculator, capacitate de stocare de: %d GB \n", pc.capacitate);
    printf("Calculator, pret: %.2f  $ \n", pc.pret);
}

// Nod Lista dublu inlantuita;
typedef struct Nod
{
    PC info;
    struct Nod *next;
    struct Nod *prev;

} Nod;
// Creare structura Lista dublu inlantuita;
typedef struct LDI
{
    Nod *prim;
    Nod *ultim;
    int nrNoduri;

} LDI;

void parcurgereLista(LDI *lista)
{
    printf("\nLista dublu inlantuita are elementele: -->> \n");
    Nod *p = lista->prim;
    int i = 0;
    while (p)
    {
        printf("\nNumar Nod: %d\n", i);
        i++;
        display(p->info);
        p = p->next;
    }
}

void parcurgereInversa(LDI *lista)
{
    printf("\nParcurgere inversa a Listei dublu inlantuite: -->>\n");
    Nod *p = lista->ultim;
    int k = 0;
    while (p)
    {
        printf("\nNumar Nod: %d\n", k);
        k++;
        display(p->info);
        p = p->prev;
        printf("\n");
    }
}

void inserareLaSfarsitLDI(LDI *lista, PC pc)
{
    Nod *nou = (Nod *)malloc(sizeof(Nod));
    nou->info = pc;
    nou->info.brand = (char *)malloc(sizeof(char) * (strlen(pc.brand) + 1));
    strcpy(nou->info.brand, pc.brand);
    nou->next = NULL;
    nou->prev = lista->ultim;
    if (lista->ultim != NULL)
    {
        lista->ultim->next = nou;
    }
    else
    {
        lista->prim = nou;
    }
    lista->ultim = nou;
    lista->nrNoduri++;
}

void inserareLaInceputLDI(LDI *lista, PC pc)
{
    Nod *nou = (Nod *)malloc(sizeof(Nod));
    nou->info = pc;
    nou->info.brand = (char *)malloc((strlen(pc.brand) + 1) * sizeof(char));
    strcpy(nou->info.brand, pc.brand);
    nou->next = lista->prim;
    nou->prev = NULL;
    if (lista->prim != NULL)
    {
        lista->prim->prev = nou;
    }
    else
    {
        lista->ultim = nou;
    }
    lista->prim = nou;
    lista->nrNoduri++;
}
// functie care sterge node din pozitia specificata;
void stergereNodPozitieLDI(LDI *lista, int poz)
{ // daca lista este goala;
    if (lista->prim == NULL)
    {
        return;
    }
    Nod *curent = lista->prim;
    // parcurgere lista pana la pozitia node-ului;
    for (int i = 1; curent != NULL && i < poz; i++)
    {
        curent = curent->next;
    }
    // daca pozitia nu este gasita;
    if (curent == NULL)
    {
        return;
    }
    // legatura cu node-ul anterior a fost actualizata;
    if (curent->prev != NULL)
    {
        curent->prev->next = curent->next;
    }
    // legatura cu node-ul urmator a fost actualizata;
    if (curent->next != NULL)
    {
        curent->next->prev = curent->prev;
    }
    // 'Cap' de lista, a fost actualizat;
    if (lista->prim == curent)
    {
        lista->prim = curent->next;
    }
    if (curent->info.brand != NULL)
    {
        free(curent->info.brand);
    }
    free(curent);
    lista->nrNoduri--;
}
// stergere nod dupa id;
void stergereNodLDIdupaId(LDI *lista, int id)
{
    if (lista->prim == NULL)
    {
        return;
    }
    Nod *p = lista->prim;
    while (p != NULL && p->info.id != id)
    {
        p = p->next;
    }
    if (p == NULL)
    {
        return;
    }
    // avem ce sa stergem ?
    if (p->prev == NULL)
    {
        lista->prim = p->next;
        if (lista->prim != NULL)
        {
            lista->prim->prev = NULL;
        }
    }
    else
    {
        p->prev->next = p->next;
    }
    if (p->next != NULL)
    {
        p->next->prev = p->prev;
    }
    else
    {
        lista->ultim = p->prev;
    }
    if (p->info.brand != NULL)
    {
        free(p->info.brand);
    }
    free(p);
    lista->nrNoduri--;
}

void dezalocareMemorieLDI(LDI *lista)
{
    Nod *p = lista->prim;
    while (p != NULL)
    {
        Nod *aux = p;
        p = p->next;
        if (aux->info.brand != NULL)
        {
            free(aux->info.brand);
            printf("\nFree Memory LDI: \n");
        }
        free(aux);
    }
    lista->prim = NULL;
    lista->ultim = NULL;
    lista->nrNoduri = 0;
}
float calculeazaPretMediu(LDI *lista)
{
    if (lista->nrNoduri > 0)
    {
        float suma = 0;
        Nod *p = lista->prim;
        while (p != NULL)
        {
            suma += p->info.pret;
            p = p->next;
        }
        return suma / lista->nrNoduri;
    }
    return 0;
}
char *getBrandCelMaiScumpPC(LDI *lista)
{
    if (lista->prim != NULL)
    {
        Nod *max = lista->prim;
        Nod *p = lista->prim->next;

        while (p != NULL)
        {
            if (p->info.pret > max->info.pret)
            {
                max = p;
            }
            p = p->next;
        }

        char *brand1 = (char *)malloc((strlen(max->info.brand) + 1) * sizeof(char));
        strcpy(brand1, max->info.brand);
        return brand1;
    }
    else
    {
        return NULL;
    }
}

// Functie care insereaza un Nod si sorteaza dupa pret;(crescator);
void insertionSort(LDI *lista)
{

    if (lista->prim == NULL || lista->prim->next == NULL)
    {
        return;
    }
    Nod *curent = lista->prim;
    Nod *sortat = NULL;
    // resetare ultim pointer;
    lista->ultim = NULL;
    while (curent != NULL)
    {
        Nod *next = curent->next;
        // refacere legaturi; setam pointeri node-ului curent, 'prev' si 'next' cu NULL;
        curent->prev = curent->next = NULL;
        // Inserare sortata in noua lista;
        if (sortat == NULL || curent->info.pret < sortat->info.pret)
        {
            curent->next = sortat;
            if (sortat != NULL)
            {
                sortat->prev = curent;
            }
            sortat = curent;
        }
        else
        {
            Nod *temp = sortat;
            while (temp->next != NULL && temp->next->info.pret < curent->info.pret)
            {
                temp = temp->next;
            }
            curent->next = temp->next;
            if (temp->next != NULL)
            {
                temp->next->prev = curent;
            }
            temp->next = curent;
            curent->prev = temp;
        }
        curent = next;
    }
    // Actualizare lista originala;
    lista->prim = sortat;
    // Cautare ultim nod;
    Nod *p = lista->prim;
    while (p->next != NULL)
    {
        p = p->next;
    }
    lista->ultim = p;
}

// Lista simpla inlantuita; structura;
typedef struct LinkedList
{
    PC data;
    struct LinkedList *next;

} LL;

void inserareInceput(LL **cap, PC c)
{
    LL *nou = (LL *)malloc(sizeof(LL));
    nou->data = c;
    nou->data.brand = (char *)malloc(sizeof(char) * (strlen(c.brand) + 1));
    strcpy(nou->data.brand, c.brand);
    nou->next = (*cap);
    (*cap) = nou;
}
// Functie de imi returneaza obiecte PC cu pret sub 1000 %, sunt stocate in Liste simplu inlantuite;
LL *obiectePCpretMic(LDI *lista, float pretSpecificat)
{
    LL *cap = NULL;
    Nod *p = lista->prim;
    while (p != NULL)
    {
        if (p->info.pret < pretSpecificat)
        {
            PC pc;
            pc.id = p->info.id;
            pc.brand = (char *)malloc(sizeof(char) * (strlen(p->info.brand) + 1));
            strcpy(pc.brand, p->info.brand);
            strncpy(pc.CPU, p->info.CPU, 50);
            pc.CPU[49] = '\0';
            pc.RAM = p->info.RAM;
            pc.capacitate = p->info.capacitate;
            pc.pret = p->info.pret;
            inserareInceput(&cap, pc);
        }
        p = p->next;
    }
    return cap;
}
void printLL(LL *cap)
{
    printf("\nLista simpla inlantuita are elementele: \n");
    LL *p = cap;
    while (p != NULL)
    {
        printf("\n Id: %d, Brand PC: %s, Pret: %.2f :", p->data.id, p->data.brand, p->data.pret);
        p = p->next;
        printf("\n");
    }
}
void dezalocareLL(LL **cap)
{
    while (*(cap) != NULL)
    {
        LL *p = *cap;
        (*cap) = (*cap)->next;
        if (p->data.brand != NULL)
        {
            free(p->data.brand);
            printf("\nFree LL memory:\n");
        }
        free(p);
        p->data.brand = NULL;
    }
}

int main()
{
    // Liste dublu inlantuite;
    PC pc1 = initializare(100, "Asus NoteBook 3T", "Intel I9", 16, 256, 520.34);
    PC pc2 = initializare(101, "Acer Nitro 5", "AMD Duron x8", 32, 512, 640.00);
    PC pc3 = initializare(102, "Dell Alienware", "Intel i9 Turbo", 64, 1024, 1282.89);
    PC pc4 = initializare(103, "Lenovo Legion", "AMD e15", 32, 512, 880.32);
    PC pc5 = initializare(104, "Dell", "Intel i3", 16, 256, 456.44);
    PC pc6 = initializare(204, "MacBook Pro 4P", "Apple M3", 32, 512, 1029.99);
    PC pc7 = initializare(205, "Lenovo Power Pro", "Inter i7 Turbo", 64, 1024, 1424.55);
    PC pc8 = initializare(206, "Toshiba Quad", "AMD Ryzen", 32, 1024, 724.85);
    PC pc9 = initializare(301, "MSI Cyborg", "Intel Core i7", 16, 512, 830.99);
    PC pc10 = initializare(303, "Alienware M18 R2", "Intel i9", 64, 2048, 2544.39);

    // Initializare lista;
    LDI lista;
    lista.prim = NULL;
    lista.ultim = NULL;
    lista.nrNoduri = 0;

    inserareLaInceputLDI(&lista, pc1);
    inserareLaInceputLDI(&lista, pc2);
    inserareLaInceputLDI(&lista, pc3);
    inserareLaSfarsitLDI(&lista, pc4);
    inserareLaSfarsitLDI(&lista, pc5);
    inserareLaInceputLDI(&lista, pc6);
    inserareLaInceputLDI(&lista, pc7);
    inserareLaSfarsitLDI(&lista, pc8);
    inserareLaSfarsitLDI(&lista, pc9);
    inserareLaInceputLDI(&lista, pc10);
    parcurgereLista(&lista);
    stergereNodLDIdupaId(&lista, 206);
    printf("\nPretul mediu al PC-urilor %.2f $:\n", calculeazaPretMediu(&lista));
    parcurgereInversa(&lista);

    char *brandPC = getBrandCelMaiScumpPC(&lista);
    printf("\nBrand PC, cel mai scump:-->> %s \n", brandPC);
    if (brandPC != NULL)
    {
        free(brandPC);
    }
    parcurgereLista(&lista);
    printf("\nStergere Node dupa pozitia specificata: -->> \n");
    stergereNodPozitieLDI(&lista, 3); // s-a sters obiect 'pc6' la struct;
    parcurgereLista(&lista);

    insertionSort(&lista);
    printf("\n----------------------Sortare-crescatoare-Liste-Dublu-Inlantuite-(InsertionSort)---------\n");
    parcurgereLista(&lista);
    printf("\nParcurgere LDI sortata crescator, in mod invers: \n");
    parcurgereInversa(&lista);

    printf("\nAfisare PC-uri ce au pret sub 1000 $, stocate in lista simplu inlantuita: \n");
    LL *capPC = obiectePCpretMic(&lista, 1000.00);
    printLL(capPC);

    dezalocareMemorieLDI(&lista);
    dezalocareLL((&capPC));
    return 0;
}

/*** Diferenta intre Vectori si Liste Simplu Inlantuite ***/ //;

/***   In memorie, elementele vectorilor sunt stocate in locatii adiacente;  ***/
/***   Liste simplu inlantuite, elementele nu sunt stocate in locatii adiacente;  ***/
/***   Vectorii au dimensiune fixa, Liste simplu inlantuite au memorie dinamica  ***/
/***   Vectorii stocheaza doar elemente fara referinta, pentru acest lucru, trebuie un pointer suplimentar;  ***/
/***   Listele simplu inlantuite, stocheaza datele, cat si adresa urmatoare a urmatorului node, prin pointer;  ***/
/***   Accesarea elementelor in vector, are un timp de constanta O(1) ;***/
/***   Accesarea elementelor in Liste, se mai face mai intai prin parcurgerea listei(toate nodurile, pana ajugem la nodul dorit), timpul fiind O(n)***/
/***   Inserarea si stergerea elementelor din vector e mai inceata, timp (O(n) la cap de vector; ***/
/***   La liste, inserarea si stergerea elementelor este mai rapida, la cap de lista este complexitate de timp de (O(1)); ***/