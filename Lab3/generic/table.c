# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "set.h"
# include <stdbool.h>
# include <assert.h>



static int search(SET *sp, void *elt, bool *found);

//Set used to store all required data structures
typedef struct set {
    void** a; //2D array that holds the strings 
    int elements; //Amount of elements in the array
    int maxElts; //Max amount of elements we can hold
    char* flags;
    int (*compare)();
    unsigned (*hash)();
}SET;

//Function initializes sets and then sets all flags EMPTY
//Big-O: O(n)
SET *createSet(int maxElts,int (*compare)(), unsigned (*hash)()){//Creates an array of strings as well as a few attributes like length
    SET* sp;
    sp = malloc(sizeof(SET));
    assert(sp!=NULL);
    sp->a = malloc(sizeof(char*)*maxElts);
    sp->elements = 0;
    sp->maxElts = maxElts;
    sp->compare = compare;
    sp->hash = hash;
    assert(sp->a!= NULL);
    //printf("check here\n");
    sp->flags = malloc(sizeof(char)*maxElts);
    for(int i=0; i<maxElts; i++){
        sp->flags[i] = 'E';
    }
    //printf("check here\n");
    return sp;
}

//Function deletes sets by freeing from memory
//Big-O: O(1)
void destroySet(SET *sp)
{
	assert(sp != NULL);
	free(sp->a);
	free(sp->flags);
	free(sp);
	return;
}

//Function returns the number of elements
//Big-O: O(1)
int numElements(SET *sp)
{
    assert(sp != NULL);
	return (sp->elements);
}

//Function adds all elements into the void** data
//Big-O: O(n)
void addElement(SET *sp, void *elt)
{
	assert(sp != NULL && elt != NULL);
    if (sp->elements == sp->maxElts) return;
    bool found = false;
    int i = search(sp, elt, &found);
    if(found == true || i == -1) return;
    sp->a[i] = elt;
    sp->flags[i] = 'F';
    sp->elements++;
    return;
}

//Function finds and removes elt from table
//Big-O: O(n)
void removeElement(SET *sp, void *elt)
{
	assert(sp != NULL && elt != NULL);
    	bool found = false;
    	int i = search(sp, elt, &found);
    	if (found == true)
    	{
        	sp->a[i] = NULL;
        	sp->flags[i] = 'D';
        	sp->elements--;
    	}
    	return;
}

//Finds elt and returns
//Big-O: O(n)
void *findElement(SET *sp, void *elt)
{
	assert(sp != NULL && elt != NULL);
    bool found = NULL;
    int index = search(sp, elt, &found);
    if(found)return (sp->a[index]);
    return NULL;
}


//Big-O: O(n)
void *getElements(SET *sp){//Returns the array of strings by first making a copy of the array.
    assert(sp!= NULL);
    int i;
    void** copy = malloc(sizeof(void*)*sp->elements);
    assert(copy!=NULL); //Allocates memory to the copy
    int j = 0;
    for(i = 0; i<sp->maxElts; i++){//Copies each element into the copy
        if(sp->flags[i] == 'F'){
	        copy[j++] = sp->a[i];  
        }
    }
    return copy;

}
unsigned strhash(char *s)
{
	unsigned hash = 0;
    	while(*s != '\0')
        	hash = 31 * hash + *s ++;
    	return hash;
}
//Function uses hash function to search and return index
//Big-O: O(n)
static int search(SET *sp, void *elt, bool *found)
{
	assert(sp != NULL);
    assert(elt != NULL);
    int i;
    int pos;
    int first = -1;
    bool x = false;
    unsigned key = (*sp->hash)(elt);
    for(i = 0; i < sp->maxElts; i++)
	{
        pos = (key + i) % (sp->maxElts);
        if(sp->flags[pos] == 'F')
    	{
    		if((*sp->compare)(sp->a[pos],elt) == 0)
        	{
                *found = true;
                return pos;
            	}
        	}
        else if(sp->flags[pos] == 'D')
    	{
            if(x == false){
                first = pos;
                x=true;
            }
    	}
        else if(sp->flags[pos] == 'E')
    	{
        	if(first > -1)
        	{
            	return first;
        	}
    		return pos;
        }
    }
    return -1;
}