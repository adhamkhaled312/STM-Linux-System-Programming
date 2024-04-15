#include "hmm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
extern block_t *firstBlock;
void merge_test();
void alloc_in_middle();
int main(){
    void*before=sbrk(0);
    
    char *ptr[1000];
    for(int i=0;i<1000;i++){
        ptr[i]=HmmAlloc(10240);
        if(ptr[i]==NULL)
            printf("error");
    }
    void*after=sbrk(0);
    for (int j = 1 - 1; j < 1000; j += 2)
        HmmFree(ptr[j]);
    void* after_free=sbrk(0);
    printf("Initial program break: %10p\n", before);
    printf("program break is now : %10p\n", after);
    printf("After free(), program break is: %10p\n", after);
    block_t *curr=firstBlock;
    while(NULL!=curr){
        printf("%10p    %10p    %10p    %10li    %10i\n",curr,curr->next,curr->prev,curr->size,curr->status);
        curr=curr->next;
    }
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