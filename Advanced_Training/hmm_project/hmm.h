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
#include <string.h>
/*----------------------Macro Declarations----------------------*/

/**
 * @brief if we have a contigous free SUFF_DEC_BREAK Bytes block at top of heap then decrease program break
 *        this is used to decrease the number of calls to sbrk
 */
#define SUFF_DEC_BREAK      128*1024
/**
 * @brief size of virtal memory page in linux is 4k
 */
#define VM_PAGE_SIZE        4096
/**
 * @brief number of pages to be allocated when using sbrk to decrease the number of calls to sbrk
 * 
 */
#define INIT_PAGE_ALLOC     33

/**
 * @brief minumum amount of memory allocated on sbrk call
 * 
 */
#define ALLOC_SPACE          (VM_PAGE_SIZE*INIT_PAGE_ALLOC)
/*----------------------Functions Declarations----------------------*/
/**
 * @brief function allocates bytes in heap and returns a pointer to the allocated memory
 *        The memory is not initialized.  If size is 0, then malloc() returns NULL
 * 
 * @param size number of bytes to be allocated
 * @return void* pointer to the allocated memory, return NULL if the request is failed
 */
void *HmmAlloc(size_t size);
/**
 * @brief The free() function frees the memory space pointed to by ptr,
 *        which must have been returned by a previous call to malloc(), calloc(), or realloc().  
 *        Otherwise, or  if  free(ptr)  has  already been called before, undefined behavior occurs.  
 *        If ptr is NULL, no operation is performed.
 * 
 * @param ptr pointer to the space to be freed
 */
void HmmFree(void *ptr);
void *HmmCalloc(size_t nmemb, size_t size);
void *HmmRealloc(void *ptr, size_t size);

#endif

