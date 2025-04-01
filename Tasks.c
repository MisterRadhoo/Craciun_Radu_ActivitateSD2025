#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// testing.....;
// Task1 {Structura si functii};// Task 2 {Vectori};// Task 5{Liste simple inlantuite};
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
// serminar, laborator 4, liste inlantuite;
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
// Functie care elimina un Nod, dupa pozitia specificata;
void stergereDupaPozitie(Node **cap, int pozitie)
{
    Node *temp = (*cap), *nodAnterior = NULL;
    // Daca lista este goala;
    if (temp == NULL)
    {
        return;
    }
    // Sterge Nod dupa pozitia 1;
    if (pozitie == 1)
    {
        (*cap) = temp->next;
        free(temp->data.brand);
        free(temp);
        return;
    }
    // Parcurge lista pana la un Nod, care trebuie sters;
    for (int i = 1; temp != NULL && i < pozitie; i++)
    {
        nodAnterior = temp;
        temp = temp->next;
    }
    // Stergere Nod gasit;
    if (temp != NULL)
    {
        nodAnterior->next = temp->next;
        free(temp->data.brand);
        free(temp);
    }
    else
    {
        printf("\nDatele nu au fost gasite. !!\n");
    }
}

// Functie care insereaza un Nod si sorteaza dupa pret;(crescator);
Node *inserareSortata(Node *newNode, Node *sortat)
{
    if (sortat == NULL ||
        sortat->data.pret >= newNode->data.pret)
    {
        newNode->next = sortat;
        sortat = newNode;
    }
    else
    {
        Node *nodCurent = sortat;

        while (nodCurent->next != NULL && nodCurent->next->data.pret < newNode->data.pret)
        {
            nodCurent = nodCurent->next;
        }
        newNode->next = nodCurent->next;
        nodCurent->next = newNode;
    }
    return sortat;
}

Node *insertionSort(Node *cap)
{
    Node *sortat = NULL;
    Node *curent = cap;
    while (curent != NULL)
    {
        Node *next = curent->next;
        sortat = inserareSortata(curent, sortat);
        curent = next;
    }
    return sortat;
}

// functie care salveaza obiecte din SLL, in vector(alocat dinamic);
PC *calculatoarePretMic(Node *cap, float pret, int *contor)
{
    (*contor) = 0;
    Node *aux = cap;
    while (aux != NULL)
    {
        if (aux->data.pret <= pret)
        {
            (*contor)++;
        }
        aux = aux->next;
    }

    PC *pretMic = (PC *)malloc((*contor) * sizeof(PC));
    int index = 0;
    aux = cap;
    while (aux != NULL)
    {
        if (aux->data.pret <= pret)
        {
            pretMic[index] = aux->data;
            pretMic[index].brand = (char *)malloc((strlen(aux->data.brand) + 1) * sizeof(char));
            strcpy(pretMic[index].brand, aux->data.brand);
            index++;
        }
        aux = aux->next;
    }
    return pretMic;
}

// seminar liste inlantuite; laborator 4;
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
// interschimbare node-uri liste simpla inlantuite dupa Id;
Node *interschimbareNoduri(Node *cap, int a_id, int b_id)
{
    // daca pozitiile (a==b),return 'cap' lista;
    if (a_id == b_id)
    {
        return cap;
    }
    Node *prevA = NULL, *currA = NULL;
    Node *prevB = NULL, *currB = NULL;
    Node *prev = NULL, *curr = cap;

    // un loop sa gaseasca pozitia 'a' si 'b';
    while (curr != NULL)
    {
        if (curr->data.id == a_id)
        {
            prevA = prev;
            currA = curr;
        }
        else if (curr->data.id == b_id)
        {
            prevB = prev;
            currB = curr;
        }
        prev = curr;
        curr = curr->next;
    }
    // daca pozitia 'a' si 'b' nu sunt prezente, return 'cap' listei;
    if (currA == NULL || currB == NULL)
    {
        return cap;
    }
    // daca node-ul de pe pozitia 'a' nu e 'cap' de lista;
    if (prevA != NULL)
    {
        prevA->next = currB;
    }
    else
    {
        cap = currB;
    }
    // daca node-ul de pe pozitia 'b' nu e 'cap' de list
    if (prevB != NULL)
    {
        prevB->next = currA;
    }
    else
    {
        cap = currA;
    }
    // Schimbam legaturile pointer-ilor 'next';
    Node *temp = currB->next;
    currB->next = currA->next;
    currA->next = temp;

    return cap;
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
/// @brief
void functieTest()
{
}
/// @brief
/// @return

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
    PC calculator7 = initializare(2044, "Lenovo Power Pro", "Inter i7 Turbo", 64, 1024, 1344.55);

    Node *cap = NULL;

    inserareInceputLista(&cap, calculator1);
    inserareInceputLista(&cap, calculator2);
    inserareInceputLista(&cap, calculator3);
    inserareInceputLista(&cap, calculator4);
    inserareSfarsitLista(&cap, calculator5);
    inserareInceputLista(&cap, calculator6);
    inserareSfarsitLista(&cap, calculator7);
    // printLista(cap);

    printf("\nPret Mediu este: %.2f $ \n", calculezaPretMediu(cap));
    printf("\nPretul PC-urilor al aceluiasi brand este: %.2f $ \n", pretulCalculatoareAcelasiBrand(cap, "Dell"));

    printf("\n\n");

    printLista(cap);
    printf("\nStergere Node: -->>  dupa pozitie:----------------------------------------------- \n");
    stergereDupaPozitie(&cap, 2);
    printf("Id sters: %d \n", calculator4.id);
    printLista(cap);
    printf("\n");
    printf("\nInserare prin sortare crescatoare Linked list:--------------------------------------- \n");
    Node *cap1 = insertionSort(cap);
    printLista(cap1);
    printf("\n");
    printf("\nVector ce contine, obiecte PC cu pret <= 800 $---------------------------------------- \n");
    int contor1 = 0;
    PC *vectorPcPretMic = calculatoarePretMic(cap1, 800, &contor1);
    displayVector(vectorPcPretMic, contor1);

    printLista(cap1); // afiseaza lista cu nodurile sortate crescator dupa 'pret';
    printf("\nInterschimbare noduri in lista: primele doua pozitii, dupa ID:-------------------------- \n");
    Node *cap2 = interschimbareNoduri(cap1, 3004, 1000);
    printLista(cap2);
    //  createFileTxt(&calculator6, 6, "Pc-uri.txt");
    dezalocareLista(&cap);
    dezalocareLista(&cap1);
    dezalocareLista(&cap2);

    return 0;
}
