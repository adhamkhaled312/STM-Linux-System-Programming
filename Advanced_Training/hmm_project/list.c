/******************************************************/
/* Author    : Adham Khaled                           */
/* Date      : 10 ABR 2024                            */
/* Version   : V01                                    */
/******************************************************/
#include "list.h"
static char moveBrkDown(block_t *block,size_t decSize);

/**
 * @brief initialize the list if there's is no allocation before
 * 
 * @param list pointer to the first entry of the list
 * @param size the size to be allocated at the beginning
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOT_OK): The function had issue to perform this action  
 */
Std_ReturnType init(block_t **list,size_t size){
    Std_ReturnType retVal=E_OK;
    (*list)=(void *)sbrk(size);
    if((void*)-1==list){
        perror("Can't initialize the heap");
        retVal=E_NOT_OK;
    }
    else{
        (*list)->next=NULL;
        (*list)->prev=NULL;
        (*list)->size=(size-sizeof(block_t));
        (*list)->status=FREE_BLOCK;
        retVal=E_OK;
    }
    return retVal;
}

/**
 * @brief used to split a block of data into two blocks
 *        it's used in case of finding a block which is bigger than block needed
 * @param fitting pointer to the block which will be split
 * @param size the size of the block after splitting
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
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOT_OK): The function had issue to perform this action  
 */
Std_ReturnType new_alloc(block_t *list,size_t size){
    Std_ReturnType retVal=E_OK;
    //if the last block in the list is free then extend it so it can hold the data
    if(FREE_BLOCK==list->status){
        void*temp=sbrk(size);
        if((void *)-1==temp){
            perror("Can't allocate new space");
            retVal=E_NOT_OK;
    }
        else{
            //the size of the block will be the current size + the extended space size
            list->size+=size;
            retVal=E_OK;
    }
    }
    else{
        //if the last block was a used block then allocate new space
        block_t *new=(void*)sbrk(size);
        if((void*)-1==new){
            perror("Can't allocate new space");
            retVal=E_NOT_OK;
        }
        else{
            //configure new block metadata and point from the current block to it
            new->prev=list;
            new->size=size-sizeof(block_t);
            new->next=NULL;
            new->status=FREE_BLOCK;
            list->next=new;
            retVal=E_OK;
        }
    }
    return retVal;
}
/**
 * @brief checks if the free block can be merged with the next or previous free block (if there exist)
 *        it's also responsible for decreasing the program break if that can be done 
 * @param block pointer to the block to check on
 * @param decSize the minimum size of the free block needed to decrease the program break
*/

void merge(block_t* block,size_t decSize){
    Std_ReturnType retVal=0;
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
        if(NULL!=block->next){
            block->next->prev=block->prev;
        }
        block=block->prev;
    }
    // part responsible for decreasing program break if possible

    //if block size is greater than or equal the size given
    //then decrease sbrk to release the space to the kernel
    if(NULL==block->next && FREE_BLOCK==block->status && block->size>=decSize){
        retVal=moveBrkDown(block,decSize);
        if(E_NOT_OK==retVal){
            perror("Can't decrease program break");
        }
    }
}
/**
 * @brief helper function to decrease the program break
 * 
 * @param block pointer to the block to check on
 * @param decSize the minimum size of the free block needed to decrease the program break
 * @return Std_ReturnType status of the process
 *         (E_OK): The function is done successfully
 *         (E_NOT_OK): The function had issue to perform this action  
 */
static Std_ReturnType moveBrkDown(block_t *block,size_t decSize){
    void *temp;
    Std_ReturnType retVal=0;
    //move sbrk down with sufficient multiple of decSize 
    // in order not to call sbrk on the next free
    // and also leave some space (if that can be done) so next malloc may not call sbrk
    size_t remaining=block->size-((block->size)/decSize)*decSize;
    size_t decValue=((block->size)/decSize)*decSize;
    //if the block size is exactly size multiple of decSize
    //remove the last block
    if(0==remaining){
        block->prev->next=NULL;
        temp=sbrk(-((decValue)+sizeof(block_t)));
        if((void *)-1==temp){
            retVal=E_NOT_OK;
        }
        else{
            retVal=E_OK;
        }
    }
    //if the remaining size isn't 0 
    //just change the size of last block
    else{
        block->size=remaining;
        temp=sbrk(-(decValue));
            if((void *)-1==temp){
            retVal=E_NOT_OK;
        }
        else{
            retVal=E_OK;
        }
    }
    
    return retVal;
}