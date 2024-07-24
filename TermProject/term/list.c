# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include "list.h"



typedef struct node{
	void **array;   
    int front;
    int size;
    int count;  
    struct node *next;  
} NODE;
typedef struct list{
	int numElts;
    int arraySize;   
    NODE *head;
    NODE *tail;
} LIST;

// Creates complete list
// O(1)
LIST *createList(void)
{
	LIST *lp = malloc(sizeof(LIST));
    assert(lp != NULL);
    lp->head = NULL;
    lp->tail = NULL;
    lp->numElts = 0;
    lp->arraySize = 8;
	return lp;
}

// Destroys complete list
// O(n)
void destroyList(LIST *lp)
{
    assert(lp!=NULL);
    NODE *pDel = lp->head;
    while (pDel != NULL)
    {
        NODE *pCur = pDel->next;
        free(pDel->array);
        free(pDel);
        pDel = pCur;
    }
    free(lp);
}

//Returns number of items
// O(1)
int numItems(LIST *lp)
{
	assert(lp != NULL);
    return (lp->numElts);
}

//Adds item to front of list
// O(1)
void addFirst(LIST *lp, void *item) {
    if (lp->head == NULL || lp->head->count == lp->head->size) {
        NODE *temp = malloc(sizeof(NODE));
        assert(temp != NULL);
        temp->front = 0;
        temp->count = 0;
        temp->size = lp->arraySize;
        temp->array = malloc(sizeof(void*)*temp->size);
        assert(temp->array != NULL);
        temp->next = lp->head;
        lp->head = temp;
        if (lp->tail == NULL) lp->tail = temp;
    }
    lp->head->front = (lp->head->front - 1 + lp->arraySize) % lp->arraySize;
    lp->head->array[lp->head->front] = item;
    lp->head->count++;
    lp->numElts++;
    
}


//Adds item to end of list
// O(1)
void addLast(LIST *lp, void *item)
{
	assert(lp != NULL && item != NULL);
    if (lp->tail == NULL || lp->tail->count == lp->tail->size)
    {
	    NODE *temp = (NODE*)malloc(sizeof(NODE));
        assert(temp != NULL);
        temp->array = (void**)malloc(sizeof(void*)*lp->arraySize);
        assert(temp->array != NULL);
        temp->front = 0;
        temp->count = 0;
        temp->size = lp->arraySize;
        temp->next = NULL;
        if (lp->tail != NULL) lp->tail->next = temp;
        lp->tail = temp;
        if (lp->head == NULL) lp->head = temp;
    }
    int last = (lp->tail->front + lp->tail->count) % lp->arraySize;
    lp->tail->array[last] = item;
    lp->tail->count++;
    lp->numElts++;
    
}
    


//Removes last elt
// O(1)
void *removeFirst(LIST *lp){
    assert(lp!=NULL);
    if (lp->head == NULL) return NULL;
    void *item = lp->head->array[lp->head->front];
    lp->head->front = (lp->head->front + 1) % lp->arraySize;
    lp->head->count--;
    lp->numElts--;
    if (lp->head->count == 0) {
        NODE *oldTail = lp->head;
        lp->head = lp->head->next;
        if (lp->head == NULL) lp->tail = NULL;
        free(oldTail->array);
        free(oldTail);
    }

    return item;
}
//Removes last elt
// O(1)
void *removeLast(LIST *lp)
{
	assert(lp != NULL); 
    if (lp->tail == NULL) return NULL; 
    int last = (lp->tail->front + lp->tail->count - 1) % lp->arraySize;
    void *item = lp->tail->array[last];
    lp->tail->count--;
    lp->numElts--;
    if (lp->tail->count == 0){
	    NODE *pDel = lp->tail;
        assert(pDel != NULL);
        if(lp->head == lp->tail) lp->head = lp->tail = NULL;
	else{
        NODE *pCur = lp->head;
        while (pCur->next != lp->tail) pCur = pCur->next;
        pCur->next = NULL;
        lp->tail = pCur;
    }
    free(pDel->array);
	free(pDel);
    }
	
	return item; 
}
//returns the index of the item being inputted
//O(logn)
void *getItem(LIST *lp, int index){
    if (index < 0 || index >= lp->numElts) return NULL;
    NODE *current = lp->head;
    while (index >= current->count) {
        index -= current->count;
        current = current->next;
    }
    return current->array[(current->front + index) % current->size];
}
//O(logn)
//sets a certain item
void setItem(LIST *lp, int index, void *item){
    if (index < 0 || index >= lp->numElts) return;
    NODE *current = lp->head;
    while (index >= current->count) {
        index -= current->count;
        current = current->next;
    }
    current->array[(current->front + index) % current->size] = item;
}



