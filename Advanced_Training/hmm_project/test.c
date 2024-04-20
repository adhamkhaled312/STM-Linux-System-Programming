#include "hmm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
extern block_t *firstBlock;
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
void merge_test();
void alloc_in_middle();
void dec_progbreak();
int main(){
}


/**
 * @brief run this function to test allocating multiple blocks and freeing some contigous block
 *        and see if they merge and also free seperated blocks
 * 
 */
void merge_test(){
    void*temp1=HmmAlloc(60);
    void*temp2=HmmAlloc(212);
    void*temp3=HmmAlloc(22);
    void*temp4=HmmAlloc(151);
    void*temp5=HmmAlloc(92);
    void*temp6=HmmAlloc(52);
    void*temp7=HmmAlloc(48);

    printf("current\t\t\tnext\t\tprev\t\tsize\t\tstatus\n");
    block_t *curr=firstBlock;
    while(NULL!=curr){
        printf("%10p    %10p    %10p    %10li    %10i\n",curr,curr->next,curr->prev,curr->size,curr->status);
        curr=curr->next;
    }
    printf("\n");
    HmmFree(temp7);
    curr=firstBlock;
    while(NULL!=curr){
        printf("%10p    %10p    %10p    %10li    %10i\n",curr,curr->next,curr->prev,curr->size,curr->status);
        curr=curr->next;
    }
    printf("\n");
    HmmFree(temp6);
    curr=firstBlock;
    while(NULL!=curr){
        printf("%10p    %10p    %10p    %10li    %10i\n",curr,curr->next,curr->prev,curr->size,curr->status);
        curr=curr->next;
    }
    printf("\n");
    HmmFree(temp3);

    curr=firstBlock;
    while(NULL!=curr){
        printf("%10p    %10p    %10p    %10li    %10i\n",curr,curr->next,curr->prev,curr->size,curr->status);
        curr=curr->next;
    }
}
/**
 * @brief test allocating in a free block to test splitting
 * 
 */
void alloc_in_middle(){
    void*temp1=HmmAlloc(60);
    void*temp2=HmmAlloc(212);
    void*temp3=HmmAlloc(120);
    void*temp4=HmmAlloc(151);
    void*temp5=HmmAlloc(92);
    void*temp6=HmmAlloc(52);
    void*temp7=HmmAlloc(48);

    printf("current\t\t\tnext\t\tprev\t\tsize\t\tstatus\n");
    block_t *curr=firstBlock;
    while(NULL!=curr){
        printf("%10p    %10p    %10p    %10li    %10i\n",curr,curr->next,curr->prev,curr->size,curr->status);
        curr=curr->next;
    }
    printf("\n");
    HmmFree(temp7);
    curr=firstBlock;
    while(NULL!=curr){
        printf("%10p    %10p    %10p    %10li    %10i\n",curr,curr->next,curr->prev,curr->size,curr->status);
        curr=curr->next;
    }
    printf("\n");
    HmmFree(temp6);
    curr=firstBlock;
    while(NULL!=curr){
        printf("%10p    %10p    %10p    %10li    %10i\n",curr,curr->next,curr->prev,curr->size,curr->status);
        curr=curr->next;
    }
    printf("\n");
    HmmFree(temp3);

    curr=firstBlock;
    while(NULL!=curr){
        printf("%10p    %10p    %10p    %10li    %10i\n",curr,curr->next,curr->prev,curr->size,curr->status);
        curr=curr->next;
    }
    printf("\n");
    void *temp8=HmmAlloc(10);
    curr=firstBlock;
    while(NULL!=curr){
        printf("%10p    %10p    %10p    %10li    %10i\n",curr,curr->next,curr->prev,curr->size,curr->status);
        curr=curr->next;
    }
    printf("\n");
    void *temp9=HmmAlloc(100);
    curr=firstBlock;
    while(NULL!=curr){
        printf("%10p    %10p    %10p    %10li    %10i\n",curr,curr->next,curr->prev,curr->size,curr->status);
        curr=curr->next;
    }
    printf("\n");
}
/**
 * @brief test the decreasing of program break
 * 
 */
void dec_progbreak(){
    long int *ptr6=(long int*)malloc(50);
    long int *ptr1=(long int*)malloc(100);
    long int *ptr2=(long int*)malloc(27);
    long int *ptr3=(long int*)malloc(600);
    long int *ptr4=(long int*)malloc(97);
    long int *ptr5=(long int*)malloc(72000);
    void* pb1=sbrk(0);
    free(ptr6);
    free(ptr5);
    free(ptr4);
    free(ptr3);
    free(ptr2);
    free(ptr1);
    void *pb2=sbrk(0);
    printf("program break decreased by %10ld\n",pb1-pb2);
}