#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// implementare Node pentru arbore binar cautare ABC;
typedef struct AVL
{
    int data;
    struct AVL *st;
    struct AVL *dr;

} AVL;

// calculare h-inaltine AVL tree;
int hAVL(AVL *root)
{
    if (root != NULL)
    {
        int Hs = hAVL(root->st);
        int Hd = hAVL(root->dr);
        return 1 + (Hs > Hd ? Hs : Hd);
    }
    else
    {
        return 0;
    }
}

int factorBalans(AVL *root)
{
    return hAVL(root->st) - hAVL(root->dr);
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

void inserareAVL(AVL **root, int value)
{
    if ((*root) != NULL)
    {
        if (value < (*root)->data)
        {
            inserareAVL(&(*root)->st, value);
        }
        else
        {
            inserareAVL(&(*root)->dr, value);
        }
        // verificare factor de balans;
        int FB = factorBalans(*root);
        if (FB == -2)
        {
            // dezechilibru in partea dreapta;
            if (factorBalans((*root)->dr) == 1)
            { // rotire dreapta;
                rotireDreapta(&(*root)->dr);
            }
            rotireStanga(root);
        }
        if (FB == 2)
        {

            // dezechilibru in partea stanga;
            if (factorBalans((*root)->st) == -1)
            {
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
        nouNode->data = value;
        (*root) = nouNode;
    }
}

// traversare postOrdine -> SDR;
void postOrdine(AVL *root)
{
    if (root != NULL)
    {
        postOrdine(root->st);
        postOrdine(root->dr);
        printf("\nPostOrdine AVL tree: [ %d ] \n", root->data);
    }
}

// SRD;
void inOrdine(AVL *root)
{
    if (root != NULL)
    {
        inOrdine(root->st);
        printf("\nInOrdine AVL tree: [ %d ] --> \n", root->data);
        inOrdine(root->dr);
    }
}

// RSD;
void preOrdine(AVL *root)
{
    if (root != NULL)
    {
        printf("\nPreOrdine AVL tree: [ %d ] --> \n", root->data);
        preOrdine(root->st);
        preOrdine(root->dr);
    }
}

void dezalocareAVL(AVL **root)
{
    if ((*root) != NULL)
    {
        dezalocareAVL(&(*root)->st);
        dezalocareAVL(&(*root)->dr);
        free((*root));
        (*root) = NULL;
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

int sum(AVL *root)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        return (root->data + sum(root->st) + sum(root->dr));
    }
}
int search(AVL *root, int value)
{
    if (root != NULL)
    {
        if (value < root->data)
        {
            return search(root->st, value);
        }
        else if (value > root->data)
        {
            return search(root->dr, value);
        }
        else
        {
            return root->data;
        }
    }
    return -1;
}

int main()
{
    AVL *root = NULL;
    inserareAVL(&root, 24);
    inserareAVL(&root, 13);
    inserareAVL(&root, 3);
    inserareAVL(&root, 65);
    inserareAVL(&root, 176);
    inserareAVL(&root, 15);
    inserareAVL(&root, 32);
    inserareAVL(&root, 9);
    inserareAVL(&root, 44);

    postOrdine(root);
    preOrdine(root);
    inOrdine(root);

    printf("\nSuma tuturor valorilor din AVL: -->> [ %d ]\n", sum(root));
    printf("\nInaltime AVL: -->> [ %d ], \n", hAVL(root));
    printf("\nFactorul de balans: [ %d ], \n", factorBalans(root));
    int key = search(root, 24);
    printf("\n[%d],", key);
}