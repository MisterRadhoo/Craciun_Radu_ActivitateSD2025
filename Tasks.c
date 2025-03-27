#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// testing.....;
// Task1 {Structura si functii};// Task 2 {Vectori....}
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
// calculeaza reducere la pret obiect;
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
void setBrand(PC *pc, const char *brandNou)
{
    if (pc->brand != NULL)
    {
        free(pc->brand);
    }
    pc->brand = (char *)malloc((strlen(brandNou) + 1) * sizeof(char));
    strcpy(pc->brand, brandNou);
}
void dezalocare(PC *pc)
{

    if (pc->brand != NULL)
    {
        free(pc->brand);
        printf("Free Memory ! \n");
    }
    pc->brand = NULL;
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

int main()
{
    // PC pc1 = inputs();
    // setPret(&pc1, 355.55); // setare pret nou, modificare atribut pret;
    // float redus = reducerePret(pc1, 10);
    // printf("Redus de la %.2f $ ", redus);

    PC pc2 = initializare(1000, "MacBook", "Apple M3 Max", 32, 512, 899.88);
    setBrand(&pc2, "MacBook Pro M1");
    // display(pc2);

    // vector alocat dinamic;
    int nrCalculatoare = 5;
    PC *vectorPC = (PC *)malloc(nrCalculatoare * sizeof(PC));
    vectorPC[0] = initializare(101, "Acer Nitro", "Intel i7 ", 32, 512, 700.99);
    vectorPC[1] = initializare(202, "Lenovo", "AMD Ryzen", 16, 256, 620.19);
    vectorPC[2] = initializare(303, "Asus Pro", "Intel i9 Core", 64, 1024, 909.99);
    vectorPC[3] = initializare(404, "Dell", "Intel i5 R", 16, 256, 500.99);
    vectorPC[4] = initializare(505, "MacBook", "Apple A16", 32, 512, 887.99);
    displayVector(vectorPC, nrCalculatoare);

    return 0;
}
