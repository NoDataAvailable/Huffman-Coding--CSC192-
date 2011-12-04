/*************************************
 Name:                  Huffman Coding
 Author:            Roberto Bortolussi
 Student Number:             998837022
 Course:                        CSC192
**************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void insertInPriorityQueue(link v);
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

    //printf("DEBUG 1\n");

    if (fp = fopen("inFile.txt","r"))//argv[1],"r"))
    {
        char ch;
        ch = fgetc(fp);
        while (!feof(fp))// && ch != '\n')
        {
            char *temp = inStr;
            strSize++;
            inStr = malloc((strSize+1)*sizeof(char));
            strcpy(inStr,temp);
            free(temp);
            //ch = fgetc(fp);
            inStr[strSize-1]=ch;
            inStr[strSize]='\0';
            freqs[ch]++;
            ch = fgetc(fp);
        };

    }
    else
    {
        printf("Could not open file!\n");
        exit(EXIT_FAILURE);
    }
    fclose(fp);

    initializePriorityQueue(N);

    //printf("DEBUG 2\n");

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
        };

    //printf("DEBUG 3\n");

    unique = size;
    storage = malloc(unique*sizeof(struct node));

    int k;
    for (k=0;k<unique;k++)
    {
        storage[k] = pq[k];//size;
    };

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

    //printf("DEBUG 4\n");

    binStr = malloc(N*sizeof(char*));

    int l;
    for (l=0;l<unique;l++)
        binStr[(int)storage[l]->value]=getBin(storage[l]);

    fp = fopen("outFile.txt","w");

    int r;
    for (r=2;r<N;r++)
        if (binStr[r]!=NULL)
        {
            printf("%2c : %3d : %15s\n", (char)r, freqs[r], binStr[r]);
            fprintf(fp,"%2c : %3d : %15s\n", (char)r, freqs[r], binStr[r]);
        };


    char *output;
    output = malloc(sizeof(char));
    output[0] = '\0';

    int s;
    for (s=0;s<strSize;s++)
    {
        char *temp, *addition;
        temp = output;
        addition = binStr[inStr[s]];
        int origSize = strlen(output);
        int addSize = strlen(addition);
        int newSize = origSize + addSize;
        output = malloc((newSize+1)*sizeof(char));
        strcpy(output,temp);
        strcpy(output+origSize, addition);
        output[newSize] = '\0';
        free(temp);
    };

    printf("\n");
    printf(inStr);
    printf("\n");
    printf(output);

    fprintf(fp,"\n");
    fprintf(fp,inStr);
    fprintf(fp,"\n");
    fprintf(fp,output);
    fclose(fp);

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

