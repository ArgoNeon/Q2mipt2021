#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "qlist.h"
#include "hash_table.h"

enum {Q_MAIN = 0, Q_IN = 1, Q_OUT = 2, Q_NOTFOUND = -1};

struct cache2q_t
{
    struct list_t* q_main;

    struct list_t* q_in;

    struct list_t* q_out;

    struct hash_table* hashtable;  
};

struct cache_result_t
{
    char res;
    int data;
};

struct cache2q_t* cache2q_init(int main_size, int in_size, int out_size);

void cache2q_free (struct cache2q_t* cache);

struct cache_result_t cache2q_getdata (struct cache2q_t* cache, int page, int (*loaddata)(int));