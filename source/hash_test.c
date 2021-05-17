#include "hash_table.h"
#include "qlist.h"
#include <time.h>
#include <math.h>

#define MAX 50
#define MIN 16

/**
Array of pages.
*/

struct array {
    struct node_t* mnode;   /**< a pointer to a array of pages. */
    int size;               /**< a quantity of array's elements. */
};

/**
Array of requests.
*/

struct dat {
    int* mpage;             /**< a pointer to a array of requests. */
    int size;               /**< a quantity of array's elements. */
};

/**
Generating of a random number.
@return a random number
*/

int my_rand()
{
    int x;

    x = rand() % (MAX - MIN) + MIN;
    return x;
}

/**
Generating a random number not exceeding a certain size.
@param size the largest possible number.
@return a random number.
*/

int my_rand_size (int size)
{
    int x;

    x = my_rand() % size + 1;
    return x;
}

/**
Creating a random array of pages.
@return a pointer to a random array of pages.
*/

struct array* gen_array ()
{
    struct array* arr;
    struct node_t* node;
    int size;
    int i;

    arr = (struct array*) calloc (1, sizeof (struct array));
    assert (arr);
    size = my_rand ();
    assert (size > 0);
    node = (struct node_t*) calloc (size, sizeof (struct node_t));
    assert (node);

    for (i = 0; i < size; i++) {
        node[i].page = i + 1;
    }

    arr->size = size;
    arr->mnode = node;
    return arr;
}

/**
Creating an array of pages with certain size.
@param size the quantity of array's elements.
@return a pointer to an array of pages.*/

struct array* create_array (int size)
{
    struct array* arr;
    struct node_t* node;
    int i;

    assert (size > 0);
    arr = (struct array*) calloc (1, sizeof (struct array));
    assert (arr);
    node = (struct node_t*) calloc (size, sizeof (struct node_t));
    assert (node);

    for (i = 0; i < size; i++) {
        node[i].page = i + 1;
    }

    arr->size = size;
    arr->mnode = node;
    return arr;
}

/**
Creating a random array of requests.
@param size the largest value for request.
@return a pointer to a random array of requests.
*/

struct dat* gen_dat (int size)
{
    struct dat* dat;
    int* page;
    int i, len;

    len = my_rand();
    dat = (struct dat*) calloc (1, sizeof (struct dat));
    page = (int*) calloc (len, sizeof (int));
    assert (page);

    for (i = 0; i < len; i++) {
        page[i] = my_rand_size (size);
    }

    dat->mpage = page;
    dat->size = len;

    return dat;
}

/**
Deleting unnecessary data.
*/

void cut_tail()
{
    char x;

    scanf ("%c", &x);

    while (x != '\n') {
        scanf ("%c", &x);
    }
}

/**
Reading an array of requests with certain size.
@param len the length of array.
@param size the largest value for request.
@return a pointer to an array of requests.
*/

struct dat* create_dat (int len, int size)
{
    struct dat* dat;
    int* page;
    int i, x, res;

    dat = (struct dat*) calloc (1, sizeof (struct dat));
    page = (int*) calloc (len, sizeof (int));
    assert (page);

    for (i = 0; i < len; i++) {
        res = scanf ("%d", &x);
        assert (res == 1);

        while (x > size) {
            cut_tail();
            printf ("Write real page.\n");
            res = scanf ("%d", &x);
            assert (res == 1);
        }

        page[i] = x;
    }

    cut_tail();

    dat->mpage = page;
    dat->size = len;

    return dat;
}

/**
Testing of the hash_table.
@param a pointer to an array of pages.
@param a pointer to an array of requests.
@param hash_size the size of the hash_table.
*/

void test (struct array* arr, struct dat* dat, int hash_size)
{
    struct hash_table* table;
    int i;

    printf ("Start testing...\n");
    table = hash_init (hash_size);
    assert (table);

    for (i = 0; i < dat->size; i++) {
        add_page (table, dat->mpage[i], & (arr->mnode[i]));
    }

    for (i = 0; i < dat->size; i++) {
        assert (find_page (table, dat->mpage[i]));
    }

    printf ("Add and find\n");

    for (i = 0; i < dat->size; i++) {
        delete_page (table, dat->mpage[i]);
    }

    for (i = 0; i < dat->size; i++) {
        assert (find_page (table, dat->mpage[i]) == NULL);
    }

    printf ("Delete and check\n");

    free_hash (table);
    free (arr->mnode);
    free (dat->mpage);
    free (arr);
    free (dat);
    printf ("Full free\n");
}

/**
Creating of a random test.
*/

void rand_test()
{
    struct array* arr;
    struct dat* dat;
    int hash_size;

    arr = gen_array();
    dat = gen_dat (arr->size);
    hash_size = my_rand_size (100);

    test (arr, dat, hash_size);
}

/**
Creating of a random tests.
*/

void rand_tests()
{
    int i, n, res;

    printf ("How many rand tests?\n");
    res = scanf ("%d", &n);

    while (res != 1 || n < 0) {
        cut_tail();
        printf ("Enter a positive number or 0.\n");
        res = scanf ("%d", &n);
    }

    for (i = 0; i < n; i++) {
        printf ("Test %d\n", i + 1);
        rand_test();
    }
}

/**
Reading of the test.
*/

void hand_test()
{
    int hash_size, len_dat, i, npage, res;
    struct dat* dat;
    struct array* arr;
    struct hash_table* table;

    printf ("Write size of the hash table...\n");
    res = scanf ("%d", &hash_size);
    assert (res == 1);
    cut_tail();

    printf ("Write quantity of pages...\n");
    res = scanf ("%d", &npage);
    assert (res == 1);
    cut_tail();

    printf ("Write quantity of requests...\n");
    res = scanf ("%d", &len_dat);
    assert (res == 1);
    cut_tail();

    printf ("Write all requests...\n");
    dat = create_dat (len_dat, npage);
    arr = create_array (npage);

    test (arr, dat, hash_size);

}

/**
Reading of the tests.
*/

void hand_tests()
{
    int i, res, q_htests;

    printf ("How many hand tests?\n");
    res = scanf ("%d", &q_htests);

    while (res != 1 || q_htests < 0) {
        cut_tail();
        printf ("Enter a positive number or 0.\n");
        res = scanf ("%d", &q_htests);
    }

    for (i = 0; i < q_htests; i++) {
        hand_test();
    }
}

/**
Testing of the basic test.
*/

void basic_test (struct array* arr, struct dat* dat, int hash_size)
{
    struct hash_table* table;
    int i;

    printf ("Start testing...\n");
    table = hash_init (hash_size);
    assert (table);

    for (i = 0; i < dat->size; i++) {
        add_page (table, dat->mpage[i], & (arr->mnode[i]));
    }

    for (i = 0; i < dat->size; i++) {
        assert (find_page (table, dat->mpage[i]));
    }

    printf ("Add and find\n");

    for (i = 0; i < dat->size; i++) {
        delete_page (table, dat->mpage[i]);
    }

    for (i = 0; i < dat->size; i++) {
        assert (find_page (table, dat->mpage[i]) == NULL);
    }

    printf ("Delete and check\n");

    free_hash (table);
    free (arr->mnode);
    free (arr);
    printf ("Full free\n");
}

/**
Testing of the basic tests.
*/

void basic_tests()
{
    int mas1[6] = {1, 2, 1, 2, 1, 2};
    int mas2[7] = {1, 2, 3, 4, 5, 6, 7};
    int mas3[12] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 4, 3, 4};
    struct dat dat1 = {mas1, 6};
    struct dat dat2 = {mas2, 7};
    struct dat dat3 = {mas3, 12};
    struct array* arr1, *arr2, *arr3;

    arr1 = create_array (2);
    arr2 = create_array (3);
    arr3 = create_array (4);

    printf ("Start basic testing...\n");
    printf ("Test №1\n");
    basic_test (arr1, &dat1, dat1.size);
    printf ("Test №2\n");
    basic_test (arr2, &dat2, dat2.size);
    printf ("Test №3\n");
    basic_test (arr3, &dat3, dat3.size);
    printf ("Accepted\n");
}

int main()
{
    struct array* arr;
    struct hash_table* table;
    struct hash_node_t* f_node;
    int n, q_htests, i, size, res;

    srand (time (NULL));

    basic_tests();
    rand_tests();
    hand_tests();

    return 0;
}
