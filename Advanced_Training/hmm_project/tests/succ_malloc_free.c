#include <stdio.h>
#include "hmm.h"
#include <stdlib.h>

#define NUM_ALLOCS 100000
#define MAX_ALLOC_SIZE 1000
void * malloc(size_t size)
{
    return HmmAlloc(size);
}

void free(void *ptr)
{
    HmmFree(ptr);
}

void *calloc(size_t nmemb, size_t size)
{
	return HmmCalloc(nmemb,size);
}

void *realloc(void *ptr, size_t size)
{
	return HmmRealloc(ptr,size);
}
int main() {
    void* ptrs[NUM_ALLOCS] = {NULL};

    // Allocate memory
    for (int i = 0; i < NUM_ALLOCS; i++) {
        
        size_t size = rand() % MAX_ALLOC_SIZE + 1;
        ptrs[i] = malloc(size);
        printf("hello %i\n",i);
        if (ptrs[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            // Cleanup allocated memory before exiting
            for (int j = 0; j < i; j++) {
                free(ptrs[j]);
            }
            exit(EXIT_FAILURE);
        }
    }

    // Free memory
    for (int i = 0; i < NUM_ALLOCS; i++) {
        free(ptrs[i]);
    }

    printf("Allocations and deallocations completed successfully!\n");

    return 0;
}
