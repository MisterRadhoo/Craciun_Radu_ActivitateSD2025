#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Ochelari
{
    int id;
    char *brand;
    float pret;

} O;

O init(int id, const char *nume, float pret)
{
    O ochelari;
    ochelari.id = id;
    ochelari.brand = (char *)malloc((strlen(nume) + 1) * sizeof(char));
    strcpy(ochelari.brand, nume);
    ochelari.pret = pret;
    return ochelari;
}

void afisareOchelari(O ochelari)
{
    printf("\nId: [ %d ]; Brand: [ %s ]; Pret: [ %.2f ] $.", ochelari.id, ochelari.brand, ochelari.pret);
}

void dezalocareOchelari(O *o)
{
    if (o->brand != NULL)
    {
        free(o->brand);
        o->brand = NULL;
    }
}

typedef struct AVL
{
    O infoUtil;
    struct AVL *st;
    struct AVL *dr;

} AVL;

int inaltimeAVL(AVL *rad)
{
    if (rad != NULL)
    {
        int Hs = inaltimeAVL(rad->st);
        int Hd = inaltimeAVL(rad->dr);
        return 1 + (Hs > Hd ? Hs : Hd);
    }
    else
    {
        return 0;
    }
}

// Factorul de balans este proprietarea unui AVL, care mentine arborele auto-echilibrat, avand valori de [ -1, 0, 1];
// inaltimea unui AVL tree trebuire sa fie mentinuta la un nivel cat mai redus, intra in calcul factorul de balans;
int factorDeBalans(AVL *rad)
{
    return inaltimeAVL(rad->st) - inaltimeAVL(rad->dr);
}

void rotireStanga(AVL **rad)
{
    AVL *aux = (*rad)->dr;
    (*rad)->dr = aux->st;
    aux->st = (*rad);
    (*rad) = aux;
}

void rotireDreapta(AVL **rad)
{
    AVL *aux2 = (*rad)->st;
    (*rad)->st = aux2->dr;
    aux2->dr = (*rad);
    (*rad) = aux2;
}

void inserareAVL(AVL **rad, O ochelari)
{
    if ((*rad) != NULL)
    {
        if (ochelari.id < (*rad)->infoUtil.id)
        {
            inserareAVL(&(*rad)->st, ochelari);
        }
        else
        {
            inserareAVL(&(*rad)->dr, ochelari);
        }
        // verificare grad de echilibru;
        int FB = factorDeBalans(*rad);
        if (FB == -2)
        {
            // dezechilibru in partea dreapta;
            if (factorDeBalans((*rad)->dr) == 1)
            {
                // rotire dreapta;
                rotireDreapta(&(*rad)->dr);
            }
            rotireStanga(rad);
        }
        if (FB == 2)
        {
            // dezechilibru in partea stanga;
            if (factorDeBalans((*rad)->st) == -1)
            {
                // rotire stanga;
                rotireStanga(&(*rad)->st);
            }
            rotireDreapta(rad);
        }
    }
    else
    {
        AVL *nou = (AVL *)malloc(sizeof(AVL));
        nou->st = NULL;
        nou->dr = NULL;
        nou->infoUtil = ochelari; // shallow copy;
        (*rad) = nou;
    }
}

// RSD;
void afisarePreOrderAVL(AVL *rad)
{
    if (rad != NULL)
    {
        afisareOchelari(rad->infoUtil);
        afisarePreOrderAVL(rad->st);
        afisarePreOrderAVL(rad->dr);
    }
}

// SRD;
void parcurgereInOrdineAVL(AVL *rad)
{
    if (rad != NULL)
    {
        parcurgereInOrdineAVL(rad->st);
        afisareOchelari(rad->infoUtil);
        parcurgereInOrdineAVL(rad->dr);
    }
}

// SDR;
void parcurgerePostOrdineAVL(AVL *rad)
{
    if (rad != NULL)
    {
        parcurgerePostOrdineAVL(rad->st);
        parcurgerePostOrdineAVL(rad->dr);
        afisareOchelari(rad->infoUtil);
    }
}

void dezalocareAVL(AVL **rad)
{
    if ((*rad) != NULL)
    {
        dezalocareAVL(&(*rad)->st);
        dezalocareAVL(&(*rad)->dr);
        dezalocareOchelari(&(*rad)->infoUtil);
        free((*rad));
        (*rad) = NULL;
        printf("\nfree AVL Tree......\n");
    }
}

float pretTotal(AVL *rad)
{
    if (rad == NULL)
    {
        return 0;
    }
    else
    {
        return (rad->infoUtil.pret + pretTotal(rad->st) + pretTotal(rad->dr));
    }
}

int nrNoduri(AVL *rad)
{
    if (rad == NULL)
    {
        return 0;
    }
    else
    {
        return (1 + nrNoduri(rad->st) + nrNoduri(rad->dr));
    }
}

O getId(AVL *rad, int id)
{
    if (rad != NULL)
    {
        if (id < rad->infoUtil.id)
        {
            return getId(rad->st, id);
        }
        else if (id > rad->infoUtil.id)
        {
            return getId(rad->dr, id);
        }
        else
        {
            return rad->infoUtil;
        }
    }
    O ochelari;
    ochelari.id = -1;
    return ochelari;
}

int main()
{
    O ochelari1 = init(10, "RayBan", 150.00);
    O ochelari2 = init(67, "Oakley", 350.00);
    O ochelari3 = init(29, "Gucci", 550.00);
    O ochelari4 = init(46, "Fendi", 657.88);
    O ochelari5 = init(55, "RayBan", 257.00);
    O ochelari6 = init(99, "Cartier", 1150.00);
    O ochelari7 = init(32, "Lacoste", 160.00);
    O ochelari8 = init(18, "Lanvin", 750.00);

    // initializare AVL tree;
    AVL *root = NULL;
    inserareAVL(&root, ochelari4);
    inserareAVL(&root, ochelari2);
    inserareAVL(&root, ochelari1);
    inserareAVL(&root, ochelari3);
    inserareAVL(&root, ochelari5);
    inserareAVL(&root, ochelari6);
    inserareAVL(&root, ochelari7);
    inserareAVL(&root, ochelari8);

    printf("\nParcurgere AVL tree in PreOrdine....\n");
    afisarePreOrderAVL(root);

    printf("\nParcurgere AVL tree in InOrdine:.....\n");
    parcurgereInOrdineAVL(root);

    printf("\nParcurgere AVL tree in PostOrdine....\n");
    parcurgerePostOrdineAVL(root);

    int h = inaltimeAVL(root);
    printf("\nInaltime AVL: [ %d ].\n", h);

    O ochelariId = getId(root, 99);
    if (ochelariId.id != -1)
    {
        printf("\nOchelari cu id gasit.\n");
        afisareOchelari(ochelariId);
    }
    else
    {
        printf("\nId negasit!\n");
    }

    return 0;
}