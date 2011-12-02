/*************************************
 Name:                  Huffman Coding
 Author:            Roberto Bortolussi
 Student Number:             998837022
 Course:                        CSC192
**************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "PQueue.h"

#define N 256

struct node *pq;
int length, size;

typedef struct node *link;

struct node
{
    char value;
    int freq;
    link right;
    link left;
};

void initializePriorityQueue(int sizeOfQueue);
//after this function is called, your heap based priority queue condition must be satisfied.
//see above note for the condition
void insertInPriorityQueue(struct node v);
//after this function is called, your heap based priority queue condition must be satisfied.
//see above note for the condition
struct node getMaximumPriorityItem();

int main(int argc, char * argv[])
{
    FILE *fp;
    int strSize = 0;
    char *inStr;
    int freqs[N];
    int i;

    for (i=0;i<N;i++) freqs[i]=0;
    inStr = malloc(sizeof(char));
    inStr[0] = '\0';

    if (fp = fopen("inFile.txt","r"))//argv[1],"r"))
    {
        char ch;
        while (!feof(fp))
        {
            char *temp = inStr;
            strSize++;
            inStr = malloc((strSize+1)*sizeof(char));
            strcpy(inStr,temp);
            free(temp);
            ch = fgetc(fp);
            //printf("%c, %d\n",ch, (int)ch);
            inStr[strSize-1]=ch;
            inStr[strSize]='\0';
            freqs[ch]++;
        };

    }
    else
    {
        printf("Could not open file!");
        exit(EXIT_FAILURE);
    }

    printf(inStr);
    printf("%d\n",freqs['l']);

    initializePriorityQueue(N);

    int j;
    for (j=0;j<N;j++)
        if (freqs[j])
        {
            struct node newNode;
            newNode.value = (char)j;
            newNode.freq = freqs[j];
            newNode.left = NULL;
            newNode.right = NULL;
            insertInPriorityQueue(newNode);
        };

    int k;
    for (k=0;k<size;k++)
    {
        pq[k].freq = pq[k].freq/size;
    };

    return 0;
};

void initializePriorityQueue(int sizeOfQueue)
{
    length = sizeOfQueue;
    pq = malloc(sizeof(int)*sizeOfQueue);
};

void insertInPriorityQueue(struct node v)
{
    size++;
    struct node tempA = v;
    int i,j;
    for (i=0;i<size-1 && (tempA.freq)<(pq[i].freq);i++);
    for (j=i;j<size;j++)
    {
        struct node tempB = pq[j];
        pq[j]=tempA;
        tempA=tempB;
    }
};

struct node getMaximumPriorityItem() {return pq[--size];};

