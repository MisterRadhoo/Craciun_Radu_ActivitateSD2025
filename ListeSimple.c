#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Calculator
{
    int id;
    char *brand;
    float pret;

} PC;

PC initializare(int id, const char *nume, float pret)
{
    PC pc;
    pc.id = id;
    pc.brand = (char *)malloc((strlen(nume) + 1) * sizeof(char));
    strcpy(pc.brand, nume);
    pc.pret = pret;
    return pc;
}

void afisarePC(PC pc)
{
    printf("\nId: [ %d ]; Brand PC: [ %s ]; Pret: -->> [ %.2f ] lei. \n", pc.id, pc.brand, pc.pret);
}

void dezalocarePC(PC *pc)
{
    if (pc->brand != NULL)
    {
        free(pc->brand);
        pc->brand = NULL;
        printf("\nfree pc....\n");
    }
}

int main()
{

    return 0;
}