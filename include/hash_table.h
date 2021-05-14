#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "qlist.h"

struct hash_node_t
{
    struct node_t* qnode;
    struct hash_node_t *prev, *next;
    int page;
};

struct hash_table_t
{
    int hash_limit;
    struct hash_node_t* table;
};

int compute_hash (int page, int param);

struct hash_table_t* hash_init (int hash_limit);

struct node_t* hash_find_page (struct hash_table_t* htable, int page);

int hash_add_page (struct hash_table_t* htable, int page, struct node_t* qnode);

int hash_delete_page (struct hash_table_t* htable, int page);

void hash_free (struct hash_table_t* htable);