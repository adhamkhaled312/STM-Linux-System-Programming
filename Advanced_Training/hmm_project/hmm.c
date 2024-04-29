/******************************************************/
/* Author    : Adham Khaled                           */
/* Date      : 10 ABR 2024                            */
/* Version   : V01                                    */
/******************************************************/
#include "hmm.h"
// Pointer to the first block allocated in the heap 
static block_t *firstBlock=NULL;
 
/**
 * @brief function allocates bytes in heap and returns a pointer to the allocated memory
 *        The memory is not initialized.  If size is 0, then malloc() returns NULL
 * 
 * @param size number of bytes to be allocated
 * @return void* pointer to the allocated memory, return NULL if the request is failed
 */
void *HmmAlloc(size_t size){
    // allign allocated data to 8 bytes
    size=((size+7)/8)*8;
    block_t *curr;
    void *retVal=NULL;
    Std_ReturnType temp;
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
        if(size+sizeof(block_t)==(curr->size)&& FREE_BLOCK==curr->status){
            SET_BLOCK_USED(curr);
            retVal=(void*)((void*)curr+sizeof(block_t));
        }
        //if a block found with size greater than needed and has enough extra space for meta data
        else if((curr->size)>size+sizeof(block_t) && FREE_BLOCK==curr->status){
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
                //split the new allocated space
                split(curr,size);
                retVal=(void *)((void*)curr+sizeof(block_t));
            }
        }
    }
    return retVal;
}
/**
 * @brief The free() function frees the memory space pointed to by ptr,
 *        which must have been returned by a previous call to malloc(), calloc(), or realloc().  
 *        Otherwise, or  if  free(ptr)  has  already been called before, undefined behavior occurs.  
 *        If ptr is NULL, no operation is performed.
 * 
 * @param ptr pointer to the space to be freed
 */
void HmmFree(void *ptr){
    //if ptr is NULL no operation is performed
    if(NULL==ptr){
        return;
    }
    else{
        //mark the block as free
        block_t *block=ptr;
        block--;
        // if the block is already free don't do anything
        if(FREE_BLOCK==block->status){
            return;
        }
        SET_BLOCK_FREE(block);
        //merge the block if possible 
        //also check if the program break needs to be decreased to release memory to kernel
        merge(block,SUFF_DEC_BREAK);
    }
}
/**
 * @brief allocates  memory for an array of nmemb elements of size bytes each and returns a pointer to the allocated memory.
 *        The memory is set to zero.  If nmemb or size is 0 then returns NULL.
 *  
 * @param nmemb number of memory spaces want to allocate  
 * @param size the size of each memory space to allocate
 * @return void* pointer to the allocated memory, return NULL if the request is failed
 */
void *HmmCalloc(size_t nmemb, size_t size){
    //if any of the them are 0 return NULL
    void *retVal;
    if(0==nmemb || 0==size){
        retVal=NULL;
    }
    //if there multiplication caused overflow return NULL
    else if(nmemb*size==0){
        perror("Overflow occured");
        retVal=NULL;
    }
    // if everything is ok, then allocate wanted space and initialize it with 0
    else{
        retVal=HmmAlloc(nmemb*size);
        memset(retVal,0,nmemb*size);
    }
    return retVal;
}
/**
 * @brief changes the size of the memory block pointed to by ptr to size bytes.
 *        The contents will be unchanged in the range from the start of the region up to the minimum of the
          old  and  new  sizes.   If  the new size is larger than the old size, the added memory will not be initialized. 
          If ptr is NULL, then the call is equivalent to malloc(size),
          if size is equal to zero, and ptr is not NULL, then the call is equivalent to free(ptr).
 * 
 * @param ptr pointer to the memory block to change its size
 * @param size the new size wanted
 * @return void* pointer to the new allocated memory, return NULL if the request is failed
 */
void *HmmRealloc(void *ptr, size_t size){
    void *retVal=NULL;
    block_t *temp=ptr;
    //if ptr is NULL similar to malloc(size)
    if(NULL==ptr){
        retVal=HmmAlloc(size);
    }
    //if size is 0 similar to free(ptr)
    else if(0==size && NULL!=ptr){
        HmmFree(ptr);
    }
    //if ptr is not null and size is not zero
    //check the size of the new block is smaller or bigger than the current block
    else{
        temp--;
        size_t oldSize=temp->size;
        //if the user want to decrease the size of the current block then just split it
        if(oldSize>=size){
            split(temp,size);
            retVal=ptr;
        }
        //if the user want a bigger block then search for a block then copy the data to it and free the old block
        else{
            retVal=HmmAlloc(size);
            memcpy(retVal,ptr,oldSize);
            HmmFree(ptr);
        }
    }
    return retVal;
}

// to replace glibc hmm enable this part
#if REPLACE_GLIBC
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
#endif