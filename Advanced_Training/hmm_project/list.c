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
 * @return int the return status -1:error 0:no error
 */
int init(block_t **list,size_t size){
    int retVal=0;
    (*list)=(void *)sbrk(size+sizeof(block_t));
    if(list==(void*)-1){
        perror("Can't initialize the heap");
        retVal=-1;
    }
    else{
        (*list)->next=NULL;
        (*list)->prev=NULL;
        (*list)->size=size;
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
    block_t *new=(void*)((void*)fitting+size+sizeof(block_t));
    new->size=(fitting->size)-size-sizeof(block_t);
    new->status=FREE_BLOCK;
    new->next=fitting->next;
    new->prev=fitting;
    fitting->next=new;
    fitting->size=size;
    fitting->status=USED_BLOCK;
}