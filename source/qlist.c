#include "qlist.h"


struct list_t* list_init (int maxsize){

    //maxsize здесь личный параметр списка
    //список создаётся пустым

    assert(maxsize>=0);

    struct list_t* list = (struct list_t*)malloc(sizeof(struct list_t));
    list_t->maxsize = maxsize;
    list_t->size = 0;
    list_t->front = NULL;
    list_t->back = NULL;

    return list;
}

struct node_t* pregen_node (int page, int data);
    struct node_t* node = (struct node_t*)calloc(1, sizeof(struct node_t));
    node->page = page;
    node->data = data;
    return node;
}

int list_push_back (struct list_t* list, struct node_t* node, struct node_t** disp){

    //обрабатываем проблемы (пока не знаю зачем, есть же assert)
    if(node==NULL){
        printf("Пришёл некорректный node = NULL");
        return 1;
    }

    //если не влезает, направляем на node disp
    if(list->size+sizeof(struct node_t)>list->maxsize){
        &disp = node;

        return 0;
    }
    if (list_is_empty(list)==0){
        node->next = NULL;
        node->back = NULL;
        list->front = node;
        list->back = list->front;

        return 0;
    }

    node->back = NULL;
    node->next = list->back;
    list->back->prev = node;

    //изменение размера списка (почему нельзя сделать через к-во ячеек?)
    list->size+=sizeof(struct node_t);

    return 0;

}
int list_contains_node (struct list_t* list, struct node_t* node){
    struct node_t* top = list->front;
    while (top != NULL)
    {
        if (top->key_pointer==node->keypointer){
            return 1;
        }
        top = top->next;
    }
    return 0;
}

int list_remove (struct list_t* list, struct node_t* node, struct node_t** disp){
    //проверяем, содержится ли node в list
    if(list_contains_node(struct list_t* list, struct node_t* node)){
        if(node->key_pointer->next!=NULL && node->key_pointer->prev!=NULL){
            node->key_pointer->next->prev = node->key_pointer->prev;
            node->key_pointer->prev->next = node->key_pointer->next;
        }
        else if(node->key_pointer->next==NULL){
            node->key_pointer->prev->next = NULL;
        }
        else if(node->key_pointer->prev==NULL){
            node->key_pointer->next->prev = NULL;
        }
        &disp = key_pointer;
        return 0;
    }
    return 1;
}

void list_apply_func (struct list_t* list, void (*func)(struct node_t*)){
    struct node_t* top = list->front;
    while (top != NULL)
    {
        func(top);
        top = top->next;
    }
}

void list_apply_func_reverse (struct list_t* list, void (*func)(struct node_t*)){
    struct node_t* back = list->back;
    while (back != NULL)
    {
        func(back);
        back = back->prev;
    }
}

void print_node (struct node_t* node){
    printf("\n { \n key_pointer: %d \n data: %d \n page: %d \n next: %d; prev: %d ", (int)(node->key_pointer)%1000, (nodea->data), (node->page),(int)(node->next)%1000,(int)(node->prev)%1000);
}

void free_node (struct node_t* node){
    free(node);
}

void list_free (struct list_t* list){
    struct node_t* top = list->front;
    struct node_t* tmp = NULL;
    while (top != NULL)
    {
        tmp = top->next;
        free_node(top);
        top = tmp;
    }
    free(list);   
}

int list_move_front (struct list_t* list, struct node_t* node){
    if(list_contains_node(struct list_t* list, struct node_t* node)){
        struct node_t* tmp = list->front;
        list->front = node;
        node->prev = NULL;
        node->next = tmp;
        tmp->prev = node;
        return 1;
    }
    return 0;
}

//0 если пуст, 1 - не пуст
int list_is_empty (struct list_t* list){

    // ! если список NULL, то он считается некорректным
    assert( list );
    assert( size_conformity(list) );

    if(list->size==0){
        return 0;
    }

    return 1;
}

//функция-дополнение к list_is_empty, проверяет соответствие параметра size 
//и структуры в смысле наличия 
int size_conformity(struct list_t* list){
    if((list->front != NULL || list->back != NULL)  && list->size == 0){
        return 0;
    }
    if((list->front == NULL || list->back == NULL)  && list->size != 0){
        return 0;
    }
    if(list->size < 0){
        return 0;
    }
    return 1;

}