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
static int max_threads = 1;
static int active_threads = 0;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
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
static pthread_attr_t attr;
void* thread_entry(void *vp) {
    struct sort_task *t = (struct sort_task*)vp; //Casting 
    merge_sort(&t->b);
    pthread_mutex_lock(&mutex);
    active_threads--;
    pthread_mutex_unlock(&mutex);
    return NULL;
}

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
    //print_block_data(my_data);
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
    /*
    
    
    int spawned = 0;
    pthread_mutex_lock(&mutex);
    if(active_threads<max_threads-1){
        active_threads++;
        spawned =1;
    }
    pthread_mutex_unlock(&mutex);
    if (my_data->size <= 1) return;
    if (spawned) {
        pthread_t lt, rt;
        pthread_t th[max_threads];
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setstacksize(&attr, THREAD_STACK_SIZE);
        int left_threads = my_data->size/2;
        int right_threads = my_data->size - left_threads;
        struct sort_task *task = malloc(sizeof *task);

        for(int i = 0;i<max_threads;i++){
            task->b = blocks[i];
            task->depth = blocks[i].size;
            pthread_create(&th[i],&attr,thread_entry,task);
        }
        for(int i = 0;i<max_threads;i++){
            pthread_join(th[i], NULL);
        }
        
    }
    else{
        for(int i = 0;i<max_threads){
            merge_sort(&lb, 1);
            merge_sort(&rb, 1);
        }
    }
    merge(&lb, &rb);
    pthread_mutex_destroy(&mutex);
    */
      
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
    long cores = sysconf(_SC_NPROCESSORS_ONLN);
    if (cores < 1) cores = 1;
    max_threads = (int)cores;
    
    int *data = malloc(size * sizeof(int));
    /*
    struct rlimit rl;
    getrlimit(RLIMIT_STACK, &rl);
    rl.rlim_cur = rl.rlim_max;
    setrlimit(RLIMIT_STACK, &rl);
    */
    struct block start_block;
    start_block.size = size;
    start_block.first = data;
    for (int i = 0; i < size; i++) {
        data[i] = rand();
    }
    struct block *blocks = malloc(max_threads * sizeof(struct block));
    int data_per = size / max_threads;
    int data_offset = size % max_threads;
    int extra = 0;
    print_block_data(&start_block);
    printf("starting---\n");
    for (int i = 0; i < max_threads; i++) {
        int chunk = data_per + (i < data_offset ? 1 : 0);
        blocks[i].size = chunk;
        blocks[i].first = data + extra;
        extra = extra + chunk;
    }

    // Create the ammount of threads up to the thread limit and then thread_Sort each 
    pthread_t *threads = malloc(max_threads * sizeof(pthread_t));

    for (int i = 0; i < max_threads; i++) {
        pthread_mutex_lock(&mutex);
        active_threads++;
        pthread_mutex_unlock(&mutex);

        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setstacksize(&attr, THREAD_STACK_SIZE);
        pthread_create(&threads[i], &attr, thread_entry, &blocks[i]);
        pthread_attr_destroy(&attr);
    }

    // Wait for all threads
    for (int i = 0; i < max_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Sequential merging stage
    int blocks_in_use = max_threads;
    while (blocks_in_use > 1) {
    for (int i = 0; i < blocks_in_use / 2; i++) {
        merge(&blocks[2*i], &blocks[2*i+1]);
        blocks[i].first = blocks[2*i].first;
        blocks[i].size  = blocks[2*i].size + blocks[2*i+1].size;
    } if (blocks_in_use % 2 == 1) {
        blocks[blocks_in_use/2] = blocks[blocks_in_use--];
        blocks_in_use = blocks_in_use / 2 + 1;
    } else {
        blocks_in_use = blocks_in_use / 2;
    }
}
    fprintf(stdout, "Cores detected: %ld\n", cores);
    printf("Threads: %d\n", max_threads);
    
    
    print_block_data(&start_block);
    printf("---ending\n");
    printf(is_sorted(data, size) ? "sorted\n" : "not sorted\n");
    free(data);
    free(blocks);
    free(threads);
    exit(EXIT_SUCCESS);
}