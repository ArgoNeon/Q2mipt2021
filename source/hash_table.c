#include "hash_table.h"

int compute_hash(int page, int param) {
  return (page % param);
};

  struct hash_table* hash_init(int npage){
  struct hash_table* table;
  struct hash_node_t* node;

  table = (struct hash_table*)calloc(1, sizeof(struct hash_table));
  node = (struct hash_node_t*)calloc(npage, sizeof(struct hash_node_t));

  table->hash_limit = npage;
  table->table = node;

  return table;
};

struct hash_node_t* find_page(int page, struct hash_table* table) {
  struct hash_node_t* p_node;
  int hash_page;

  hash_page = compute_hash(page, table->hash_limit);
  p_node = &(table->table[hash_page]);

  while (p_node->next != NULL) {
    p_node = p_node->next;
    if (p_node->page == page)
    return p_node;
  }

  return NULL;
};

void add_page(int page, struct hash_table* table, struct node_t* list_node) {
  struct hash_node_t* n_node;
  struct hash_node_t* p_node;
  int hash_page;

  n_node = (struct hash_node_t*)calloc(1, sizeof(struct hash_node_t));
  hash_page = compute_hash(page, table->hash_limit);
  p_node = &(table->table[hash_page]);

  while (p_node->next != NULL) {
    p_node = p_node->next;
  }

  p_node->next = n_node;
  n_node->prev = p_node;
  n_node->next = NULL;
  n_node->qnode = list_node;
  n_node->page = page;
};

void delete_page(int page, struct hash_table* table) {
  struct hash_node_t* d_node;

  d_node = find_page(page, table);

  d_node->prev->next = d_node->next;
  d_node->next->prev = d_node->prev;

  free(d_node);
};

void free_branch(struct hash_node_t* d_node){

  if (d_node != NULL)
  free_branch(d_node->next);
  free(d_node);
};

void free_hash(struct hash_table* table) {
int i;

for (i = 0; i < table->hash_limit; i++) {
  free_branch(table->table[i].next);
}

free(table->table);
free(table);
};
