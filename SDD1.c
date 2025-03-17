#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Laptop
{
    char *brand;
    int RAM;
    float capacitate;
    float rezolutie;
    int nrTaste;
    int *nrApasariTasta;
};

struct Laptop initializare() {}
void display(struct Laptop l) {}
void freeMemory(struct Laptop *laptop) {}

struct Node
{
    struct Laptop laptop;
    struct Node *next;
};

int main()
{
    return 0;
}