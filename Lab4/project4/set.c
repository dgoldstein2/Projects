# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <string.h> 
# include "set.h"
# include "list.h"
# include "list.c"

//defines the set structure
//0(1)
typedef struct set 
{
	int length;
    int count;
    int (*compare)();
    unsigned (*hash)();
    LIST **lists; 
} SET;

//Creates full set
// O(n)
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)())
{    
	int i;
	SET *sp;    
	assert(compare != NULL && hash != NULL);    
	sp = malloc(sizeof(SET));    
	assert(sp != NULL); 
	sp->compare = compare;    
	sp->hash = hash;    
	sp->count = 0;
    sp->length = maxElts / 20;
	sp->lists = malloc(sizeof(LIST*)*sp->length);
    assert(sp->lists != NULL);
	for(i = 0; i < sp->length; i++) sp->lists[i] = createList(compare);
	return sp;
}

//Destroys full set
// O(1)
void destroySet(SET *sp)
{
	assert(sp != NULL);
    free(sp->lists);
    free(sp);
}

//returns the number of elements in the set
// O(1)
int numElements(SET *sp)
{
	assert(sp != NULL);
    return sp->count;
}

//Adds an element into the set
// O(n)
void addElement(SET *sp, void *elt)
{
	assert(sp != NULL && elt != NULL);
    int index = (*sp->hash)(elt) % sp->length;
	if(findItem(sp->lists[index],elt) == NULL)
    {
        addFirst(sp->lists[index],elt);
        sp->count++;
    }
}

//Removes elt from the set
// O(n)

void removeElement(SET *sp, void *elt)
{
	assert(sp != NULL && elt != NULL);
    int index = (*sp->hash)(elt)%sp->length;
    
    if(findItem(sp->lists[index],elt) == NULL) return;
    if(findItem(sp->lists[index],elt) != NULL && sp->count>0)
    {
        
        removeItem(sp->lists[index], elt);
        
        sp->count--;
    }
}


//Finds an element in the set
// O(n)
void *findElement(SET *sp, void *elt)
{
	assert(sp != NULL && elt != NULL);
	int index = (*sp->hash)(elt) % sp->length;
    return findItem(sp->lists[index], elt); 
}

//Returns the contents of the set
//O(n^2)
void *getElements(SET *sp)
{
	assert(sp != NULL);
    void **dest = malloc(sizeof(void*)*sp->count);
    int i,j;
    j=0;
    int h = 0;
    printf("check beginning\n");
    for(int x=0;x<sp->count;x++){
        dest[x] = malloc(sizeof(void*));
        assert(dest[x] != NULL);
    }
    for(i = 0; i < sp->length; i++)
    	{
            void **end = getItems(sp->lists[i]);
        	int num = numItems(sp->lists[i]);
            
        	for(j=0;j<num;j++)
        	{
                	memcpy(&dest[h],&end[j],sizeof(void*));
                    h++;
                    
            	
        	}
    	}
        return dest;
    
}