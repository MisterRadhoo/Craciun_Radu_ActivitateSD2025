#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// testing.....;
// Task1 {Structura si functii};// Task 2 {Vectori};// Task 3;{Fisiere} // Task 5{Liste simple inlantuite....};
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

// introducere de la tastura un obiect Struct Calculator//alias PC;
PC inputs()
{
    PC c;
    c.brand = (char *)malloc(150 * sizeof(char));
    printf("Introduceti ID calculator: -->> \n");
    scanf("%d", &c.id);
    printf("Introduceti brand PC: \n");
    scanf("%s", c.brand);
    printf("Introduceti nume de CPU al PC-ului: \n");
    getchar();
    gets(c.CPU);
    printf("Introduceti numarul de RAM: \n");
    scanf("%d", &c.RAM);
    printf("Introduceti capacitatea PC-ului: \n");
    scanf("%d", &c.capacitate);
    printf("Introduceti pretul PC-ul: \n");
    scanf("%f", &c.pret);

    printf("Calculator ID: %d \n", c.id);
    printf("Calculator Brand: %s \n", c.brand);
    printf("Calculator CPU: %s \n", c.CPU);
    printf("Calculator RAM: %d Gbytes \n", c.RAM);
    printf("Calculator, capacitate de stocare de: %d GB \n", c.capacitate);
    printf("Calculator, pret: %.2f  $ \n", c.pret);

    return c;
}
// calculeaza reducerea de pret al unui obiect;
float reducerePret(PC c, float reducere)
{
    float discount = c.pret - (c.pret * reducere / 100.0f);
    return discount;
}
// setare pret;
void setPret(PC *pc, float pretNou)
{
    pc->pret = pretNou;
}
// modificare atribut/menbru de data (char *brand);
void setBrand(PC *pc, const char *brandNou)
{
    if (pc->brand != NULL)
    {
        free(pc->brand);
    }
    pc->brand = (char *)malloc((strlen(brandNou) + 1) * sizeof(char));
    strcpy(pc->brand, brandNou);
}
void dezalocare(PC **pc, int *nrElemente)
{
    for (int i = 0; i < *nrElemente; i++)
    {
        free((*pc)[i].brand);
        printf("Free Memory: %d \n", (*pc)[i].id);
    }
    free(*pc);
    *nrElemente = 0;
    *pc = NULL;
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
void displayVector(PC *c, int nrElemente)
{
    for (int i = 0; i < nrElemente; i++)
    {
        display(c[i]);
        printf("\n");
    }
}
// functie care returneaza un vector cu obiecte care au capacitatea mai mare de 256;
PC *vectorCapacitate(PC *vectorPC, int nrElemente, int cap, int *dimensiune)
{ // initializeaza numarul de obiecte din vector;
    *dimensiune = 0;
    for (int i = 0; i < nrElemente; i++)
    {
        if (vectorPC[i].capacitate > cap)
        {
            (*dimensiune)++;
        }
    }

    PC *c = (PC *)malloc(sizeof(PC) * (*dimensiune));
    int index = 0; // index pentru pointer *c la struct PC;
    for (int i = 0; i < nrElemente; i++)
    {
        if (vectorPC[i].capacitate > cap)
        {
            c[index] = vectorPC[i];
            c[index].brand = (char *)malloc((strlen(vectorPC[i].brand) + 1) * sizeof(char));
            strcpy(c[index].brand, vectorPC[i].brand);
            index++;
        }
    }
    return c;
}
PC *vectorMinRAM(PC *vectorRAM, int nrElem, int RAM, int *dim)
{ // Initializare;
    *dim = 0;
    for (int i = 0; i < nrElem; i++)
    {
        if (vectorRAM[i].RAM <= RAM)
        {
            (*dim)++;
        }
    }
    // returnare obiecte(PC) <= 16 GBytes;
    PC *rezultat = (PC *)malloc(sizeof(PC) * (*dim));
    int index = 0;
    for (int i = 0; i < nrElem; i++)
    {
        if (vectorRAM[i].RAM <= RAM)
        {
            rezultat[index] = vectorRAM[i];
            rezultat[index].brand = (char *)malloc((strlen(vectorRAM[i].brand) + 1) * sizeof(char));
            strcpy(rezultat[index].brand, vectorRAM[i].brand);
            index++;
        }
    }
    return rezultat;
}

PC *concatVectori(PC *v1, PC *v2, int dim1, int dim2)
{
    int dimFinal = dim1 + dim2;
    int index1 = 0;
    PC *vectorFinal = (PC *)malloc(sizeof(PC) * (dimFinal));
    for (int i = 0; i < dim1; i++)
    {
        vectorFinal[index1] = v1[i];
        vectorFinal[index1].brand = (char *)malloc(sizeof(char) * (strlen(v1[i].brand) + 1));
        strcpy(vectorFinal[index1].brand, v1[i].brand);
        index1++;
    }
    for (int i = 0; i < dim2; i++)
    {
        vectorFinal[index1] = v2[i];
        vectorFinal[index1].brand = (char *)malloc(sizeof(char) * (strlen(v2[i].brand) + 1));
        strcpy(vectorFinal[index1].brand, v2[i].brand);
        index1++;
    }
    return vectorFinal;
}

void createFileTxt(PC *vectorPC, int dim, const char *calculatoare)
{
    FILE *f;
    f = fopen(calculatoare, "w");
    if (f == NULL)
    {
        printf("Fisierul nu s-a putut deschide !!! \n");
    }
    for (int i = 0; i < dim; i++)
    {
        fprintf(f, "Calculator Id: [%d] \n", vectorPC[i].id);
        fprintf(f, "Calculator Brand: [%s] \n", vectorPC[i].brand);
        fprintf(f, "Calculator CPU: [%s] \n", vectorPC[i].CPU);
        fprintf(f, "Calculator Memorie RAM: [%d] Gbytes \n", vectorPC[i].RAM);
        fprintf(f, "Calculator capacitate: [%d] GB \n", vectorPC[i].capacitate);
        fprintf(f, "Calculator pret: [%.2f] $ \n", vectorPC[i].pret);
        fprintf(f, "--------------------------------------------------------------\n");
    }
    fclose(f);
    printf("Fisier text creat. \n", calculatoare);
}

// Lista simpla inlantuita;
typedef struct Node
{
    PC data;
    struct Node *next;

} Node;

void inserareInceputLista(Node **cap, PC calculator)
{
    Node *nouNode = (Node *)malloc(sizeof(Node));
    nouNode->data = calculator; // shallow copy, numai pentru copy de obiecte dupa cel original/initial;
    nouNode->data.brand = (char *)malloc((strlen(calculator.brand) + 1) * sizeof(char));
    strcpy(nouNode->data.brand, calculator.brand);
    nouNode->next = (*cap);
    (*cap) = nouNode;
}

void inserareSfarsitLista(Node **cap, PC calculator)
{
    Node *nouNod = (Node *)malloc(sizeof(Node));
    nouNod->data = calculator;
    nouNod->data.brand = (char *)malloc((strlen(calculator.brand) + 1) * sizeof(char));
    strcpy(nouNod->data.brand, calculator.brand);
    nouNod->next = NULL;
    if ((*cap) != NULL)
    {
        Node *pointer = (*cap);
        while (pointer->next)
        {
            pointer = pointer->next;
        }
        pointer->next = nouNod;
    }
    else
    {
        (*cap) = nouNod;
    }
}
// stergere Node dupa pozitie, conditia fiind "id";
void stegereNodDupaPozitie(Node **cap, int id)
{
    while ((*cap) && (*cap)->data.id == id)
    {
        Node *aux = *cap;
        (*cap) = aux->next;
        if (aux->data.brand != NULL)
        {
            free(aux->data.brand);
        }
        free(aux);
    }
    if ((*cap))
    {
        Node *p = *cap;
        while (p)
        {
            while (p->next && p->next->data.id != id)
            {
                p = p->next;
            }
            if (p->next)
            {
                Node *temp = p->next;
                p->next = temp->next;
                if (temp->data.brand != NULL)
                {
                    free(temp->data.brand);
                }
                free(temp);
            }
            else
            {
                p = NULL;
            }
        }
    }
}

float calculezaPretMediu(Node *cap)
{
    float suma = 0;
    int contor = 0;
    while (cap != NULL)
    {
        suma += cap->data.pret;
        contor++;
        cap = cap->next;
    }
    if (contor > 0)
    {
        return suma / contor;
    }
    return 0;
}

float pretulCalculatoareAcelasiBrand(Node *cap, const char *brandCautat)
{
    float suma = 0;

    while (cap != NULL)
    {
        if (strcmp(cap->data.brand, brandCautat) == 0)
        {
            suma += cap->data.pret;
        }
        cap = cap->next;
    }
    return suma;
}

void printLista(Node *cap)
{
    printf("\nLista Simpla inlantuita este: \n");
    while (cap != NULL)
    {
        display(cap->data);
        // printf(" %d --->>", cap->data);
        cap = cap->next;
        printf(" -->> \n");
    }
}

void dezalocareLista(Node **cap)
{

    while (*cap != NULL)
    {
        Node *pointer = (*cap);
        (*cap) = (*cap)->next;
        if (pointer->data.brand)
        {
            free(pointer->data.brand);
            printf("Free. \n");
        }
        free(pointer);
        pointer->data.brand = NULL;
    }
}

int main()
{
    // PC pc1 = inputs();
    // setPret(&pc1, 355.55); // setare pret nou, modificare atribut pret;
    // float redus = reducerePret(pc1, 10);
    // printf("Redus de la %.2f $ ", redus);

    // PC pc2 = initializare(1000, "MacBook", "Apple M3 Max", 32, 512, 899.88);
    // setBrand(&pc2, "MacBook Pro M1");
    // display(pc2);

    // vector alocat dinamic;
    int nrCalculatoare = 6;
    PC *vectorPC = (PC *)malloc(nrCalculatoare * sizeof(PC));
    vectorPC[0] = initializare(101, "Acer Nitro", "Intel i7 ", 32, 512, 700.99);
    vectorPC[1] = initializare(202, "Lenovo", "AMD Ryzen", 16, 256, 620.19);
    vectorPC[2] = initializare(303, "Asus Pro", "Intel i9 Core", 64, 1024, 909.99);
    vectorPC[3] = initializare(404, "Dell", "Intel i5 R", 16, 256, 500.99);
    vectorPC[4] = initializare(505, "MacBook", "Apple A16", 32, 512, 887.99);
    vectorPC[5] = initializare(606, "Toshiba", "AMD Ryzen 3x", 32, 256, 455.78);
    displayVector(vectorPC, nrCalculatoare);

    // vector ce stocheaza PC cu capacitate > 256 GB;
    int dim1 = 0;
    int dim2 = 0;
    PC *spatiu = vectorCapacitate(vectorPC, nrCalculatoare, 256, &dim1);
    displayVector(spatiu, dim1);
    //  Vector ce stocheaza PC cu RAM <= 16 GBtyes;
    PC *vectorRAM = vectorMinRAM(vectorPC, nrCalculatoare, 16, &dim2);
    displayVector(vectorRAM, dim2);

    printf("Suma a doi vector:---------------------------------------------------------------------------- \n");
    int dimFinal = dim1 + dim2;
    PC *concat = concatVectori(spatiu, vectorRAM, dim1, dim2);
    displayVector(concat, dimFinal);

    // createFileTxt(vectorPC, nrCalculatoare, "Calculatoare.txt");

    dezalocare(&vectorPC, &nrCalculatoare);
    dezalocare(&spatiu, &dim1);
    dezalocare(&vectorRAM, &dim2);
    dezalocare(&concat, &dimFinal);

    // Linked list;
    PC calculator1 = initializare(1000, "Asus Pro 3", "Intel I9", 16, 256, 500.10);
    PC calculator2 = initializare(1001, "Acer Nitro 5", "AMD Duron x6", 32, 512, 640.00);
    PC calculator3 = initializare(1002, "Dell", "Intel i9 Turbo", 64, 1024, 1280.89);
    PC calculator4 = initializare(1003, "Lenovo Legion", "AMD e15", 32, 512, 870.30);
    PC calculator5 = initializare(3004, "Dell", "Intel i3", 16, 256, 456.44);
    PC calculator6 = initializare(3004, "MacBook Pro 2T", "Apple M3", 32, 512, 1099.99);

    Node *cap = NULL;

    inserareInceputLista(&cap, calculator1);
    inserareInceputLista(&cap, calculator2);
    inserareInceputLista(&cap, calculator3);
    inserareInceputLista(&cap, calculator4);
    inserareSfarsitLista(&cap, calculator5);
    inserareInceputLista(&cap, calculator6);
    printLista(cap);

    printf("\nPret Mediu este: %.2f $ \n", calculezaPretMediu(cap));
    printf("\nPret Total al PC-urilor este: %.2f $ \n", pretulCalculatoareAcelasiBrand(cap, "Dell"));

    printf("\nStergere Calculatoare dupa ID: 3004 \n");
    stegereNodDupaPozitie(&cap, 3004);
    printLista(cap);

    // createFileTxt(&calculator6, 6, "Pc-uri.txt");
    dezalocareLista(&cap);

    return 0;
}
