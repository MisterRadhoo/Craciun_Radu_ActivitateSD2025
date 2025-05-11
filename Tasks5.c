#define _CRT_NO_SECURE_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Task 12 {Stive si Cozi};

typedef struct Parfum
{
    int id;
    char *brand;
    char *scent; // aroma;
    int gramaj;  // u.m 'ml';

} P;

P initializare(int id, const char *brand, const char *aroma, int gramaj)
{
    P parfum;
    parfum.id = id;
    parfum.brand = (char *)malloc((strlen(brand) + 1) * sizeof(char));
    strcpy(parfum.brand, brand);
    parfum.scent = (char *)malloc((strlen(aroma) + 1) * sizeof(char));
    strcpy(parfum.scent, aroma);
    parfum.gramaj = gramaj;
    return parfum;
}

void printParfum(P parfum)
{
    printf("\nid: [ %d ],\nBrand parfum: [ %s ],\nAroma parfum: [ %s ],\nGramaj: --> [ %d ] ml. \n", (parfum.id ? parfum.id : -1), parfum.brand, parfum.scent, parfum.gramaj);
}

void dezalocareParfum(P *parfum)
{
    if (parfum->brand != NULL)
    {
        free(parfum->brand);
        parfum->brand = NULL;
    }
    if (parfum->scent != NULL)
    {
        free(parfum->scent);
        parfum->scent = NULL;
        printf("\nfree parfum....\n");
    }
}

// implementare Lista simpla inlantuita struct;
typedef struct Node
{
    // int data;
    P data;
    struct Node *next;

} Node;

typedef struct Stack
{
    Node *top;

} Stack;

void push(Stack *stack, P parfum)
{
    Node *nou = (Node *)malloc(sizeof(Node));
    if (nou == NULL)
    {
        printf("\nErorare de alocare de memorie. \n");
        return;
    }

    nou->data = parfum;
    nou->data.brand = (char *)malloc((strlen(parfum.brand) + 1) * sizeof(char));
    strcpy(nou->data.brand, parfum.brand);
    nou->data.scent = (char *)malloc((strlen(parfum.scent) + 1) * sizeof(char));
    strcpy(nou->data.scent, parfum.scent);
    nou->next = stack->top;
    stack->top = nou;
}

void pop(Stack *stack)
{
    if (stack->top == NULL)
    {
        printf("\nStiva e goala. \n");
        return;
    }
    Node *temp = stack->top;
    printf("\nElement scos: [%d] \n", temp->data.id);
    stack->top = stack->top->next;
    dezalocareParfum(&temp->data);
    free(temp);
}

void peek(Stack *stack)
{
    if (stack->top == NULL)
    {
        printf("\nStiva e goala. \n");
    }
    else
    {
        printf("\nElementul/Nod-ul din varf: [ %d ].\n", stack->top->data.id);
    }
}

int isEmpty(Stack *stack)
{
    return stack->top == NULL;
}

void printStack(Stack *stack)
{
    Node *curent = stack->top;
    printf(" \nStiva: \n");
    while (curent != NULL)
    {
        printParfum(curent->data);
        printf("------------------------------\n");
        curent = curent->next;
    }
    printf("\nNULL\n");
}

void freeStack(Stack *stack)
{
    Node *temp;
    while (stack->top != NULL)
    {
        temp = stack->top;
        stack->top = stack->top->next;
        dezalocareParfum(&temp->data);
        free(temp);
    }
}

P getParfumById(Stack *stack, int id)
{
    Node *aux = stack->top;
    while (aux != NULL)
    {
        if (aux->data.id == id)
        {
            return aux->data;
        }
        else
        {
            aux = aux->next;
        }
    }
    P empty = {-1, NULL, NULL, 0};
    printParfum(empty);
    return empty;
}

P getParfumBrand(Stack *stack, const char *numeCautat)
{
    Node *temp = stack->top;
    while (temp != NULL)
    {
        if (strcmp(temp->data.brand, numeCautat) == 0)
        {
            return temp->data;
        }
        else
        {
            temp = temp->next;
        }
    }
    P parfum = {-1, NULL, NULL, 0};
    printParfum(parfum);
    return parfum;
}

// implementare pentru struct Queue; (wrapper struct);
// proprietate Queue: First In, First Out;
typedef struct Queue
{
    Node *front; // extragere primul element/node;
    Node *rear;  // inserare la sfasitul Queue-ului;

} Queue;

void enqueue(Queue *q, P parfum)
{
    Node *nou = (Node *)malloc(sizeof(Node));
    if (nou == NULL)
    {
        printf("\nAlocare de memorie esuata. \n");
        return;
    }
    nou->data = parfum; // shallow copy;
    nou->next = NULL;
    if (q->rear == NULL)
    {
        // Daca queue-ul este gol;
        q->front = q->rear = nou;
    }
    else
    {
        q->rear->next = nou;
        q->rear = nou;
    }
}

void dequeue(Queue *q)
{
    if (q->front == NULL)
    {
        printf("\nCoada este goala. \n");
        return;
    }
    Node *temp = q->front;
    printf("\nElement extras: [ %d ] \n", temp->data.id);
    q->front = q->front->next;

    if (q->front == NULL)
    {
        q->rear = NULL; // Queue a devenit gol;
    }
    dezalocareParfum(&temp->data);
    free(temp);
}

int isEmptyQueue(Queue *q)
{
    return q->front == NULL;
}

void printQueue(Queue *q)
{
    Node *curent = q->front;
    printf("\nCoada: \n");
    while (curent != NULL)
    {
        // printf(" [ %d ] -> ", curent->data);
        printParfum(curent->data);
        curent = curent->next;
    }
    printf("\nNULL\n");
}

void freeQueue(Queue *q)
{

    while (q->front != NULL)
    {
        Node *temp = q->front;
        q->front = q->front->next;
        dezalocareParfum(&temp->data);
        free(temp);
    }
    q->rear = NULL;
}

int main()
{
    P p = initializare(1001, "Aqua di parma", "Citrus", 75);
    P p2 = initializare(1002, "JPG Elixir", "Vanilla", 50);
    P p3 = initializare(1003, "Aqua di Gio", "Fresh-Lemon", 100);
    P p4 = initializare(1004, "Aqua di parma Colonia", "Fresh Grepfrut", 75);
    P p5 = initializare(1005, "PR Phantom", "Sweet vanilla,lavender,", 125);
    // printParfum(p);
    //  dezalocareParfum(&p);

    Stack stack;
    stack.top = NULL;

    push(&stack, p);
    push(&stack, p2);
    push(&stack, p3);
    push(&stack, p4);
    push(&stack, p5);
    peek(&stack);

    printStack(&stack);
    P getIdParfum = getParfumById(&stack, 1004);
    printParfum(getIdParfum);
    dezalocareParfum(&getIdParfum);
    P getBrand = getParfumBrand(&stack, "PR Phantom");
    printParfum(getBrand);
    dezalocareParfum(&getBrand);

    pop(&stack);
    pop(&stack);
    pop(&stack);
    pop(&stack);
    pop(&stack);

    Queue queue;
    queue.front = NULL;
    queue.rear = NULL;

    enqueue(&queue, p);
    enqueue(&queue, p2);
    enqueue(&queue, p3);
    enqueue(&queue, initializare(111, "Dior Hommbre", "woody-spicey", 50));
    enqueue(&queue, initializare(222, "Versace", "PepperMint", 75));
    enqueue(&queue, p4);
    enqueue(&queue, p5);

    if (isEmptyQueue(&queue))
    {
        printf("\nQueue is empty.....\n");
    }
    else
    {
        printf("\nQueue is not empty....[???? ].\n");
    }

    printQueue(&queue);

    dequeue(&queue);
    dequeue(&queue);
    dequeue(&queue);
    dequeue(&queue);
    dequeue(&queue);
    dequeue(&queue);
    dequeue(&queue);

    printQueue(&queue);

    freeStack(&stack);
    freeQueue(&queue);

    dezalocareParfum(&p);
    dezalocareParfum(&p2);
    dezalocareParfum(&p3);
    dezalocareParfum(&p4);
    dezalocareParfum(&p5);

    return 0;
}