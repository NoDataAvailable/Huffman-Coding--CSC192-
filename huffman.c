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
#define BIN 10

typedef struct node *link;

link *pq, *storage;
char **binStr;
int length, size, unique;

struct node
{
    char value;
    int freq;
    link right;
    link left;
    link parent;
};

void initializePriorityQueue(int sizeOfQueue);
//after this function is called, your heap based priority queue condition must be satisfied.
//see above note for the condition
void insertInPriorityQueue(link v);
//after this function is called, your heap based priority queue condition must be satisfied.
//see above note for the condition
link getMaximumPriorityItem();
char *getBin(link leaf);

int main(int argc, char * argv[])
{
    FILE *fp;
    int strSize = 0;
    char *inStr;
    int freqs[N];
    int i;

    link root;

    for (i=0;i<N;i++) freqs[i]=0;
    inStr = malloc(sizeof(char));
    inStr[0] = '\0';

    if (fp = fopen(argv[1],"r"))
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
        printf("Could not open file!\n");
        exit(EXIT_FAILURE);
    }

    //printf(inStr);

    initializePriorityQueue(N);


    int j;
    for (j=0;j<N;j++)
        if (freqs[j])
        {
            link newNode;
            newNode = malloc(sizeof(struct node));
            newNode->value = (char)j;
            newNode->freq = freqs[j];
            newNode->left = NULL;
            newNode->right = NULL;
            insertInPriorityQueue(newNode);
            //printf("Size: %d\n",size);
        };

    unique = size;
    storage = malloc(unique*sizeof(struct node));

    int k;
    for (k=0;k<unique;k++)
    {
        storage[k] = pq[k];//size;
    };

    /*for (k=0;size!=0;k++)
    {
        printf("Size: %d/%d\n",k,size);
        struct node next = getMaximumPriorityItem();
        printf("%d, %c\n", next.freq, next.value);
    };*/



    while (size!=0)
    {
        if (size > 1)
        {
        link a,b;
        a = getMaximumPriorityItem();
        b = getMaximumPriorityItem();
        link n;
        n = malloc(sizeof(struct node));
        n->freq = (a->freq+b->freq);
        n->value = (char)(n->freq);
        n->left = a;
        n->right = b;
        a->parent=b->parent=n;
        insertInPriorityQueue(n);
        }
        else
        {
            root = getMaximumPriorityItem();
        };
    };

    printf("Freq:  %d\n",root->left->right->freq);
    printf("Value: %c\n",root->left->right->value);

    // I got a Huffman tree, what now b*tches?

    binStr = malloc(unique*sizeof(char*));



    int l;
    for (l=0;l<unique;l++)
        binStr[l]=getBin(storage[l]);

    for (l=0;l<unique;l++)
        printf("%c, %s\n",storage[l]->value,binStr[l]);

    return 0;
};

void initializePriorityQueue(int sizeOfQueue)
{
    length = sizeOfQueue;
    pq = malloc(sizeof(link)*sizeOfQueue);
};

void insertInPriorityQueue(link v)
{
    size++;
    link tempA = v;
    int i,j;
    for (i=0;i<size-1 && (tempA->freq)<(pq[i]->freq);i++);
    for (j=i;j<size;j++)
    {
        link tempB = pq[j];
        pq[j]=tempA;
        tempA=tempB;
    }
};

link getMaximumPriorityItem() {return pq[--size];};

char *getBin(link leaf)
{
    printf("leaf: %c\n",leaf->value);
    char *bin = malloc(BIN*sizeof(char));
    link runner = leaf;
    int i=1;
    bin[BIN-1]= '\0';
    while(runner->parent)
    {
        if (runner->parent->right == runner)
            bin[BIN-1-i] = '1';
        else
            bin[BIN-1-i] = '0';
        runner = runner->parent;
        i++;
    }
    strcpy(bin,bin+BIN-i);
    return bin;
};

