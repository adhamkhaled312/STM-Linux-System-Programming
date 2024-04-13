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
#define INIT_PAGE_ALLOC     33
/*----------------------Functions Declarations----------------------*/
/**
 * @brief function allocates bytes in heap and returns a pointer to the allocated memory
 *        The memory is not initialized.  If size is 0, then malloc() returns NULL
 * 
 * @param size number of bytes to be allocated
 * @return void* pointer to the allocated memory, return NULL if the request is failed
 */
void *HmmAlloc(size_t size);
void HmmFree(void *ptr);
#endif

