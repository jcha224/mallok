 // John Chang
 // Header file: mallok.h

#ifndef MALLOK_H
#define MALLOK_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Make up of a node
typedef struct block {
    void *mem_address;
    int size;
    int free;
    struct block *next;
} Block;

// mallok prototypes
void create_pool(int size);
void *my_malloc(int size);
void my_free(void *block);
void free_pool();

#endif 