#include "PQueue.h"
#include <stdio.h>
#include <stdlib.h>

void Pqinit(int maxSize)
{
    length = size;
    pq = malloc(sizeof(int)*maxSize);
};

int Pqempty() {size = 0;};

void Pqinsert(Item new)
{
    size++;
    Item tempA = new;
    int i,j;
    for (i=0;i<size-1 && tempA>pq[i];i++);
    for (j=i;j<size;j++)
    {
        Item tempB = pq[j];
        pq[j]=tempA;
        tempA=tempB;
    }
};

Item Pqdelmax() {return pq[--size];};

int main()
{
    Pqinit(7); //construct a priority queue from N given items.
    Pqempty(); //empty the priority queue
    Pqinsert(5); //insert a new item
    Pqinsert(2);
    Pqinsert(7);
    Pqinsert(8);
    Pqinsert(1);
    int i;
    for (i=0; i<4;i++)
       printf("%d\n",Pqdelmax());
    free(pq);
    pq = NULL;
}
