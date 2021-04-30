#pragma once

#include "qlist.h"
#include "hash_table.h"

struct cache2q_t
{
    struct list_t* q_main;

    struct list_t* q_in;

    struct list_t* q_out;

    struct hash_table* hashtable;  
};