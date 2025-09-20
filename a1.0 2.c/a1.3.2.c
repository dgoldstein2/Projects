/*
    The Merge Sort to use for Operating Systems Assignment 1

    Modified by: Tim Gunn
    UPI: tgun744

    By submitting a program you are claiming that you and only you have made
    adjustments and additions to this code.
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h>
#include <sys/resource.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/sysinfo.h>

#define SIZE    2
#define THREAD_STACK_SIZE (1024*1024*16)

// Coutner of how many threads we have currnetly. 
int thread_counter = 0; 
// Max limit of threads 
int thread_limit = 1; 
// Thread Lock
pthread_mutex_t thread_lock; 


struct block {
    int size;
    int *first;
};

void print_block_data(struct block *blk) {
    printf("size: %d address: %p\n", blk->size, blk->first);
 }

/* Combine the two halves back together. */
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


void merge_sort(struct block *my_data) {
    if (my_data->size > 1) {
        struct block left = { my_data->size / 2, my_data->first };
        struct block right = { my_data->size - left.size, my_data->first + left.size };
        merge_sort(&left);
        merge_sort(&right);
        merge(&left, &right);
    }
}

// Sorting within the thread as well as decrementing the availble amount of threads using mutex locks. 
void *thread_sort(void *arg) {
    struct block *blk = (struct block *)arg;
    merge_sort(blk);
    pthread_mutex_lock(&thread_lock);
    thread_counter--;
    pthread_mutex_unlock(&thread_lock);

    return NULL;
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

     int *data = malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) { 
        data[i] = rand(); } 

    // Initialising the thread lock
    pthread_mutex_init(&thread_lock, NULL);
    thread_limit = get_nprocs_conf();

    printf("starting---\n");

struct block *blocks = malloc(thread_limit * sizeof(struct block));
    int base = size / thread_limit;
    int extra = size % thread_limit;
    int offset = 0;

    for (int i = 0; i < thread_limit; i++) {
        int chunk_size = base + (i < extra ? 1 : 0);
        blocks[i].size = chunk_size;
        blocks[i].first = data + offset;
        offset += chunk_size;
    }

    // Create the ammount of threads up to the thread limit and then thread_Sort each 
    pthread_t *threads = malloc(thread_limit * sizeof(pthread_t));

    for (int i = 0; i < thread_limit; i++) {
        pthread_mutex_lock(&thread_lock);
        thread_counter++;
        pthread_mutex_unlock(&thread_lock);

        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setstacksize(&attr, THREAD_STACK_SIZE);
        pthread_create(&threads[i], &attr, thread_sort, &blocks[i]);
        pthread_attr_destroy(&attr);
    }

    // Wait for all threads
    for (int i = 0; i < thread_limit; i++) {
        pthread_join(threads[i], NULL);
    }

    // Sequential merging stage
    int active_blocks = thread_limit;
    while (active_blocks > 1) {
    for (int i = 0; i < active_blocks / 2; i++) {
        merge(&blocks[2*i], &blocks[2*i+1]);
        blocks[i].first = blocks[2*i].first;
        blocks[i].size  = blocks[2*i].size + blocks[2*i+1].size;
    } if (active_blocks % 2 == 1) {
        blocks[active_blocks/2] = blocks[active_blocks-1];
        active_blocks = active_blocks/2 + 1;
    } else {
        active_blocks /= 2;
    }
}
    printf("---ending\n");
    printf(is_sorted(data, size) ? "sorted\n" : "not sorted\n");
    free(data);
    free(blocks);
    free(threads);
    exit(EXIT_SUCCESS);
}
