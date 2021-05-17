#include "../include/qlist.h"
#include <string.h>
#include <time.h>

void test01(){
    struct list_t* list = list_init(5);
    struct node_t* node1 = pregen_node(1, 1);
    struct node_t* node2 = pregen_node(1, 1);
    struct node_t* disp = malloc(sizeof(struct list_t));

    assert(disp);

    list_push_back(list, node1, &disp);
    if(list_is_empty(list)==1){
        printf("Test01 - OK\n");
    }
    else{
        printf("Test01 - ERR\n");
    }

    free(disp);
    list_free(list);
    free_node(node2);
}

void test02(){
    struct list_t* list = list_init(3);
    struct node_t* node1 = pregen_node(1, 1);
    struct node_t* node2 = pregen_node(1, 1);
    struct node_t* node3 = pregen_node(1, 1);
    struct node_t* node4 = pregen_node(1, 1);
    struct node_t* node5 = pregen_node(1, 1);
    struct node_t* disp = malloc(sizeof(struct list_t));

    assert(disp);

    list_push_back(list, node1, &disp);
    list_push_back(list, node2, &disp);
    list_push_back(list, node3, &disp);
    list_push_back(list, node4, &disp);
    list_push_back(list, node5, &disp);
    if(list_is_empty(list)==1 && list_cursize(list)==list_maxsize(list)){
        printf("Test02 - OK\n");
    }
    else{
        printf("Test02 - ERR\n");
    }

    free(disp);
    list_free(list);

}

void test03(){
    struct list_t* list = list_init(5);
    struct node_t* node1 = pregen_node(1, 1);
    struct node_t* node2 = pregen_node(2, 2);
    struct node_t* disp = malloc(sizeof(struct list_t));

    assert(disp);

    list_push_back(list, node1, &disp);
    list_push_front(list, node2, &disp);
    if(list_is_empty(list)==1 && list->front->data==2 && list->back->data==1){
        printf("Test03 - OK\n");
    }
    else{
        printf("Test03 - ERR\n");
    }

    free(disp);
    list_free(list);
}

void test04(){
    struct list_t* list = list_init(5);
    struct node_t* node1 = pregen_node(1, 1);
    struct node_t* node2 = pregen_node(2, 2);
    struct node_t* node3 = pregen_node(3, 3);
    struct node_t* disp = malloc(sizeof(struct list_t));

    assert(disp);

    list_push_front(list, node1, &disp);
    list_push_front(list, node2, &disp);
    list_push_front(list, node3, &disp);
    list_remove(list, node3, &disp);
    if(list_is_empty(list)==1 && list->front->data==2){
        printf("Test04 - OK\n");
    }
    else{
        printf("Test04 - ERR\n");
    }

    free(disp);
    list_free(list);
}

void test05(){
    struct list_t* list = list_init(5);
    struct node_t* node1 = pregen_node(1, 1);
    struct node_t* node2 = pregen_node(2, 2);
    struct node_t* node3 = pregen_node(3, 3);
    struct node_t* node4 = pregen_node(4, 4);
    struct node_t* node5 = pregen_node(5, 5);
    struct node_t* node6 = pregen_node(6, 6);
    struct node_t* disp1 = malloc(sizeof(struct list_t));
    struct node_t* disp2 = malloc(sizeof(struct list_t));

    assert(disp1);
    assert(disp2);

    list_push_front(list, node1, &disp1);
    list_push_front(list, node2, &disp1);
    list_push_front(list, node3, &disp1);
    list_push_front(list, node4, &disp1);
    list_push_front(list, node5, &disp1);
    list_push_front(list, node6, &disp1);
    free(disp1);
    list_remove (list, node5, &disp2);
    //printf("%d %d\n", list->front->data, list->back->data);
    if(list_is_empty(list)==1 && list->front->data==6 && list->back->data==2  && list_cursize(list)==4){
        printf("Test05 - OK\n");
    }
    else{
        printf("Test05 - ERR\n");
    }

    //free_node(node6);
    free(disp2);
    list_free(list);
}

void test06(){
    struct list_t* list = list_init(5);
    struct node_t* node1 = pregen_node(1, 1);
    struct node_t* node2 = pregen_node(2, 2);
    struct node_t* node3 = pregen_node(3, 3);
    struct node_t* node4 = pregen_node(4, 4);
    struct node_t* node5 = pregen_node(5, 5);
    struct node_t* node6 = pregen_node(6, 6);
    struct node_t* disp1 = malloc(sizeof(struct list_t));
    struct node_t* disp2 = malloc(sizeof(struct list_t));

    assert(disp1);
    assert(disp2);

    list_push_front(list, node1, &disp1);
    list_push_front(list, node2, &disp1);
    list_push_front(list, node3, &disp1);
    list_push_front(list, node4, &disp1);
    list_push_front(list, node5, &disp1);
    list_push_front(list, node6, &disp1);
    free(disp1);
    list_remove (list, node5, &disp2);
    //printf("%d %d\n", list->front->data, list->back->data);
    if(list_is_empty(list)==1 && list->front->data==6 && list->back->data==2  && list_cursize(list)==4){
        printf("Test06 - OK\nLIST:");
        list_apply_func(list, print_node);
    }
    else{
        printf("Test06 - ERR\n");
    }

    //free_node(node6);
    free(disp2);
    list_free(list);
}

int main(){
    int n = 6, i;
    void (*test []) (void) = {test01, test02, test03, test04, test05, test06};
    for(i=0; i<n; ++i){
        test[i]();
    }

    //test1();
    
    return 0;
}