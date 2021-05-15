#include "cache.h"
#include <string.h>
#include <time.h>

int loadfakedata (int page)
{
    return page;
}

void prepared (int argc, char *argv[])
{
    int cache_size, npages, pg;
    int hit = 0, miss = 0;
    struct cache_result_t res;
    struct cache2q_t* cache;
    
    if (scanf ("%d%d", &cache_size, &npages) < 2)
    {
        printf ("ERROR: not enough data or broken input");
        exit (1);
    }
    cache = cache2q_init ((cache_size + 3) / 4, (cache_size + 1) / 4, cache_size / 2, cache_size * 10);

    for (int i = 0; i < npages; i++)
    {
        if (scanf ("%d", &pg) < 1)
        {
            printf ("ERROR: not enough data or broken input");
            exit (1);
        }

        res = cache2q_getdata (cache, pg, loadfakedata);
        if (res.res != Q_NOTFOUND)
            hit++;
        else
            miss++;
    }

    printf ("Results:\n\tpages: %d\n\thits: %d\n\tmiss: %d\n\thitrate: %f%%\n", npages, hit, miss, (float) hit / npages * 100);
}

void randtest (int argc, char *argv[])
{
    int cache_size, npages, pg, maxpage;
    int hit = 0, miss = 0;
    struct cache_result_t res;
    struct cache2q_t* cache;
    srand (time (NULL));
    
    if (scanf ("%d%d%d", &cache_size, &npages, &maxpage) < 3)
    {
        printf ("ERROR: not enough data or broken input");
        exit (1);
    }
    cache = cache2q_init ((cache_size + 3) / 4, (cache_size + 1) / 4, cache_size / 2, cache_size * 10);

    for (int i = 0; i < npages; i++)
    {
        res = cache2q_getdata (cache, rand () % maxpage, loadfakedata);
        if (res.res != Q_NOTFOUND)
            hit++;
        else
            miss++;
    }

    printf ("Results:\n\tpages: %d\n\thits: %d\n\tmiss: %d\n\thitrate: %.1f\n", npages, hit, miss, (float) hit / npages * 100);
}

void print_help ()
{
    printf ("usage:\n");
    printf ("\tcache_test --help    show help\n");
    printf ("\tcache_test -p        test cache with pregenerated data\n");
    printf ("\t\tinput: <cache size> <number of pages> <pages>\n");
    printf ("\tcache_test -r        test cache with random data\n");
    printf ("\t\tinput: <cache size> <number of pages> <max page>\n");
}

int main (int argc, char *argv[])
{
    if (argc == 1 || (argc > 1 && strncmp (argv[1], "--help", 6) == 1))
        print_help ();
    if (argc > 1 && strncmp (argv[1], "-p", 2) == 1)
        prepared (argc, argv);
    if (argc > 1 && strncmp (argv[1], "-r", 2) == 1)
        randtest (argc, argv);
    else
        printf ("%s is not cache_test command. Use \"cache_test --help\" to see all commands\n", argv[1]);
}