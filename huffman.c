/*************************************
 Name:                  Huffman Coding
 Author:            Roberto Bortolussi
 Student Number:             998837022
 Course:                        CSC192
**************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 257 // Number of possible ASCII values
#define BIN 15 // Max length alloted fot a binary string for a character

typedef struct node *link;

link *pq, *storage; // the priority queue (and its copy)
char **binStr; // Array that will contain all of the binary strings corresponding to chars
int length, size, unique; // Variables for tracking the priority queue and number of unique chars

struct node // tree node definition
{
    char value;
    int freq;
    link right;
    link left;
    link parent;
};

void initializePriorityQueue(int sizeOfQueue); // Priority queue functions (Array based)
void insertInPriorityQueue(link v);
link getMaximumPriorityItem();
char *getBin(link leaf); // Function to determine the binary representation of a char

int main(int argc, char * argv[])
{
    FILE *fp;
    int strSize = 0;
    char *inStr; // incoming string (stored to avoid re-reading)
    int freqs[N]; // frequencies of chars (char value used as indecies)

    int i;
    for (i=0;i<N;i++) freqs[i]=0; // initializes frequencies as 0

    inStr = malloc(sizeof(char)); // Ensures the incoming string exists and prevents errors if nothing is read
    inStr[0] = '\0';

    if ((fp = fopen(argv[1],"r"))) //ensures file is open (or else kills in the else statement)
    {
        char ch;
        ch = fgetc(fp); //initial read of ch is needed
        while (!feof(fp) && ch != '\n')
        {
            char *temp = inStr; // Needed for memory freeing
            strSize++;
            inStr = malloc((strSize+1)*sizeof(char)); // Dynamic string length required
            strcpy(inStr,temp);
            free(temp); // Prevent memory leaks
            inStr[strSize-1]=ch; 
            inStr[strSize]='\0'; // makes the array a string by adding the null char
            freqs[(int)ch]++; // increase the frequency of the read character
            ch = fgetc(fp);
        };

    }
    else
    {
        printf("Could not open file!\n");
        exit(EXIT_FAILURE);
    }
    fclose(fp); // Close the file

    initializePriorityQueue(N);

    int j;
    for (j=0;j<N;j++)
        if (freqs[j]) // Only make nodes for non-zero frequencies
        {
            link newNode;
            newNode = malloc(sizeof(struct node));
            newNode->value = (char)j;
            newNode->freq = freqs[j];
            newNode->left = NULL; // All char nodes are leaf nodes
            newNode->right = NULL;
            insertInPriorityQueue(newNode); //  All nodes sorted in priority queue
        };

    unique = size; // initial priority queue size must equal the number of unique chars

    storage = malloc(unique*sizeof(struct node)); // the priority queue is copied for future use 
    int k;
    for (k=0;k<unique;k++)
        storage[k] = pq[k];

    while (size!=0) // The tree is built in accordance with the assignment
    {
        if (size > 1)
        {
       	    link a,b;
            a = getMaximumPriorityItem();
            b = getMaximumPriorityItem();
            link n; // n is the parent of the two top priority items
            n = malloc(sizeof(struct node));
            n->freq = (a->freq+b->freq);
            n->value = (char)(n->freq);
            n->left = a;
            n->right = b;
            a->parent=b->parent=n;
            insertInPriorityQueue(n); // n put into the priority queue
        }
        else
        {
            getMaximumPriorityItem(); // Final node must be removed for some reason
        };
    };

    binStr = malloc(N*sizeof(char*)); // array of binary strings (index is a char)

    int l; // propogate the list of binary strings
    for (l=0;l<unique;l++)
        binStr[(int)storage[l]->value]=getBin(storage[l]);

    char *output; // starts propagating the output string
    output = malloc(sizeof(char));
    output[0] = '\0';

    int s; // The input string is parsed and for each  char, the appropriate binary string is added to the output
    for (s=0;s<strSize;s++)
    {
        char *temp, *addition;
        temp = output;
        addition = binStr[(int)inStr[s]];
        int origSize = strlen(output);
        int addSize = strlen(addition);
        int newSize = origSize + addSize;
        output = malloc((newSize+1)*sizeof(char)); // new, longer output is needed
        strcpy(output,temp);
        strcpy(output+origSize, addition); // concatinates the new string to output
        output[newSize] = '\0';
        free(temp);
    };

    printf(output);
    printf("\n");

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
    for (i=0; i<size-1 && (tempA->freq) < (pq[i]->freq); i++); // locates the appropriate insertion spot
    for (j=i; j<size; j++) // shifts all entries after the new item
    {
        link tempB = pq[j];
        pq[j]=tempA;
        tempA=tempB;
    }
};

link getMaximumPriorityItem() {return pq[--size];};

char *getBin(link leaf) // traces (backwards) the tree to determine the binary string
{
    char *bin = malloc(BIN*sizeof(char));
    link runner = leaf;
    int i=1;
    bin[BIN-1]= '\0';
    while(runner->parent) // Each bit is put at the beginning of the string as the function traces UP the tree
    {
        if (runner->parent->right == runner)
            bin[BIN-1-i] = '1';
        else
            bin[BIN-1-i] = '0';
        runner = runner->parent;
        i++;
    }
    strcpy(bin,bin+BIN-i); // shifts the beginning string to bin
    return bin;
};

