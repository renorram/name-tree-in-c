//
// Created by renorram on 17/09/2019.
//
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main(void) {
//    char *ret = strstr("carlos", "lo");
//    if (ret == NULL) {
//        printf("Return is NULL\n");
//    } else {
//        printf("Return is %s\n", ret);
//    }
//    exit(0);
    Tree * t = tree_create();
    char * c = "beto";
//    tree_insert(t, "beto");
    tree_insert(t, c);
    tree_insert(t, "ana");
    tree_insert(t, "joão");
    tree_insert(t, "carlos");
    tree_insert(t, "charlos");
    tree_print(t);

    tree_remove_by_substring(t, "arl");
    tree_print(t);

//    tree_remove(t, "joão");
//    tree_print(t);
//    tree_remove(t, "beto");
//    tree_print(t);

    tree_destroy(t);
//    printf("Return is %s\n", ret);
    return 0;
}
