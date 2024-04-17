/******************************************************/
/* Author    : Adham Khaled                           */
/* Date      : 10 ABR 2024                            */
/* Version   : V01                                    */
/******************************************************/
#include "hmm.h"
// Pointer to the first block allocated in the heap 
 block_t *firstBlock=NULL;
 
/**
 * @brief function allocates bytes in heap and returns a pointer to the allocated memory
 *        The memory is not initialized.  If size is 0, then malloc() returns NULL
 * 
 * @param size number of bytes to be allocated
 * @return void* pointer to the allocated memory, return NULL if the request is failed
 */
void *HmmAlloc(size_t size){
    block_t *curr;
    void *retVal=NULL;
    Std_ReturnType temp;
    //if size is zero retrn NULL
    if(0==size){
        retVal=NULL;
    }
    else{
        
        // if there is no block assigned (the list is still empty)
        if(!firstBlock){
            //initialize the heap by allocating multiple of ALLOC_SPACE pages in it
            //that handles if the user entered very big size
            temp=init(&firstBlock,((size/ALLOC_SPACE)+1)*ALLOC_SPACE);
            //if error occured during allocating set retVal to null
            if(E_NOT_OK==temp){
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
                temp=new_alloc(curr,((size/ALLOC_SPACE)+1)*ALLOC_SPACE);
                if(E_NOT_OK==temp){
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
    }
    
    return retVal;
}
void HmmFree(void *ptr){
    //if ptr is NULL no operation is performed
    if(NULL==ptr){
        return;
    }
    else{
        //mark the block as free
        block_t *block=ptr;
        block--;
        SET_BLOCK_FREE(block);
        //merge the block if possible 
        //also check if the program break needs to be decreased to release memory to kernel
        merge(block,SUFF_DEC_BREAK);
    }
}