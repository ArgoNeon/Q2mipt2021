#pragma once

enum {Q_INPUT = 0, Q_OUTPUT = 1, Q_MAIN = 2};

struct node_t
{
    int data;
    int page;
    char qltype;
    struct node_t* next;
    struct node_t* prev;
};

struct list_t
{
    struct node_t* front;
    struct node_t* back;
    struct node_t* trash_node;
    int size;
    int maxsize;
    char qltype;
};