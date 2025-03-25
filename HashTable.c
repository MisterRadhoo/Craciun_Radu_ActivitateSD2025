#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Implementare Hash Table;

typedef struct Ochelari
{
    int id;
    char *brand;
    char *provenienta;
    float pret;
} O;
typedef struct Nod
{
    O data;
    struct Nod *next;

} Nod;

typedef struct HashTable
{
    int capacitate;
    Nod **array;

} HT;

O initializare(int id, const char *brand, const char *provenienta, float pret)
{
    O ochelari;
    ochelari.id = id;
    ochelari.brand = (char *)malloc((strlen(brand) + 1) * sizeof(char));
    strcpy(ochelari.brand, brand);
    ochelari.provenienta = (char *)malloc((strlen(provenienta) + 1) * sizeof(char));
    strcpy(ochelari.provenienta, provenienta);
    ochelari.pret = pret;
    return ochelari;
}
void afisare(O o)
{
    printf("Ochelari Id: -->> %d , Brand ochelari: -->> %s \n", o.id, o.brand);
    printf("Tara de fabricatie: -->> %s , Pret ochelari: -->> %.2f $ \n", o.provenienta, o.pret);
}

HT initializareHashTable(int capacitate)
{
    HT ht;
    ht.array = (Nod **)malloc(sizeof(Nod *) * capacitate);
    for (int i = 0; i < capacitate; i++)
    {
        ht.array[i] = NULL;
    }
    ht.capacitate = capacitate;
    return ht;
}
// cheie: brand + id;
int calculeazaHash(const char *brand, int id, int dimensiune)
{
    int suma = 0;
    for (int i = 0; i < strlen(brand); i++)
    {
        suma += brand[i];
    }
    suma += id;
    return (dimensiune > 0 ? (suma % dimensiune) : -1);
}

void afisareLista(Nod *cap)
{
    while (cap)
    {

        afisare(cap->data);
        cap = cap->next;
    }
}
void afisareHashTable(HT ht)
{
    for (int i = 0; i < ht.capacitate; i++)
    {
        printf("\n Cluster [%d]: --->> \n", (i + 1));
        afisareLista(ht.array[i]);
    }
}
// inserare la inceput 'Nod' in lista;
void inserareNodLista(Nod **cap, O ochelari)
{
    Nod *nou = (Nod *)malloc(sizeof(Nod));
    nou->data = ochelari;
    nou->data.brand = (char *)malloc((strlen(ochelari.brand) + 1) * sizeof(char));
    strcpy(nou->data.brand, ochelari.brand);
    nou->data.provenienta = (char *)malloc((strlen(ochelari.provenienta) + 1) * sizeof(char));
    strcpy(nou->data.provenienta, ochelari.provenienta);
    nou->next = (*cap);
    (*cap) = nou;
}
void stergereNodLista(Nod **cap, int id)
{
    if (*cap)
    {
        if ((*cap)->data.id == id)
        {
            Nod *p = (*cap);
            (*cap) = (*cap)->next;
            free(p->data.brand);
            free(p->data.provenienta);
            free(p);
        }
        else
        {
            Nod *p = (*cap);
            while (p->next && p->next->data.id != id)
            {
                p = p->next;
            }
            if (p->next == NULL)
            {
                printf("Node Id: --->> [%d] NU EXISTA. \n", id);
                return;
            }
            Nod *aux = p->next;
            p->next = p->next->next;
            free(aux->data.brand);
            free(aux->data.provenienta);
            free(aux);
        }
    }
}
void inserareElemHashTable(HT hash, O ochelari)
{
    int index = calculeazaHash(ochelari.brand, ochelari.id, hash.capacitate);
    if (index >= 0 && index < hash.capacitate)
    {
        if (hash.array[index] != NULL)
        {
            // avem coliziune;
            inserareNodLista(&(hash.array[index]), ochelari);
        }
        else
        {
            inserareNodLista(&(hash.array[index]), ochelari);
        }
    }
}
void stergereElemHashTable(HT ht, O ochelariVechi)
{
    int index = calculeazaHash(ochelariVechi.brand, ochelariVechi.id, ht.capacitate);
    if (index < 0 || index >= ht.capacitate)
    {
        printf("\n Cheia nu exista. \n");
    }
    else
    {
        stergereNodLista(&(ht.array[index]), ochelariVechi.id);
    }
}
void stergereLista(Nod **cap)
{
    while ((*cap))
    {
        Nod *p = (*cap);
        (*cap) = p->next;
        if (p->data.brand != NULL)
        {
            free(p->data.brand);
            p->data.brand = NULL;
        }
        if (p->data.provenienta)
        {
            free(p->data.provenienta);
            p->data.provenienta = NULL;
        }
        free(p);
    }
}
void freeMemoryHT(HT *ht)
{
    for (int i = 0; i < ht->capacitate; i++)
    {
        stergereLista(&(ht->array[i]));
        // printf("Hash table is free. \n");
    }
    free(ht->array);
    ht->array = NULL;
    ht->capacitate = 0;
}

O getOchelariDupaIdLista(Nod *cap, int id)
{
    while (cap)
    {
        if (cap->data.id == id)
        {
            return cap->data;
        }
        else
        {
            cap = cap->next;
        }
    }
    O ochelari;
    ochelari.id = 0;
    return ochelari;
}
O getOchelariDupaIdHT(HT ht, int id)
{
    O ochelariID;
    for (int i = 0; i < ht.capacitate; i++)
    {
        ochelariID = getOchelariDupaIdLista(ht.array[i], id);
        if (ochelariID.id == id)
        {
            return ochelariID;
        }
    }
    return ochelariID;
}
float pretTotalLista(Nod *cap)
{
    if (cap)
    {
        float suma = 0;
        int contor = 0;
        while (cap)
        {
            suma += cap->data.pret;
            contor++;
            cap = cap->next;
        }
        return suma;
    }
    return 0;
}
// vector bidimensional 2D vector;
float **sumaPreturilorUnuiCluster(HT ht, int *nrClustere)
{
    *nrClustere = 0;
    for (int i = 0; i < ht.capacitate; i++)
    {
        if (ht.array[i] != NULL)
        {
            (*nrClustere)++;
        }
    }
    float **total = (float **)malloc(sizeof(float *) * 2);
    total[0] = (float *)malloc(sizeof(float *) * (*nrClustere));
    total[1] = (float *)malloc(sizeof(float *) * (*nrClustere));

    int index = 0;
    for (int i = 0; i < ht.capacitate; i++)
    {
        if (ht.array[i] != NULL)
        {
            total[0][index] = i;
            total[1][index] = pretTotalLista(ht.array[i]);
            index++;
        }
    }
    return total;
}
void afisareMatrice(float **matrice, int nrCol, int nrLinii)
{
    for (int i = 0; i < nrLinii; i++)
    {
        for (int j = 0; j < nrCol; j++)
        {
            printf("// %.2f ", matrice[i][j]);
        }
        printf("\n");
    }
}
void dezalocareM(float ***matrix, int *nrLinii, int *nrCol)
{
    for (int i = 0; i < *nrLinii; i++)
    {
        free((*matrix)[i]);
        printf("Matrix free. \n");
    }
    free(*matrix);
    *matrix = NULL;
    *nrLinii = 0;
    *nrCol = 0;
}

int main()
{
    Nod *head = NULL;
    O o1 = initializare(1008, "Rayban", "China", 120.24);
    O o2 = initializare(1009, "Gucci", "Italia", 400);
    O o3 = initializare(1110, "Bottega Venetta", "Taiwan", 1500);
    O o4 = initializare(1111, "Police", "Italia", 420.99);
    O o5 = initializare(99, "Louis Vuitton", "France", 380.99);

    // afisare(o1);

    HT ht = initializareHashTable(5);
    inserareElemHashTable(ht, o5);
    inserareElemHashTable(ht, o1);
    inserareElemHashTable(ht, o2);
    inserareElemHashTable(ht, o3);
    inserareElemHashTable(ht, o4);
    stergereElemHashTable(ht, o5);
    O idO = getOchelariDupaIdHT(ht, 99);
    if (idO.id == 99)
    {
        printf("ID's matched. %d \n", idO.id);
    }
    else
    {
        printf("ID's not found \n");
    }

    // afisareHashTable(ht);
    printf("\n");
    afisareHashTable(ht);

    printf("Pret total pe clustere <<Hash Table>>;  \n");
    int nrClustere = 3;
    float **M = sumaPreturilorUnuiCluster(ht, &nrClustere);
    int nrLinii = 2;
    afisareMatrice(M, nrClustere, 2);
    dezalocareM(&M, &nrLinii, &nrClustere);
    freeMemoryHT(&ht);
    return 0;
}