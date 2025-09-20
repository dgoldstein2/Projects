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

#define SIZE    2
static int THREAD_STACK_SIZE = 256 * 1024ULL * 1024ULL;
static int count = 0;
struct block {
    int size;
    int *first;
};
void merge_sort(struct block *my_data, int depth);
void print_block_data(struct block *blk) {
     printf("size: %d address: %p\n", blk->size, blk->first);
}

struct sort_task {
    struct block b;
    int depth;
};
static pthread_attr_t attr;
void* thread_entry(void *vp) {
    struct sort_task *t = (struct sort_task*)vp; //Casting 
    merge_sort(&t->b, &t->depth);
    free(t);
    return NULL;
}
//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
/* Combine the two halves back together. */
//Added comments for better understanding while figuring out threads
void merge(struct block *left, struct block *right) {
	int combined[left->size + right->size];
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
}


/* Merge sort the data. */
void merge_sort(struct block *my_data, int depth) {
    //print_block_data(my_data);
    struct block lb; 
    struct block rb;
    lb.size = my_data->size / 2;
    lb.first = my_data->first;
    rb.size = lb.size + (my_data->size % 2);
    rb.first = my_data->first + lb.size;
    if (my_data->size <= 1) return;
    if (depth > 1) {
        pthread_t lt, rt;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setstacksize(&attr, THREAD_STACK_SIZE);
        int left_threads = my_data->size/2;
        int right_threads = my_data->size - left_threads;
        struct sort_task *left_task = malloc(sizeof *left_task);
        struct sort_task *right_task = malloc(sizeof *right_task);
        left_task->b = lb;
        right_task->b = rb;
        left_task->depth = left_threads;
        right_task->depth = right_threads;
        pthread_create(&lt,&attr,thread_entry,left_task);
        pthread_create(&rt,&attr,thread_entry,right_task);
        pthread_join(lt, NULL);
        pthread_join(rt, NULL);
        
    }
    else{
        merge_sort(&lb, 1);
        merge_sort(&rb, 1);
    }
    merge(&lb, &rb);
      
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
    count = 0;
	if (argc < 2) {
		size = SIZE;
	} else {
		size = atol(argv[1]);
	}
    
    struct rlimit rl;
    getrlimit(RLIMIT_STACK, &rl);
    rl.rlim_cur = rl.rlim_max;
    setrlimit(RLIMIT_STACK, &rl);
    struct block start_block;
    int data[size];
    start_block.size = size;
    start_block.first = data;
    for (int i = 0; i < size; i++) {
        data[i] = rand();
    }
    print_block_data(&start_block);
    printf("starting---\n");
    merge_sort(&start_block, 2);
    print_block_data(&start_block);
    printf("---ending\n");
    printf(is_sorted(data, size) ? "sorted\n" : "not sorted\n");
    exit(EXIT_SUCCESS);
}