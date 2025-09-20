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
#define SIZE    2
static int THREAD_STACK_SIZE = 256 * 1024ULL * 1024ULL;
static int count = 0;
struct block {
    int size;
    int *first;
};
void merge_sort(struct block *my_data);
//Helper functions for mass amounts of data
static int write_all(int fd, const void *buffer, int n) {
    const char *p = (const char*)buffer;
    int done = 0;
    while (done < n) {
        size_t w = write(fd, p + done, n - done);
        if (w < 0) {
            if (errno == EINTR) continue;   //retry on flag
            return -1; //error
        }
        done += (int)w;
    }
    return done;
}
static int read_all(int fd, void *buffer, int n) {
    char *p = (char*)buffer;
    int done = 0;
    while (done < n) {
        size_t r = read(fd, p + done, n - done);
        if (r < 0) {
            if (errno == EINTR) continue;   //retry on flag
            return -1; //error
        }
        if (r == 0) exit(EXIT_FAILURE);
        done += (int)r;
    }
    return done;
}
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
    count = 0;
	if (argc < 2) {
		size = SIZE;
	} else {
		size = atol(argv[1]);
	}
    int *data = malloc(size * sizeof(int));
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
    int piping[2];
    pipe(piping);
    
    printf("starting---\n");
    print_block_data(&start_block);
    if (fork() == 0) {
        //Child

        close(piping[0]); 
        merge_sort(&rb);
        int needed = rb.size * sizeof(int);
        write(piping[1], rb.first, rb.size * sizeof(int));
        if (write_all(piping[1], rb.first, needed) != needed) {
            perror("write_all");
            exit(EXIT_FAILURE);
        }
        close(piping[1]);
        exit(0);
    }
    else {
        //Parent
        close(piping[1]);
        merge_sort(&lb);
        int needed = rb.size * sizeof(int);
        int got = read_all(piping[0], rb.first, needed);
        close(piping[0]);
        wait(NULL);
        if (got != needed) {
            fprintf(stderr, "short read: got %d of %d\n", got, needed);
            exit(EXIT_FAILURE);
        }
        merge(&lb, &rb);
    }

    
    
    
    
    
    print_block_data(&start_block);
    printf("---ending\n");
    printf(is_sorted(data, size) ? "sorted\n" : "not sorted\n");
    exit(EXIT_SUCCESS);
}