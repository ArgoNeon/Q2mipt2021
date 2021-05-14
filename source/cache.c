#include <stdio.h>
#include <assert.h>
#include "qlist.h"
#include "hash_table.h"
#include "cache.h"

struct cache2q_t* cache2q_init(int main_size, int in_size, int out_size, int hashsize) {

	assert(main_size >= 0);
	assert(in_size >= 0);
	assert(out_size >= 0);

	struct cache2q_t* cache = (struct cache2q_t*) calloc(1, sizeof(struct cache2q_t));
	assert(cache);

	cache->hashtable = hash_init (hashsize);
    assert (cache->hashtable != NULL);

	cache->q_main = list_init (main_size);
    assert (cache->q_main != NULL);

    cache->q_in = list_init (in_size);
    assert (cache->q_in != NULL);

    cache->q_out = list_init (out_size);
    assert (cache->q_out != NULL);

	return cache;
}

void cache2q_free (struct cache2q_t* cache)
{
    assert (cache != NULL);

    hash_free (cache->hashtable);

    list_free (cache->q_main);
    list_free (cache->q_in);
    list_free (cache->q_out);

    free (cache);
}

struct cache_result_t cache2q_getdata (struct cache2q_t* cache, int page, int (*loaddata)(int))
{
    struct cache_result_t result;                                     
    assert (cache != NULL);                                                                                 // Checking cache poitner


    struct node_t* node = hash_find_page (cache->hashtable, page);                                          // Try to find page in hash table
    if (node == NULL)                                                                                       // If not found
    {
        struct node_t* node = pregen_node (page, loaddata (page));                                          // Load page
        struct node_t* disp;                                                                
        list_push_front (cache->q_in, node, &disp);                                                         // Push in input list
        if (disp != NULL)                                                                                   // If element was displaced
        {
            list_push_front (cache->q_out, disp, &disp);                                                    // Push it in output queue
            hash_delete_page  (cache->hashtable, disp->page);                                               // delete from hash table
            free (disp);
        }

        hash_add_page (cache->hashtable, page, node);                                                       // Add page to hash table

        result.data = -1;
        result.res = Q_NOTFOUND;
        return result;                                                                                      // exit from function
    }

    if (list_contains_node (cache->q_main, node) == 1)                                                      // if in main queue
    {
        int move_res = list_move_front (cache->q_main, node);                                               // page is popular, move it in front of main queue

        result.data = node->data;
        result.res = Q_MAIN;
        return result;                                                                                      // if no problem, return from function
    }

    if (list_contains_node (cache->q_in, node) == 1)                                                        // if in input queue
    {
        int move_res = list_move_front (cache->q_in, node);                                                 // page is popular, move it in front of input queue

        result.data = node->data;
        result.res = Q_IN;
        return result;                                                                                      // if no problem, return from function
    }

    if (list_contains_node (cache->q_out, node) == 1)                                                       // if in output queue
    {
        struct node_t* disp;
        list_remove (cache->q_out, node, &disp);                                                            // remove from output queue
        list_push_front(cache->q_main, disp, &disp);                                                        // push to front of main queue
        hash_delete_page (cache->hashtable, disp->page);                                                    // delete from hash table
        free (disp);

        result.data = node->data;
        result.res = Q_OUT;
        return result;                                                                                      // return from function
    }

    assert ("page founded in hash table, but it isn't from any queue" == 0);                                // strange error
}