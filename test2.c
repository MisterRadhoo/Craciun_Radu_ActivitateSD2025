#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Bec
{
    int id;
    char *producator;
    float pret;

} B;

B initializare(int id, const char *prod, float pret)
{
    B bec;
    bec.id = id;
    bec.producator = (char *)malloc((strlen(prod) + 1) * sizeof(char));
    strcpy(bec.producator, prod);
    bec.pret = pret;
    return bec;
}

void afisareBec(B bec)
{
    printf("\nId: [ %d ], \nProducator: -->> [ %s ], \nPret: [ %.2f ] lei. \n", bec.id, bec.producator, bec.pret);
}

void dezalocareBec(B *b)
{
    if (b->producator != NULL)
    {
        free(b->producator);
        b->producator = NULL;
        printf("\nFree bec....\n");
    }
}

// implementare Node pentru ABC; // Arbore binar de cautare;
typedef struct Node
{
    B info;
    struct Node *st;
    struct Node *dr;

} Node;

int hBST(Node *root)
{
    if (root != NULL)
    {
        int Hs = hBST(root->st);
        int Hd = hBST(root->dr);
        return 1 + (Hs > Hd ? Hs : Hd);
    }
    else
    {
        return 0;
    }
}

// factorul de balans in arbore binar de cautare;
//  in AVL tree, Factorul de Balans trebuie sa aiba valoarea [-1, 0, 1] sa mentina AVL tree auto-echilibrat;
int factorDeBalans(Node *root)
{
    return hBST(root->st) - hBST(root->dr);
}

void rotireStanga(Node **root)
{
    Node *aux = (*root)->dr;
    (*root)->dr = aux->st;
    aux->st = (*root);
    (*root) = aux;
}

void rotireDreapta(Node **root)
{
    Node *aux2 = (*root)->st;
    (*root)->st = aux2->dr;
    aux2->dr = (*root);
    (*root) = aux2;
}

void inserareABC(Node **root, B becNou)
{
    if ((*root) != NULL)
    {
        if (becNou.id < (*root)->info.id)
        {
            inserareABC(&(*root)->st, becNou);
        }
        else
        {
            inserareABC(&(*root)->dr, becNou);
        }
        int FB = factorDeBalans(*root);
        if (FB == -2)
        { // dezechilibru pe partea dreapta;
            if (factorDeBalans((*root)->dr) == 1)
            {
                // rotire dreapta;
                rotireDreapta(&(*root)->dr);
            }
            rotireStanga(root);
        }
        if (FB == 2)
        {
            // dezechilibru pe partea stanga;
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
        Node *nouNode = (Node *)malloc(sizeof(Node));
        nouNode->st = NULL;
        nouNode->dr = NULL;
        nouNode->info = becNou;
        nouNode->info.producator = (char *)malloc((strlen(becNou.producator) + 1) * sizeof(char));
        strcpy(nouNode->info.producator, becNou.producator);
        (*root) = nouNode;
    }
}

// traversare ABC PreOrdine -> RSD;
void preOrdine(Node *root)
{
    if (root != NULL)
    {
        afisareBec(root->info);
        preOrdine(root->st);
        preOrdine(root->dr);
    }
}

//  traversare ABC inOrdine -> SRD;
void inOrdine(Node *root)
{
    if (root != NULL)
    {
        inOrdine(root->st);
        afisareBec(root->info);
        inOrdine(root->dr);
    }
}

// traversare ABC PostOrdine -> SDR;
void postOrdine(Node *root)
{
    if (root != NULL)
    {
        postOrdine(root->st);
        postOrdine(root->dr);
        afisareBec(root->info);
    }
}

void dezalocareABC(Node **root)
{
    if ((*root) != NULL)
    {
        dezalocareABC(&(*root)->st);
        dezalocareABC(&(*root)->dr);
        free((*root)->info.producator);
        free((*root));
        (*root) = NULL;
        printf("\nABC free........\n");
    }
}

int nrNoduri(Node *root)
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

float PretulBecurilorUnuiProd(Node *root, const char *prod)
{
    if (root == NULL)
    {
        return 0;
    }
    float suma = 0;
    if (strcmp(root->info.producator, prod) == 0)
    {
        suma += root->info.pret;
    }
    return (suma + PretulBecurilorUnuiProd(root->st, prod) + PretulBecurilorUnuiProd(root->dr, prod));
}

float pretTotal(Node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        return (root->info.pret + pretTotal(root->st) + pretTotal(root->dr));
    }
}

B getId(Node *root, int id)
{
    if (root == NULL)
    {
        B bec = {-1, NULL, 0.00};
        return bec;
    }

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

// driver code;
int main()
{
    B b1 = initializare(999, "Lights & Color", 67.77);
    B b2 = initializare(1000, "Atomic Lights", 110.99);
    B b3 = initializare(888, "Light Company", 56.89);
    B b4 = initializare(776, "Phillips", 95.00);
    B b5 = initializare(221, "SuperLights Extreme", 257.77);
    B b6 = initializare(223, "SuperLights Extreme", 234.44);
    B b7 = initializare(1929, "L&L", 89.99);
    B b8 = initializare(1010, "Bec SRL", 39.77);

    Node *root = NULL;

    inserareABC(&root, b2);
    inserareABC(&root, b1);
    inserareABC(&root, b3);
    inserareABC(&root, b4);
    inserareABC(&root, b5);
    inserareABC(&root, b7);
    inserareABC(&root, b8);
    inserareABC(&root, b6);

    printf("\nAfisare inOrdine ABC........\n");
    // inOrdine(root);

    printf("\nAfisare preOrdine ABC........\n");
    // preOrdine(root);

    int h = hBST(root);
    printf("\nInnaltime ABC: [ %d ], \n", h);

    float total = pretTotal(root);
    printf("\nPret total: [ %.2f ] lei.\n", total);

    float pretBecProd = PretulBecurilorUnuiProd(root, "SuperLights Extreme");
    printf("\n[ %.2f ] lei", pretBecProd);

    int FB = factorDeBalans(root);
    printf("\nFactorul de balans: -->> [ %d ], \n", FB);

    printf("\nAfisare postOrdine ABC........\n");
    postOrdine(root);

    dezalocareABC(&root);
    return 0;
}