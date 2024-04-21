#include "hmm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

extern block_t *firstBlock;
void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
void merge_test();
void alloc_in_middle();
void dec_progbreak();
void access_data();
int main() {
    
}


/**
 * @brief run this function to test allocating multiple blocks and freeing some contigous block
 *        and see if they merge and also free seperated blocks
 * 
 */
void merge_test()
{
    void *temp1 = HmmAlloc(60);
    void *temp2 = HmmAlloc(212);
    void *temp3 = HmmAlloc(22);
    void *temp4 = HmmAlloc(151);
    void *temp5 = HmmAlloc(92);
    void *temp6 = HmmAlloc(52);
    void *temp7 = HmmAlloc(48);

    printf("current\t\t\tnext\t\tprev\t\tsize\t\tstatus\n");
    block_t *curr = firstBlock;
    while (NULL != curr) {
	printf("%10p    %10p    %10p    %10li    %10i\n", curr, curr->next,
	       curr->prev, curr->size, curr->status);
	curr = curr->next;
    }
    printf("\n");
    HmmFree(temp7);
    curr = firstBlock;
    while (NULL != curr) {
	printf("%10p    %10p    %10p    %10li    %10i\n", curr, curr->next,
	       curr->prev, curr->size, curr->status);
	curr = curr->next;
    }
    printf("\n");
    HmmFree(temp6);
    curr = firstBlock;
    while (NULL != curr) {
	printf("%10p    %10p    %10p    %10li    %10i\n", curr, curr->next,
	       curr->prev, curr->size, curr->status);
	curr = curr->next;
    }
    printf("\n");
    HmmFree(temp3);

    curr = firstBlock;
    while (NULL != curr) {
	printf("%10p    %10p    %10p    %10li    %10i\n", curr, curr->next,
	       curr->prev, curr->size, curr->status);
	curr = curr->next;
    }
}

/**
 * @brief test allocating in a free block to test splitting
 * 
 */
void alloc_in_middle()
{
    void *temp1 = HmmAlloc(60);
    void *temp2 = HmmAlloc(212);
    void *temp3 = HmmAlloc(120);
    void *temp4 = HmmAlloc(151);
    void *temp5 = HmmAlloc(92);
    void *temp6 = HmmAlloc(52);
    void *temp7 = HmmAlloc(48);

    printf("current\t\t\tnext\t\tprev\t\tsize\t\tstatus\n");
    block_t *curr = firstBlock;
    while (NULL != curr) {
	printf("%10p    %10p    %10p    %10li    %10i\n", curr, curr->next,
	       curr->prev, curr->size, curr->status);
	curr = curr->next;
    }
    printf("\n");
    HmmFree(temp7);
    curr = firstBlock;
    while (NULL != curr) {
	printf("%10p    %10p    %10p    %10li    %10i\n", curr, curr->next,
	       curr->prev, curr->size, curr->status);
	curr = curr->next;
    }
    printf("\n");
    HmmFree(temp6);
    curr = firstBlock;
    while (NULL != curr) {
	printf("%10p    %10p    %10p    %10li    %10i\n", curr, curr->next,
	       curr->prev, curr->size, curr->status);
	curr = curr->next;
    }
    printf("\n");
    HmmFree(temp3);

    curr = firstBlock;
    while (NULL != curr) {
	printf("%10p    %10p    %10p    %10li    %10i\n", curr, curr->next,
	       curr->prev, curr->size, curr->status);
	curr = curr->next;
    }
    printf("\n");
    void *temp8 = HmmAlloc(10);
    curr = firstBlock;
    while (NULL != curr) {
	printf("%10p    %10p    %10p    %10li    %10i\n", curr, curr->next,
	       curr->prev, curr->size, curr->status);
	curr = curr->next;
    }
    printf("\n");
    void *temp9 = HmmAlloc(100);
    curr = firstBlock;
    while (NULL != curr) {
	printf("%10p    %10p    %10p    %10li    %10i\n", curr, curr->next,
	       curr->prev, curr->size, curr->status);
	curr = curr->next;
    }
    printf("\n");
}

/**
 * @brief test the decreasing of program break
 * 
 */
void dec_progbreak()
{
    long int *ptr6 = (long int *) malloc(50);
    long int *ptr1 = (long int *) malloc(100);
    long int *ptr2 = (long int *) malloc(27);
    long int *ptr3 = (long int *) malloc(600);
    long int *ptr4 = (long int *) malloc(97);
    long int *ptr5 = (long int *) malloc(72000);
    void *pb1 = sbrk(0);
    free(ptr6);
    free(ptr5);
    free(ptr4);
    free(ptr3);
    free(ptr2);
    free(ptr1);
    void *pb2 = sbrk(0);
    printf("program break decreased by %10ld\n", pb1 - pb2);
}

/**
 * @brief try to access data after successive allocation and after freeing 
 * 
 */
void access_data(){
        int *intArr = HmmAlloc(11 * sizeof(int));
    for (int i = 0; i < 11; i++) {
	intArr[i] = i;
    }
    char *charArr = HmmAlloc(20 * sizeof(char));
    for (int i = 0; i < 20; i++) {
	    charArr[i] = i + 11;
    }
    int *intArr2 = HmmAlloc(22 * sizeof(int));
    int *intArr3 = HmmAlloc(11 * sizeof(int));
    int *intArr4 = HmmAlloc(8 * sizeof(int));
    for (int i = 0; i < 22; i++) {
	    intArr2[i] = i + 31;
    }
    for (int i = 0; i < 11; i++) {
	    intArr3[i] = i + 53;
    }
    for (int i = 0; i < 8; i++) {
	    intArr4[i] = i + 64;
    }

    /*Printing values */
    for (int i = 0; i < 11; i++) {
    	printf("intArr[%d]= %d \n", i, intArr[i]);
    }
    printf("\n");
    for (int i = 0; i < 20; i++) {
	    printf("charArr[%d]= %d \n", i, charArr[i]);
    }
        printf("\n");
    for (int i = 0; i < 22; i++) {
	    printf("intArr2[%i]= %d \n", i, intArr2[i]);
    }
        printf("\n");
    for (int i = 0; i < 11; i++) {
	    printf("intArr3[%i]= %d \n", i, intArr3[i]);
    }
        printf("\n");
    for (int i = 0; i < 8; i++) {
	    printf("intArr4[%i]= %d \n", i, intArr4[i]);
    }
        printf("\n");
    HmmFree(intArr4);
    HmmFree(charArr);
    HmmFree(intArr2);
    HmmFree(intArr);
    printf("Accessing again after freeing\n");
    for (int i = 0; i < 11; i++) {
	    printf("intArr3[%i]= %d \n", i, intArr3[i]);
    }
}
void *malloc(size_t size)
{
    return HmmAlloc(size);
}

void free(void *ptr)
{
    HmmFree(ptr);
}

void *calloc(size_t nmemb, size_t size)
{
    return HmmCalloc(nmemb, size);
}

void *realloc(void *ptr, size_t size)
{
    return HmmRealloc(ptr, size);
}
