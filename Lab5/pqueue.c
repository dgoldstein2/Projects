/*
Dakota Goldstein CSEN 12 LAB 5
pqueue.c
Due June 2nd
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "pqueue.h"

#define parent(x) (((x) - 1) / 2)
#define lC(x) ((x) * 2 + 1)
#define rC(x) ((x) * 2 + 2)

typedef struct pqueue{
    int count;
    int length;
    void** data;
    int (*compare)();
}PQ;
//Allocates and creates the queue to be used
//O(1)
PQ *createQueue(int(*compare)()){
    PQ *pq = malloc(sizeof(PQ));
    assert(pq != NULL);
    pq->compare = compare;
    pq->length = 10;
    pq->count = 0;
    pq->data = malloc(sizeof(void*)*pq->length);
    assert(pq->data != NULL);
    return pq;
}
//Destroys the queue to free up memory
//O(1)
void destroyQueue(PQ *pq){
    assert(pq != NULL);
    free(pq->data);
    free(pq);
}
//Returns the amount of items in the queue
//O(1)
int numEntries(PQ *pq){
    assert(pq != NULL);
    return pq->count;
}
//adds an item to the queue
//O(log n)
void addEntry(PQ *pq, void *entry){
    assert(pq != NULL && entry != NULL);
    if(pq->length == pq->count)
    {
        pq->length *= 2;
        pq->data = realloc(pq->data, sizeof(void *)*pq->length);
        assert(pq->data != NULL);	
    }
    int index = pq->count++; 
    while(index > 0 && (*pq->compare)(entry, pq->data[parent(index)]) < 0)
    {
       
        pq->data[index] = pq->data[parent(index)]; 
        
        index = parent(index);
    }
    
    pq->data[index] = entry;
}
//removes an item from the queue, the oldest item
//O(log n)
void *removeEntry(PQ *pq){
    assert(pq != NULL);
    void *first = pq->data[0];
    int index = 0;
    int small = 0;
    pq->data[index] = pq->data[pq->count - 1];
    pq->count--;
    while(lC(index) < pq->count)
    {
        small = lC(index);
        if(rC(index) < pq->count)
        {
            if(pq->compare(pq->data[lC(index)] , pq->data[rC(index)]) < 0) small = lC(index); 
            else small = rC(index); 
        }
        	if(pq->compare(pq->data[small],pq->data[index]) < 0)
            {
            	void *temp = pq->data[small]; 
            	pq->data[small] = pq->data[index];
            	pq->data[index] = temp; 
            	index = small; 
            }
            else break;
        
    } 
    return first; 

}