#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "qlist.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/**
An element of the hash table.
*/
struct hash_node_t
{
    struct node_t* qnode;             /**< a pointer to an element of the list. */
    struct hash_node_t *prev, *next;  /**< pointers to the previous and next elements of the hash table. */
    int page;                         /**< the page, located in current element of the hash table. */
};

/**
Table with the maximum number of pages.
*/
struct hash_table
{
    struct hash_node_t* table;        /**< an array of the elements of the hash table. */
    int hash_limit;                   /**< maximum number of elements with different hashs. */
};

/**
Calculating the hash of the page according to parameter.
@param page the page, which hash we need to know.
@param param the maximum number of pages in the hash table.
@return the hash of the page.
*/
int compute_hash(int page, int param);

/**
Creating a hash table.
@param npage the maximum number of pages in the hash table.
@return a pointer to the struct of the hash table.
*/
struct hash_table* hash_init(int npage);

/**
@param page a page which we want to find.
@param table a pointer to the struct of the hash table, where we are searching.
@return a pointer to the element of the hash table if this page is founded or NULL pointer if it is not.
*/
struct hash_node_t* find_page(struct hash_table* table, int page);

/**
Adding the page in the hash table.
@param table a pointer to the struct of the hash table, where we want to add.
@param page a page we want to add.
@param node a pointer to the element of list, where this page is located.
*/
void add_page(struct hash_table* table, int page, struct node_t* node);

/**
Deleting the page from the hash table.
@param table a pointer to the struct of the hash table, where we want to delete.
@param page a page we want to delete.
*/
void delete_page(struct hash_table* table, int page);

/**
Deleting the branch with all collisions.
@param d_node a pointer to the element, starting from which we delete all elements of the branch.
*/
void free_branch(struct hash_node_t* d_node);

/**
Deleting the struct of the hash table.
@param table a pointer to the struct of the hash table, which we want to delete.
*/
void free_hash(struct hash_table* table);
