// John Chang

#include <stdio.h>

#include "mallok.h"

// Global variables
static Block *private_heap = NULL;
static void *private_mem = NULL;
static int private_check = 0;

// prototypes
void create_pool(int size);
void *my_malloc(int size);
void my_free(void *block);
void free_pool();
void split(Block *theBlock, int size);
void merge();

/**
 * Creates a data pool at specified size.
 */
void create_pool(int size) {    
    private_heap = malloc(sizeof(Block));
    private_heap->mem_address = malloc(size + sizeof(Block));
    private_mem = private_heap->mem_address;
    private_heap->next = NULL;
    private_heap->size = size;
    private_heap->free = 1;
    private_check = 1;
    
}

/**
 *  Takes a piece of the datapool and creates a block.
 */
void *my_malloc(int size) {
    Block *current = NULL, *back = NULL;
    void *result = NULL;
    if(private_check) {
        current = private_heap;
        while((((current->size) < size) || ((current->free) == 0))
                                        && (current->next != NULL)) {
            back = current;
            current = current->next;
        }  
        if((current->free)&&(current->size == size)) {
            current->free = 0;
            result = current->mem_address;
        } else if((current->free)&&(current->size > size)) {
            split(current, size);
            result = current->mem_address;
        } else {
            result = NULL;
        }
        
    }
    return result;
    
}

/**
 * Splits memory to fit with the block.
 */
void split(Block *theBlock, int size) {
    Block *temp = malloc(sizeof(Block));
    temp->mem_address = theBlock->mem_address + size;
    temp->size = theBlock->size - size;
    temp->next = theBlock->next;
    temp->free = 1;
    theBlock->free = 0;
    theBlock->size = size;
    theBlock->next = temp;
    
}

/**
 * Combines the free memory into one block.
 */
void merge() {
    Block *back = NULL;
    Block *current = private_heap;
    while((current->next) != NULL) {
        back = current;
        current = current->next;
        if((back->free) && (current->free)) {
            back->size += (current->size);
            back->next = current->next;
        }
    }
}
 
/**
 * Frees memory of specified block.
 */
void my_free(void *block) {
    Block *current = private_heap;
    while(!(current->free) && current->mem_address != block 
            && current->next != NULL) {
        current = current->next;
    }
    if(current->mem_address == block) {
        current->free = 1;
        merge();
    } 
}

/**
 * Completely frees the private heap.
 */
 void free_pool() {
     Block *back = private_heap;
     Block *current = private_heap->next;
    while(current->next != NULL) {
        back = current;
        current = current->next;
        free(back->mem_address);
        back->mem_address = NULL;
        free(back);
        back == NULL;
    }
    free(current->mem_address);
    current->mem_address = NULL;
    free(current);
    current = NULL;
    private_check = 0;
 }