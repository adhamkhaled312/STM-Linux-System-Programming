/******************************************************/
/* Author    : Adham Khaled                           */
/* Date      : 10 ABR 2024                            */
/* Version   : V01                                    */
/******************************************************/
#include "list.h"
/**
 * @brief initialize the list if there's is no allocation before
 * 
 * @param list pointer to the first entry of the list
 * @param size the size to be allocated at the beginning
 * @return char the return status -1:error 0:no error
 */
char init(block_t **list,size_t size){
    char retVal=0;
    (*list)=(void *)sbrk(size);
    if((void*)-1==list){
        perror("Can't initialize the heap");
        retVal=-1;
    }
    else{
        (*list)->next=NULL;
        (*list)->prev=NULL;
        (*list)->size=(size-sizeof(block_t));
        (*list)->status=FREE_BLOCK;
        retVal=0;
    }
    return retVal;
}

/**
 * @brief used to split a block of data into two blocks
 *        it's used in case of finding a block which is bigger than block needed
 * @param fitting pointer to the block which will be split
 * @param size 
 */
void split(block_t *fitting,size_t size){
    //if the remaining part will not be enough for metadata then don't split and mark block as used
    if(sizeof(block_t)<=fitting->size-size){
        //allocate new block after current block metadata and data
        block_t *new=(void*)((void*)fitting+size+sizeof(block_t));
        //configure the meta data of the new block
        new->size=(fitting->size)-size-sizeof(block_t);
        new->status=FREE_BLOCK;
        new->next=fitting->next;
        new->prev=fitting;
        //configure the metadata of the current block
        fitting->next=new;
        fitting->size=size;
        //link the next block of the new block with it (only if it exist) 
        if(NULL!=new->next){
            new->next->prev=new;
        }
    }
    fitting->status=USED_BLOCK;
}
/**
 * @brief used to allocate new space in heap if the current allocated space isn't enough
 *        first check if the block is free then extend it, if used then allocate new space
 * @param list pointer to the last block in the current free list
 * @param size the size to be allocated
 * @return char the return status -1:error 0:no error
 */
char new_alloc(block_t *list,size_t size){
    char retVal=0;
    //if the last block in the list is free then extend it so it can hold the data
    if(FREE_BLOCK==list->status){
        void*temp=sbrk(size);
        if((void *)-1==temp){
            perror("Can't allocate new space");
            retVal=-1;
    }
        else{
            //the size of the block will be the current size + the extended space size
            list->size+=size;
            retVal=0;
    }
    }
    else{
        //if the last block was a used block then allocate new space
        block_t *new=(void*)sbrk(size);
        if((void*)-1==new){
            perror("Can't allocate new space");
            retVal=-1;
        }
        else{
            //configure new block metadata and point from the current block to it
            new->prev=list;
            new->size=size-sizeof(block_t);
            new->next=NULL;
            new->status=FREE_BLOCK;
            list->next=new;
        }
    }
    return retVal;
}
void merge(block_t* block){
    //if the next block is also free block merge both blocks
    if(NULL!=(block->next) && FREE_BLOCK==(block->next)->status){
        //size of current block increased by size of the next block and its metadata
        block->size+=((block->next)->size)+sizeof(block_t);
        //remove the next block
        //if the next block isn't the last one link current block with the next of next
        if(NULL!=block->next->next){
            block->next->next->prev=block;
        }
        block->next=block->next->next;
    }
    //if the previous block is also free block merge both blocks
    if(NULL!=block->prev && FREE_BLOCK==(block->prev)->status){
        //size of previous  block increased by size of the current block and its metadata
        block->prev->size+=block->size+sizeof(block_t);
        //remove current block
        block->prev->next=block->next;
        block->next->prev=block->prev;

    }
}