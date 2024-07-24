# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "set.h"
# include <stdbool.h>
# include <assert.h>


unsigned strhash(char *s);
static int search(SET *sp, char *elt, bool *found);
typedef struct set {
    char** a; //2D array that holds the strings 
    int elements; //Amount of elements in the array
    int maxElts; //Max amount of elements we can hold
    char* flags; //Flags for marking F for filled, E for empty, and D for deleted
    
}SET;
SET *createSet(int maxElts){//Creates an array of strings as well as a few attributes like length
    SET* sp;
    sp = malloc(sizeof(SET));
    assert(sp!=NULL);
    sp->a = malloc(sizeof(char*)*maxElts);
    sp->elements = 0;
    sp->maxElts = maxElts;
    assert(sp->a!= NULL);
    sp->flags = malloc(sizeof(char)*maxElts);
    for(int i=0; i<maxElts; i++){
        sp->flags[i] = 'E';
    }
    return sp;
}
//Big-O: O(1)
int numElements(SET *sp){//Returns amount of elements in the array
    return sp->elements;
}
//Big-O: O(n)
void destroySet(SET *sp){//Frees up all the memory being used in the array back to the computer
    int i;
    assert(sp != NULL);
    int start = 0;
    int end =  sp->maxElts -1;
    while(start <= end){
        if(sp->flags[start] == 'F') free(sp->a[start]);
        start++;
    }
    free(sp->flags);
    free(sp->a);
    free(sp);
}
//Big-O: O(n)
void addElement(SET *sp, char* elt){//Adds an element into the array and increments the number of elements. First checks if the element is already in the array
    bool found = false;
    int i = search(sp,elt,&found);//Searches for the element, if false runs the condition below
    if(found) return;
    if(sp->elements == sp->maxElts)
    {
        printf("FULL");
		printf("%d",sp->elements); //test for falure cases
        return;
    }
    if(sp->flags[i] == 'F'){
        printf("Copy");
        return;
    } 
    sp->a[i] = strdup(elt);
    sp->elements += 1;
    sp->flags[i] = 'F';
    return;
}
//Big-O: O(n)
void removeElement(SET *sp, char *elt){//Removes an element from the array by searching for the element and clearing out the space. Decrements number of elements 
    
    assert(sp != NULL);
    assert(elt != NULL);
    bool found = NULL;
    int i = search(sp, elt, &found);
    
    if(i == -1)
        return;
    if (found == true)
    {
        free(sp->a[i]);
        sp->flags[i] = 'D';
        sp->elements--;
    }
    return;
    
}
//Big-O: O(n)
char *findElement(SET *sp, char *elt){//Searches for an element and returns that element
    bool found = NULL;
    int temp = search(sp, elt,&found);
    if(found) return sp->a[temp];
    return NULL;
}
//Big-O: O(n)
char **getElements(SET *sp){//Returns the array of strings by first making a copy of the array.
    assert(sp!= NULL);
    int i;
    char** copy = malloc(sizeof(char*)*sp->elements);
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
static int search(SET *sp, char *elt, bool *found)
{
	assert(sp != NULL);
    assert(elt != NULL);
    int i;
    int pos;
    int first = -1;
    bool x = false;
    unsigned key = strhash(elt);
    for(i = 0; i < sp->maxElts; i++)
	{
        pos = (key + i) % (sp->maxElts);
        if(sp->flags[pos] == 'F')
    	{
    		if(strcmp(elt, sp->a[pos]) == 0)
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
    *found = false;
    return -1;
}