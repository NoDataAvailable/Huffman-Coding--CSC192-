typedef int Item;

extern void Pqinit(int); //construct a priority queue from N given items.
extern int Pqempty(); //empty the priority queue
extern void Pqinsert(Item); //insert a new item
extern Item Pqdelmax(); //delete the maximum item.

Item *pq;
int length, size;
