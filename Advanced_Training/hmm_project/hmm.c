/******************************************************/
/* Author    : Adham Khaled                           */
/* Date      : 10 ABR 2024                            */
/* Version   : V01                                    */
/******************************************************/
#include "hmm.h"
static block_t *firstBlock=NULL;

void *HmmAlloc(size_t size){
    // if there is no block assigned (the list is still empty)
    if(!firstBlock){
        //initialize the heap by allocating INIT_PAGE_ALLOC pages in it
        init(firstBlock,VM_PAGE_SIZE*INIT_PAGE_ALLOC);
    }
}
void HmmFree(void *ptr){

}