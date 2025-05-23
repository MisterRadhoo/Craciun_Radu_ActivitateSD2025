#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Ceas
{
    int id;
    char *brand;
    float pret;

} C;

C initializare(int id, const char *brand, float pret)
{
    C ceas;
    ceas.id = id;
    ceas.brand = (char *)malloc(sizeof(char) * (strlen(brand) + 1));
    strcpy(ceas.brand, brand);
    ceas.pret = pret;
    return ceas;
}

void afisareCeas(C ceas)
{
    printf("\nid: [ %d ], \nBrand: [ %s ], \nPret: [ %.2f ] $.\n", ceas.id, ceas.brand, ceas.pret);
}

typedef struct AVL
{
    C info;
    struct AVL *st; // subarborele stang AVL;
    struct AVL *dr; // subarborele drept AVL;

} AVL;

int inaltimeAVL(AVL *root)
{
    if (root != NULL)
    {
        int Hs = inaltimeAVL(root->st);
        int Hd = inaltimeAVL(root->dr);
        return 1 + (Hs > Hd ? Hs : Hd);
    }
    else
    {
        return 0;
    }
}

int factorDeBalans(AVL *root)
{
    return inaltimeAVL(root->st) - inaltimeAVL(root->dr);
}

void rotireStanga(AVL **root)
{
    AVL *aux = (*root)->dr;
    (*root)->dr = aux->st;
    aux->st = (*root);
    (*root) = aux;
}

void rotireDreapta(AVL **root)
{
    AVL *aux2 = (*root)->st;
    (*root)->st = aux2->dr;
    aux2->dr = (*root);
    (*root) = aux2;
}

void inserareAVL(AVL **root, C ceasNou)
{
    if ((*root) != NULL)
    {
        if (ceasNou.id < (*root)->info.id)
        {
            inserareAVL(&(*root)->st, ceasNou);
        }
        else
        {
            inserareAVL(&(*root)->dr, ceasNou);
        }
        int FB = factorDeBalans(*root);
        if (FB == -2)
        {
            // dezechilibru in partea dreapta;
            if (factorDeBalans((*root)->dr) == 1)
            {

                // rotire dreata;
                rotireDreapta(&(*root)->dr);
            }
            rotireStanga(root);
        }
        if (FB == 2)
        {
            // dezechilibru in partea stanga;
            if (factorDeBalans((*root)->st) == -1)
            {
                // rotire stanga;
                rotireStanga(&(*root)->st);
            }
            rotireDreapta(root);
        }
    }
    else
    {
        AVL *nouNode = (AVL *)malloc(sizeof(AVL));
        nouNode->st = NULL;
        nouNode->dr = NULL;
        nouNode->info = ceasNou;
        nouNode->info.brand = (char *)malloc((strlen(ceasNou.brand) + 1) * sizeof(char));
        strcpy(nouNode->info.brand, ceasNou.brand);
        (*root) = nouNode;
    }
}

int nrNoduri(AVL *root)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        return (1 + nrNoduri(root->st) + nrNoduri(root->dr));
    }
}

// traversare postOrder AVL tree -> SDR;
void postOrder(AVL *root)
{
    if (root != NULL)
    {

        postOrder(root->st);
        postOrder(root->dr);
        afisareCeas(root->info);
    }
}

// traversare inOrder AVL tree-> SRD;
void inOrder(AVL *root)
{
    if (root != NULL)
    {

        inOrder(root->st);
        afisareCeas(root->info);
        inOrder(root->dr);
    }
}

void preOrder(AVL *root)
{
    if (root != NULL)
    {

        afisareCeas(root->info);
        preOrder(root->st);
        preOrder(root->dr);
    }
}

void dezalocareAVL(AVL **root)
{
    if ((*root) != NULL)
    {
        dezalocareAVL(&(*root)->st);
        dezalocareAVL(&(*root)->dr);
        free((*root)->info.brand);
        free((*root));
        (*root) = NULL;
    }
}

C getId(AVL *root, int id)
{
    C ceas;
    ceas.id = -1;
    ceas.brand = NULL;
    ceas.pret = 0.00f;
    if (root != NULL)
    {
        if (id < root->info.id)
        {
            return getId(root->st, id);
        }
        else if (id > root->info.id)
        {
            return getId(root->dr, id);
        }
        else
        {
            return root->info;
        }
    }
    return ceas;
}

float sum(AVL *root)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        return (root->info.pret + sum(root->st) + sum(root->dr));
    }
}

int main()
{
    C c = initializare(89, "Omega SpeedMaster", 2400.55);
    C c1 = initializare(109, "Rolex Rust", 3400.00);
    C c2 = initializare(99, "Tudor Pelagos", 5699.89);
    C c3 = initializare(26, "Casio G-shock", 124.55);
    C c4 = initializare(19, "Seiko Diver", 220.55);
    C c5 = initializare(54, "Skeletor CHinatown", 24.55);
    C c6 = initializare(88, "Rolex Daytona", 8999.99);
    C c7 = initializare(189, "AP", 20000.00);
    // afisareCeas(c);

    AVL *root = NULL;

    inserareAVL(&root, c);
    inserareAVL(&root, c1);
    inserareAVL(&root, c2);
    inserareAVL(&root, c3);
    inserareAVL(&root, c4);
    inserareAVL(&root, c5);
    inserareAVL(&root, c6);
    inserareAVL(&root, c7);

    printf("\nAfisare AVL postOrdine.......\n");
    postOrder(root);
    printf("\nAfisare AVL inOrdine.......\n");
    inOrder(root);
    printf("\nAfisare AVL preOrdine.......\n");
    preOrder(root);

    int h = inaltimeAVL(root);
    printf("\nInaltime AVL: [ %d ], ", h);
    int factor = factorDeBalans(root);
    printf("\nFactor de balans AVL: [ %d ], \n", factor);
    C idCeas = getId(root, 189);

    if (idCeas.id != -1)
    {
        afisareCeas(idCeas);
    }
    else
    {
        printf("\nId ceas nu a fost gasit!\n");
    }

    float total = sum(root);
    printf("\nSuma totala: [%.2f] $ \n", total);

    dezalocareAVL(&root);

    return 0;
}