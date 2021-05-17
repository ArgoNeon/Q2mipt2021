/**
@file
@brief header file with 2q cache struct and function for it.
*/
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "qlist.h"
#include "hash_table.h"

/**
Queue constants (for using in struct cache_result_t)  
*/
enum {Q_MAIN = 0, Q_IN = 1, Q_OUT = 2, Q_NOTFOUND = -1};


/**
Struct of 2q cache. Contains three queue: main, input, output. And hashtable for ~O(1) search
*/
struct cache2q_t
{
    struct list_t* q_main;              /**< A pointer to main queue (most useful pages) */

    struct list_t* q_in;                /**< A pointer to input queue (recent pages) */

    struct list_t* q_out;               /**< A pointer to output queue (old pages) */

    struct hash_table* hashtable;       /**< Hashtable for ~O(1) search */
};

/**
Struct for result in cache_getdata function
*/
struct cache_result_t
{
    char res;            //*< Type of queue (see queue constants) */
    int data;            //*< Page data */
};

/**
Initialiaze of 2q cache struct
@param main_size size of main queue
@param in_size size of input queue
@param out_size size of output queue
@param hashsize max hash in hash table
@return pointer to created struct, NULL if not successful unsuccessfull
*/
struct cache2q_t* cache2q_init(int main_size, int in_size, int out_size, int hashsize);

/**
Clear 2q cache struct
@param cache pointer to cache
*/
void cache2q_free (struct cache2q_t* cache);


/**
Try to find data in cache. If didn't find calling function, that loads data
@param cache poiner to 2q cache
@param page number of page
@param page number of page
@param loaddata loadindng dadta function
*/
struct cache_result_t cache2q_getdata (struct cache2q_t* cache, int page, int (*loaddata)(int));
