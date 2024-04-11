/******************************************************/
/* Author    : Adham Khaled                           */
/* Date      : 10 ABR 2024                            */
/* Version   : V01                                    */
/******************************************************/
#ifndef HMM_H
#define HMM_H

/*----------------------Includes----------------------*/
#include "list.h"
#include <unistd.h>

/*----------------------Macro Declarations----------------------*/

/**
 * @brief if we have a contigous free SUFF_DEC_BREAK kB block at top of heap then decrease program break
 *        this is used to decrease the number of calls to sbrk
 */
#define SUFF_DEC_BREAK      128
/**
 * @brief size of virtal memory page in linux is 4k
 */
#define VM_PAGE_SIZE        4096
/**
 * @brief number of pages to be allocated when using sbrk to decrease the number of calls to sbrk
 * 
 */
#define INIT_PAGE_ALLOC     5

/*----------------------Functions Declarations----------------------*/

void *HmmAlloc(size_t size);
void HmmFree(void *ptr);
#endif

