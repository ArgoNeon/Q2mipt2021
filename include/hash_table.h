#pragma once

#include "qlist.h"

struct hash_node_t
{
    struct node_t* qnode;
    struct hash_node_t *prev, *next;
    int page;
};

struct hash_table
{
    int hash_limit;
    struct hash_node_t* table;
};