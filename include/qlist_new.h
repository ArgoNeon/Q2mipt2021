#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node_t
{
    int data;
    int page;
    void* key_pointer;
    struct node_t* next;
    struct node_t* prev;
};

struct list_t
{
    struct node_t* front;
    struct node_t* back;
    void* key_pointer;
    int size;
    int maxsize;
};

// key_pointer - указатель в уникальное место памяти, которое существует,
// пока существует список. Как вариант: key_pointer = calloc (1, sizeof (char))

// инициализация списка, принимает размер, возвращает укзатель на созданный спирок
struct list_t* list_init (int maxsize);

// генерирует ноду без указателей, принимает номер страницы и данные, возвращает указатель
struct node_t* pregen_node (int page, int data);

// пушит в конец списка list ноду node. Если вымещается элемент, 
// то содержимое disp (указатель на ноду) начинает указывать на нее
// если передать в качестве disp NULL, то просто чистится
// возвращает 0 при успехе, и 1, если что-то не сложилось, например node = NULL
int list_push_back (struct list_t* list, struct node_t* node, struct node_t** disp);

// то же, но в начало
int list_push_front (struct list_t* list, struct node_t* node, struct node_t** disp);

// Проверяет, принадлежит ли нода списку (сравнивает key_pointer)
int list_contains_node (struct list_t* list, struct node_t* node);

// аналогично пушам, если ноды нет, то возвращает 1
int list_remove (struct list_t* list, struct node_t* node, struct node_t** disp);

// применяет функцию в прямом порядке, от front до back
void list_apply_func (struct list_t* list, void (*func)(struct node_t*));

// применяет функцию в обратном порядке, от back до front
void list_apply_func_reverse (struct list_t* list, void (*func)(struct node_t*));

// печатает ноду (для использования совместно с предыдущими двумя функциями)
void print_node (struct node_t* node);

// чистит ноду (нужно для следующей функции)
void free_node (struct node_t* node);

// чистит список
void list_free (struct list_t* list);

// возвращает size
int list_cursize (struct list_t* list);

// maxsize
int list_maxsize (struct list_t* list);

// двигает элемент в начало. Возврщает 0 при успехе, 1 при неудаче (например, нода не из этого списка)
int list_move_front (struct list_t* list, struct node_t* node);

// 0, если пуст, 1 если не пуст
int list_is_empty (struct list_t* list);