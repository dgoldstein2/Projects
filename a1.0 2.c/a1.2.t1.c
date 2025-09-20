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
#include <pthread.h>

#define SIZE    2

struct block {
    int size;
    int *first;
};
void* nothing(void* args, struct block *data){
    struct sort_task *temp = args;
    temp->b.size = data->size /2;

};
struct sort_task{
    struct block b;
};

void print_block_data(struct block *blk) {
     printf("size: %d address: %p\n", blk->size, blk->first);
 }

/* Combine the two halves back together. */
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
void merge_sort(struct block *my_data) {
    print_block_data(my_data);
    pthread_t p1, p2;
    pthread_attr_t attr1, attr2;
    int p1_S;
    if (my_data->size > 1) {
        pthread_attr_init(&attr1);
        pthread_attr_init(&attr2);
        struct block left_block;
        struct block right_block;
        if(pthread_create(&p1, &attr1, nothing(&left_block), NULL)) return 1;
        if(pthread_create(&p2, &attr2, nothing(&right_block), NULL)) return 2;
        if(pthread_join(&p1, NULL)) return 3;
        if(pthread_join(&p2, NULL)) return 4;
        pthread_attr_setstacksize(&attr1,my_data->size / 2); //left block
        pthread_attr_getstacksize(&attr1,&p1_S);
        //left_block.first = my_data->first;
        pthread_attr_setstacksize(&attr2, p1_S +(my_data->size % 2)); //right block
        //right_block.size = left_block.size + ;
        //right_block.first = my_data->first + left_block.size;
        merge_sort(&p1);
        merge_sort(&p2);
        merge(&p1, &p2);
        pthread_attr_destroy(&attr1);
        pthread_attr_destroy(&attr2);
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