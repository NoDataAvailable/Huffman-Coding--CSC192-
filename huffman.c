/*************************************
 Name:                  Huffman Coding
 Author:            Roberto Bortolussi
 Student Number:             998837022
 Course:                        CSC192
**************************************/

#include <stdio.h>
#include <stdlib.h>
//#include "PQueue.h"

#define N 256

int *pq;
int length, size;

void initializePriorityQueue(int sizeOfQueue);
//after this function is called, your heap based priority queue condition must be satisfied.
//see above note for the condition
void insertInPriorityQueue(int v);
//after this function is called, your heap based priority queue condition must be satisfied.
//see above note for the condition
int getMaximumPriorityItem();

main()
{
    return 0;
};

void initializePriorityQueue(int sizeOfQueue)
{
    length = sizeOfQueue;
    pq = malloc(sizeof(int)*sizeOfQueue);
};

void insertInPriorityQueue(int v)
{
    size++;
    int tempA = v;
    int i,j;
    for (i=0;i<size-1 && tempA<pq[i];i++);
    for (j=i;j<size;j++)
    {
        int tempB = pq[j];
        pq[j]=tempA;
        tempA=tempB;
    }
};

int getMaximumPriorityItem() {return pq[--size];};

