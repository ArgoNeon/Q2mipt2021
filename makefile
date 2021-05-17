CC = gcc
CFLAGS = -g -Wall -I include
BASEOBJECTS = cache.o hash_table.o qlist.o
OBJECTS = $(BASEOBJECTS) cache_test.o hash_test.o cache_test hash_test

qlist.o: source/qlist.c include/qlist.h
	$(CC) $(CFLAGS) source/qlist.c -c -o qlist.o

hash_table.o: source/hash_table.c include/hash_table.h
	$(CC) $(CFLAGS) source/hash_table.c -c -o hash_table.o

cache.o: source/cache.c include/cache.h
	$(CC) $(CFLAGS) source/cache.c -c -o cache.o

cache_test.o: source/cache_test.c
	$(CC) $(CFLAGS) source/cache_test.c -c -o cache_test.o

cache_test: $(BASEOBJECTS) cache_test.o
	$(CC) $(CFLAGS) $(BASEOBJECTS) cache_test.o -o cache_test

hash_test.o: source/hash_test.c
	$(CC) $(CFLAGS) source/hash_test.c -c -o hash_test.o

hash_test: $(BASEOBJECTS) hash_test.o
	$(CC) $(CFLAGS) $(BASEOBJECTS) hash_test.o -o -D cache_test

clean:
	rm -r -f $(OBJECTS)
	rm -f cache_test
