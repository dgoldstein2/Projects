/*
    The Merge Sort to use for Operating Systems Assignment 1

    Modified by: Dakota Goldstein
    UPI: dgol720

    By submitting a program you are claiming that you and only you have made
    adjustments and additions to this code.
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h>
#include <sys/resource.h>
#include <stdbool.h>

#define SIZE    2

struct block {
    int size;
    int *first;
};

void print_block_data(struct block *blk) {
     printf("size: %d address: %p\n", blk->size, blk->first);
 }

/* Combine the two halves back together. */
//Added comments for better understanding while figuring out threads
void merge(struct block *left, struct block *right) {
	int combined[left->size + right->size]; //Set combined size
	int dest = 0, l = 0, r = 0; //initial values
	while (l < left->size && r < right->size) { // while loop for each value in each block
		if (left->first[l] < right->first[r]) // checksfirst  left value and right value
			combined[dest++] = left->first[l++]; // if left first is smaller puts as first in combines
		else
			combined[dest++] = right->first[r++]; //else puts right first value
	}
	while (l < left->size) // if one of the sides finishes it fills the rest
		combined[dest++] = left->first[l++];
	while (r < right->size)
		combined[dest++] = right->first[r++];
    memmove(left->first, combined, (left->size + right->size) * sizeof(int)); //maps the values
}

/* Merge sort the data. */
void merge_sort(struct block *my_data) {
    //print_block_data(my_data);
    if (my_data->size > 1) {
        struct block left_block; 
        struct block right_block;
        left_block.size = my_data->size / 2; //sets left block size
        //printf("left blocksize: %d\n",left_block.size);
        left_block.first = my_data->first; //sets right block first value as data value
        //printf("left block first: %d\n",*left_block.first);
        right_block.size = left_block.size + (my_data->size % 2); //sets right size as left size + either 1 or 0
        //printf("right blocksize: %d\n",right_block.size);
        right_block.first = my_data->first + left_block.size; //sets the right value address as my_data address offsetted by the left size
        //printf("right block first: %d\n",*right_block.first);
        merge_sort(&left_block);
        merge_sort(&right_block);
        merge(&left_block, &right_block);
    }
}

/* Check to see if the data is sorted. */
bool is_sorted(int data[], int size) {
    bool sorted = true;
    for (int i = 0; i < size - 1; i++) {
        if (data[i] > data[i + 1])
            sorted = false;
    }
    return sorted;
}

int main(int argc, char *argv[]) {
	long size;

	if (argc < 2) {
		size = SIZE;
	} else {
		size = atol(argv[1]);
	}
    struct block start_block;
    struct rlimit rl;
    getrlimit(RLIMIT_STACK, &rl);
    rl.rlim_cur = rl.rlim_max;
    setrlimit(RLIMIT_STACK, &rl);
    int data[size];
    start_block.size = size;
    start_block.first = data;
    for (int i = 0; i < size; i++) {
        data[i] = rand();
    }
    print_block_data(&start_block);
    printf("starting---\n");
    merge_sort(&start_block);
    print_block_data(&start_block);
    printf("---ending\n");
    printf(is_sorted(data, size) ? "sorted\n" : "not sorted\n");
    exit(EXIT_SUCCESS);
}