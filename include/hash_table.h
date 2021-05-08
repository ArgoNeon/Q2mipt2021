#pragma once

#include "qlist.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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

int compute_hash(int page, int param);

struct hash_table* hash_init(int npage);

struct hash_create_node* find_page(int page, struct hash_table* table);

void add_page(int page, struct hash_table* table, struct hash_node_t* node);

void delete_page(int page, struct hash_table* table);

void free_hash(struct hash_table* table);
