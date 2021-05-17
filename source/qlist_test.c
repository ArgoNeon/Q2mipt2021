#include "../include/qlist.h"
#include <string.h>
#include <time.h>

void test1(){
    struct list_t* list = list_init(5);
    struct node_t* node1 = pregen_node(1, 1);
    struct node_t* node2 = pregen_node(1, 1);
    struct node_t* disp = malloc(sizeof(struct list_t));
    list_push_back(list, node1, &disp);
    if(list_is_empty(list)==1){
        printf("Normal");
    }
    else{
        printf("Error");
    }
}

int main(){
    test1();

    return 0;
}