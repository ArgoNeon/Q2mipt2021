#include "../include/qlist.h"


struct list_t* list_init (int maxsize){

    void* key_pointer;
    struct list_t* list;

    //maxsize здесь личный параметр списка
    //список создаётся пустым

    assert(maxsize>=0);

    list = (struct list_t*)malloc(sizeof(struct list_t));
    key_pointer = calloc (1,sizeof(char));

    assert(list);
    assert(key_pointer);

    list->maxsize = maxsize;
    list->size = 0;
    list->front = NULL;
    list->back = NULL;
    list->key_pointer = key_pointer;

    return list;
}

struct node_t* pregen_node (int page, int data){
    struct node_t* node = (struct node_t*)calloc(1, sizeof(struct node_t));

    assert(node);

    node->page = page;
    node->data = data;

    node->key_pointer = NULL;
    node->next = NULL;
    node->prev = NULL;

    return node;
}

int list_push_back (struct list_t* list, struct node_t* node, struct node_t** disp){

    if(node==NULL){
        printf("Пришёл некорректный node = NULL");
        return 1;
    }

    //если не влезает, направляем на node disp
    if(list->size+1>list->maxsize){
        *disp = node;

        return 0;
    }
    node->key_pointer = list->key_pointer;
    if (list_is_empty(list)==0){
        node->next = NULL;
        node->prev = NULL;
        list->front = node;
        list->back = list->front;

        return 0;
    }

    node->next = NULL;
    node->prev = list->back;
    list->back = node;

    //изменение размера списка 
    list->size+=1;

    return 0;
}

int list_push_front (struct list_t* list, struct node_t* node, struct node_t** disp){

    if(node==NULL){
        printf("Пришёл некорректный node = NULL");
        return 1;
    }

    //если не влезает, направляем на node disp
    if(list->size+1>list->maxsize){
        *disp = node;

        return 0;
    }
    node->key_pointer = list->key_pointer;
    if (list_is_empty(list)==0){
        node->next = NULL;
        node->prev = NULL;
        list->front = node;
        list->back = list->front;

        return 0;
    }

    node->prev = NULL;
    node->next = list->front;
    list->front = node;

    //изменение размера списка 
    list->size+=1;

    return 0;
}


int list_contains_node (struct list_t* list, struct node_t* node){
    if(node->key_pointer==list->key_pointer){
        return 1;
    }
    return 0;
}

int list_remove (struct list_t* list, struct node_t* node, struct node_t** disp){
    //проверяем, содержится ли node в list
    if(list_contains_node(list, node)){
        if(node->next!=NULL && node->prev!=NULL){
            node->next->prev = node->prev;
            node->prev->next = node->next;
        }
        else if(node->next==NULL){
            node->prev->next = NULL;
        }
        else if(node->prev==NULL){
            node->next->prev = NULL;
        }

        *disp = node;

        //изменение размера списка 
        list->size-=1;

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
    while (back != NULL){
        func(back);
        back = back->prev;
    }
}

void print_node (struct node_t* node){
    //printf("\n { \n key_pointer: %d \n data: %d \n page: %d \n next: %d; prev: %d ", (int)(node->key_pointer)%1000, (node->data), (node->page),(int)(node->next)%1000,(int)(node->prev)%1000);
    printf("\n { \n data: %d \n page: %d ", (node->data), (node->page));
}

void free_node (struct node_t* node){
    free(node);
}

void list_free (struct list_t* list){
    struct node_t* top = list->front;
    struct node_t* tmp = NULL;
    while (top != NULL){
        tmp = top->next;
        free_node(top);
        top = tmp;
    }
    free(list);   
}

int list_cursize (struct list_t* list){
    return list->size;
}

int list_maxsize (struct list_t* list){
    return list->maxsize;
}

int list_move_front (struct list_t* list, struct node_t* node){
    if(list_contains_node(list, node)){
        struct node_t* tmp = list->front;
        list->front = node;
        node->prev = NULL;
        node->next = tmp;
        tmp->prev = node;
        return 1;
    }
    return 0;
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

