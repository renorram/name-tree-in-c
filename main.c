//
// Created by renorram on 17/09/2019.
//
#include <string.h>
#include <stdio.h>
#include "tree.h"

int main(void) {
//    char *ret = strstr("carlos", "fadsfiadsfj123123");
//    if (ret == NULL) {
//        printf("Return is NULL\n");
//    } else {
//        printf("Return is %s\n", ret);
//    }
    Tree * t = tree_create();
    char * c = "beto";
//    tree_insert(t, "beto");
    tree_insert(t, c);
    tree_insert(t, "ana");
    tree_insert(t, "joão");
    tree_insert(t, "carlos");
    tree_print(t);

    tree_remove(t, "joão");
    tree_print(t);
    tree_remove(t, "beto");
    tree_print(t);

    tree_destroy(t);
//    printf("Return is %s\n", ret);
    return 0;
}
