/*
*   Dakota Goldstein
*   File: unsorted.c
*   Lab 2
*   Description: The purpose of this lab is to create two files that create, add, remove, and search an unsorted and sorted array.
*   
*/


# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include "set.h"
# include <stdbool.h>
typedef struct set {
    char** a; //2D array that holds the strings 
    int elements; //Amount of elements in the array
    int maxElts; //Max amount of elements we can hold
}SET;

static int search(SET *sp, char *elt, bool *found)
{//Searches through the array of strings to find the string passed to by the parameters
    int i;
    found = false;
    for(i = 0; i < sp->elements; i++)
    {
        if(strcmp(elt, sp->a[i]) == 0) return i; //Compares the strings to see if the right one is found
    }
    return -1;
}

SET *createSet(int maxElts){//Creates an array of strings as well as a few attributes like length
    SET* sp;
    sp = malloc(sizeof(SET));
    assert(sp!=NULL);
    sp->a = malloc(sizeof(char*)*maxElts);
    sp->elements = 0;
    sp->maxElts = maxElts;
    assert(sp->a!= NULL);
    return sp;
}
    

int numElements(SET *sp){//Returns amount of elements in the array
    return sp->elements;

}
void destroySet(SET *sp){//Frees up all the memory being used in the array back to the computer
    int i;
    assert(sp != NULL);
    for(i = 0; i < sp->elements; i++){
        free(sp->a[i]);
    }
    free(sp->a);
    free(sp);
}
void addElement(SET *sp, char* elt){//Adds an element into the array and increments the number of elements. First checks if the element is already in the array
    bool *found = NULL;
    if(search(sp,elt,found) == -1){//Searches for the element, if false runs the condition below
        if(sp->elements == sp->maxElts)
        {
            printf("FULL");
			printf("%d",sp->elements); //test for falure cases
            return;
        }
        sp->a[sp->elements] = strdup(elt);
        sp->elements += 1;
		
    }
    return;


   
}
void removeElement(SET *sp, char *elt){//Removes an element from the array by searching for the element and clearing out the space. Decrements number of elements 
    assert(sp != NULL);
    assert(elt != NULL);
    bool found = NULL;
    int i = search(sp, elt, &found);
    if(i == -1)
        return; 
    sp->a[i] = sp->a[sp->elements-1];
    sp->a[sp->elements-1]=NULL;
    sp->elements -= 1;
    return;
    
}
char *findElement(SET *sp, char *elt){//Searches for an element and returns that element
    bool *found = NULL;
    int temp = search(sp, elt,found);
    if(temp != -1) return sp->a[temp];
    return NULL;
}
char **getElements(SET *sp){//Returns the array of strings by first making a copy of the array.
    int i;
    char** copy = malloc(sizeof(char*)*sp->maxElts); //Allocates memory to the copy
    for(i = 0; i<sp->elements; i++){//Copies each element into the copy
	   copy[i] = strdup(sp->a[i]);
    }
    return copy;

}
