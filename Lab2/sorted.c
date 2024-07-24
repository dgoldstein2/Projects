/*
*   Dakota Goldstein
*   File: sorted.c
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

SET *createSet(int maxElts){//Creates an array of strings as well as a few attributes like length
    SET* sp;
    sp = malloc(sizeof(SET)); // Allocates memory for the 2d array
    assert(sp!=NULL);
    sp->a = malloc(sizeof(char*)*maxElts); //Allocates memory for each value in the array 
    sp->elements = 0;
    sp->maxElts = maxElts;
    assert(sp->a!= NULL);
    return sp;
}
static int binsearch(SET *sp, char *elt, bool *found)
{ //Does a binary search to find a certain element
    assert(sp != NULL);
    int mid;
    int low = 0;
    int high = sp->elements -1;
    int answer;
    while(low <= high)
    {
        mid = ((high + low) / 2);
        answer = strcmp(sp->a[mid],elt);
        if(answer > 0) high = mid - 1;
        else if(answer < 0) low = mid + 1;
        else
        {
            *found = true;
            return mid;
        }
    }
    *found = false;
    return low;
}

    

int numElements(SET *sp){
    return sp->elements; //Returns amount of elements in the array

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
// bigO runtime: O(n)
void addElement(SET *sp, char* elt){//Adds an element into the list by first looking if it is already in the array.
    assert(sp != NULL);
    int i;
	bool found;
    
    int index = binsearch(sp, elt, &found);
    
    if(found == true) return; 
    
    if(sp->elements == sp->maxElts) //Checks to see if the array is full
    {
        printf("FULL");
        return;
    }
    
    for(i = sp->elements; i > index; i--) //shifts all elements in the array over by 1
    {
        sp->a[i] = sp->a[i-1];
    }
    
    sp->a[index] = strdup(elt); //adds the string into the array
    
    sp->elements += 1;
    return;
  
}
// bigO runtime: O(n)
void removeElement(SET *sp, char *elt){//Removes an element from a list
    assert(sp != NULL);
    bool found;
    int i;
    int index = binsearch(sp, elt, &found);
    if(found == false) return;
    for(i = index + 1; i < sp->elements; i++)
    {
    	sp->a[i-1] = sp->a[i];
    }
    sp->elements -= 1;
    	
    return;
    
}
char *findElement(SET *sp, char *elt){//Uses the Search function to find an element in the list. 
    bool found = false;
    int temp = binsearch(sp, elt, &found);
    found ? sp->a[temp] : NULL;
}
char **getElements(SET *sp){//Returns the array of strings by first making a copy of the array. See unsorted.c for specific comments per code
    int i;
    char** copy = malloc(sizeof(char*)*sp->maxElts);
    for(i = 0; i<sp->elements; i++){
	   copy[i] = strdup(sp->a[i]);
    }
    return copy;

}
