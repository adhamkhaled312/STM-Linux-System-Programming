/******************************************************/
/* Author    : Adham Khaled                           */
/* Date      : 10 ABR 2024                            */
/* Version   : V01                                    */
/******************************************************/
#include "hmm.h"
 block_t *firstBlock=NULL;

void *HmmAlloc(size_t size){
    block_t *curr;
    void *retVal=NULL;
    char temp;
    // if there is no block assigned (the list is still empty)
    if(!firstBlock){
        //initialize the heap by allocating INIT_PAGE_ALLOC pages in it
        temp=init(&firstBlock,VM_PAGE_SIZE*INIT_PAGE_ALLOC);
        //if error occured during allocating set retVal to null
        if(-1==temp){
            retVal=NULL;
        }
        else{
            //split the allocated pages into the part user needed and the other part is free
            split(firstBlock,size);
            //return to the user pointer to the start of the data (after the metadata)
            retVal=(void*)((void*)firstBlock+sizeof(block_t));
        }
    }
    else{
        // traverse free list to find the suitable block
        curr=firstBlock;
        TRAVERSE_LIST(curr,size);
        //if a block with found the same size allocate it (mark it as not free)
        if(size==(curr->size)){
            SET_BLOCK_USED(curr);
            retVal=(void*)((void*)curr+sizeof(block_t));
        }
        //if a block found with size greater than needed and has enough extra space for meta data
        else if((curr->size)>size+sizeof(block_t)){
            split(curr,size);
            retVal=(void*)((void*)curr+sizeof(block_t));
        }
        //no block is found in the free list then we need to allocate new space in heap
        else{
            temp=new_alloc(curr,VM_PAGE_SIZE*INIT_PAGE_ALLOC);
            if(-1==temp){
                retVal=NULL;
            }
            else{
                //if the current block is used then a new block is allocated
                if(USED_BLOCK==curr->status){
                    curr=curr->next;
                }
                split(curr,size);
                retVal=(void *)((void*)curr+sizeof(block_t));
            }
        }
    }
    return retVal;
}
void HmmFree(void *ptr){

}