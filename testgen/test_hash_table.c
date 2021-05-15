#include "hash_table.h"
#include "qlist.h"
#include <time.h>
#include <math.h>

#define MAX 50
#define MIN 16

struct array {
  struct node_t* mnode;
  int size;
};

struct dat{
  int* mpage;
  int size;
};

int my_rand() {
  int x;

  x = rand() % (MAX - MIN) + MIN;
  return x;
}

int my_rand_size(int size) {
  int x;

  x = my_rand() % size + 1;
  return x;
}

struct array* gen_array (){
  struct array* arr;
  struct node_t* node;
  int size;
  int i;

  arr = (struct array*)calloc(1, sizeof (struct array));
  assert(arr);
  size = my_rand ();
  assert (size > 0);
  node = (struct node_t*)calloc(size, sizeof (struct node_t));
  assert(node);

  for (i = 0; i < size; i++) {
    node[i].page = i + 1;
  }

  arr->size = size;
  arr->mnode = node;
  return arr;
}

struct array* create_array (int size){
  struct array* arr;
  struct node_t* node;
  int i;

  assert (size > 0);
  arr = (struct array*)calloc(1, sizeof (struct array));
  assert(arr);
  node = (struct node_t*)calloc(size, sizeof (struct node_t));
  assert(node);

  for (i = 0; i < size; i++) {
    node[i].page = i + 1;
  }

  arr->size = size;
  arr->mnode = node;
  return arr;
}

struct dat* gen_dat(int size) {
  struct dat* dat;
  int* page;
  int i, len;

  len = my_rand();
  dat = (struct dat*)calloc(1, sizeof(struct dat*));
  page = (int*)calloc(len, sizeof(int));
  assert(page);

  for (i = 0; i < len; i++) {
    page[i] = my_rand_size(size);
  }

  dat->mpage = page;
  dat->size = len;

  return dat;
}

struct dat* create_dat(int len) {
  struct dat* dat;
  int* page;
  int i, x, res;

  dat = (struct dat*)calloc(1, sizeof(struct dat*));
  page = (int*)calloc(len, sizeof(int));
  assert(page);

  for (i = 0; i < len; i++) {
    res = scanf("%d", &x);
    assert(res == 1);
    page[i] = x;
  }

  dat->mpage = page;
  dat->size = len;

  return dat;
}

void test(struct array* arr, struct dat* dat, int hash_size) {
  struct hash_table* table;
  int i;

  printf ("Start testing...\n");
  table = hash_init(hash_size);
  assert(table);

  for (i = 0; i < dat->size; i++) {
    add_page(dat->mpage[i], table, &(arr->mnode[i]));
  }

  for (i = 0; i < dat->size; i++) {
    assert(find_page(dat->mpage[i], table));
  }

  printf("Add and find\n");

  for (i = 0; i < dat->size; i++) {
    delete_page(dat->mpage[i], table);
  }

  for (i = 0; i < dat->size; i++) {
    assert(find_page(dat->mpage[i], table) == NULL);
  }

  printf ("Delete and check\n");

  free_hash(table);
  free(arr->mnode);
  free(dat->mpage);
  free(arr);
  free(dat);
  printf ("Full free\n");
}

void rand_test() {
  struct array* arr;
  struct dat* dat;
  int hash_size;

  arr = gen_array();
  dat = gen_dat(arr->size);
  hash_size = my_rand_size(100);

  test(arr, dat, hash_size);
}

void rand_tests(int n) {
  int i;

  for (i = 0; i < n; i++) {
    printf ("Test %d\n", i + 1);
    rand_test();
  }
}

void hand_test(){
  int hash_size, len_dat, i, npage, res;
  struct dat* dat;
  struct array* arr;
  struct hash_table* table;

  printf ("Write size of the hash table...\n");
  res = scanf ("%d", &hash_size);
  assert(res == 1);

  printf ("Write size of pages...\n");
  res = scanf ("%d", &npage);
  assert(res == 1);

  printf ("Write quantity of requests...\n");
  res = scanf ("%d", &len_dat);
  assert(res == 1);

  table = hash_init(hash_size);
  assert(table);

  printf ("Write all requests...\n");
  dat = create_dat(len_dat);
  arr = create_array(npage);

  test(arr, dat, hash_size);

}

int main() {
  struct array* arr;
  struct hash_table* table;
  struct hash_node_t* f_node;
  int n, q_htests, i, size, res;

  srand (time(NULL));

  scanf ("%d", &n);

  rand_tests(n);
  printf("How many hand tests?\n");
  res = scanf("%d", &q_htests);
  assert(res == 1);

  for (i = 0; i < q_htests; i++) {
    hand_test();
  }

  return 0;
}
