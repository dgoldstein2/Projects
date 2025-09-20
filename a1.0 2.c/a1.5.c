/*
    The Merge Sort to use for Operating Systems Assignment 1

    Modified by: Dakota Goldstein
    UPI: dgol720

    By submitting a program you are claiming that you and only you have made
    adjustments and additions to this code.
 */
#define _GNU_SOURCE
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h>
#include <sys/resource.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/types.h>
#define SIZE    2
static int THREAD_STACK_SIZE = 256 * 1024ULL * 1024ULL;
struct block {
    int size;
    int *first;
};
void merge_sort(struct block *my_data);
void print_block_data(struct block *blk) {
     printf("size: %d address: %p\n", blk->size, blk->first);
}

struct sort_task {
    struct block b;
    int depth;
};

/* Combine the two halves back together. */
//Added comments for better understanding while figuring out threads
void merge(struct block *left, struct block *right) {
	int *combined = malloc((left->size + right->size) * sizeof(int));
	int dest = 0, l = 0, r = 0;
	while (l < left->size && r < right->size) {
		if (left->first[l] < right->first[r])
			combined[dest++] = left->first[l++];
		else
			combined[dest++] = right->first[r++];
	}
	while (l < left->size)
		combined[dest++] = left->first[l++];
	while (r < right->size)
		combined[dest++] = right->first[r++];
    memmove(left->first, combined, (left->size + right->size) * sizeof(int));
    free(combined);
}


/* Merge sort the data. */
void merge_sort(struct block *my_data) {
    
    if (my_data->size > 1) {
        struct block lb;
        struct block rb;
        lb.size = my_data->size / 2;
        lb.first = my_data->first;
        rb.size = lb.size + (my_data->size % 2);
        rb.first = my_data->first + lb.size;
        merge_sort(&lb);
        merge_sort(&rb);
        merge(&lb, &rb);
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
    int *data = mmap(NULL, size*sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    struct block lb;
    struct block rb;
    lb.size = size / 2;
    lb.first = data;
    rb.size = lb.size + (size % 2);
    rb.first = data + lb.size;
    struct rlimit rl;
    getrlimit(RLIMIT_STACK, &rl);
    rl.rlim_cur = rl.rlim_max;
    setrlimit(RLIMIT_STACK, &rl);
    struct block start_block;
    start_block.size = size;
    start_block.first = data;
    for (int i = 0; i < size; i++) {
        data[i] = rand();
    }
    
    printf("starting---\n");
    print_block_data(&start_block);
    if (fork() == 0) {
        // Child
        merge_sort(&rb);
        exit(0);
    }
    else {
        // Parent
        merge_sort(&lb);
        wait(NULL);
        merge(&lb, &rb);
    }

    
    
    
    
    
    print_block_data(&start_block);
    printf("---ending\n");
    printf(is_sorted(data, size) ? "sorted\n" : "not sorted\n");
    munmap(data, size*sizeof(int));
    exit(EXIT_SUCCESS);
}