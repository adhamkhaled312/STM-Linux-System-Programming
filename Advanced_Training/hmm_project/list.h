/******************************************************/
/* Author    : Adham Khaled                           */
/* Date      : 10 ABR 2024                            */
/* Version   : V01                                    */
/******************************************************/

/*----------------------Includes----------------------*/

#include <unistd.h>
#include <stdio.h>
/*----------------------Macro Declarations----------------------*/
/**
 * @brief indicates that the block is free
 * 
 */
#define FREE_BLOCK  0
/**
 * @brief indicate that the block is used
 * 
 */
#define USED_BLOCK  1
/*----------------------Macro Functions Declarations----------------------*/
/**
 * @brief macro function to convert free block into used block
 * 
 */
#define SET_BLOCK_USED(BLOCK)    (BLOCK->status=USED_BLOCK)

/**
 * @brief macro function to convert used block into free block
 * 
 */
#define SET_BLOCK_FREE(BLOCK)    (BLOCK->status=FREE_BLOCK)
/**
 * @brief macro function to traverse the list to find the suitbale block for the desired size
 * 
 */
#define TRAVERSE_LIST(CURR,SIZE)                                                                                \
    while ((CURR->next) != NULL && ((CURR->size) < (SIZE + sizeof(block_t)) || (CURR->status) == USED_BLOCK)) { \
        CURR = CURR->next;                                                                                      \
    } 

/* ----------------Data Types Declarations----------------*/
/**
 * @brief structure represnting the meta data of allocated block
 * 
 */
typedef struct block
{
    struct block *prev; /* points to the prevoius block */
    struct block *next; /* points to the next block */
    size_t size;        /* the size of the block of data (without meta data )*/
    char status;        /* the status of block FREE_BLOCK or USED_BLOCK */
   
}block_t;

/* ----------------Functions Declarations----------------*/
/**
 * @brief initialize the list if there's is no allocation before
 * 
 * @param list pointer to the first entry of the list
 * @param size the size to be allocated at the beginning
 * @return char the return status -1:error 0:no error
 */
char init(block_t **list,size_t size);

/**
 * @brief used to split a block of data into two blocks
 *        it's used in case of finding a block which is bigger than block needed
 * @param fitting pointer to the block which will be split
 * @param size the size of the block after splitting
 */
void split(block_t *fitting,size_t size);

/**
 * @brief used to allocate new space in heap if the current allocated space isn't enough
 *        first check if the block is free then extend it, if used then allocate new space
 * @param list pointer to the last block in the current free list
 * @param size the size to be allocated
 * @return char the return status -1:error 0:no error
 */
char new_alloc(block_t *list,size_t size);
/**
 * @brief checks if the free block can be merged with the next or previous free block (if there exist)
 *        it's also responsible for decreasing the program break if that can be done 
 * @param block pointer to the block to check on
 * @param decSize the minimum size of the free block needed to decrease the program break
 * @return char the return status -1:error 0:no error
 */
char merge(block_t* block,size_t decSize);
