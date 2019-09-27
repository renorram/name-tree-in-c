//
// Created by renorram on 17/09/2019.
//
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main(void) {
    Tree * t = tree_create();
    tree_insert(t, "beto");
    tree_insert(t, "ana");
    tree_insert(t, "joão");
    tree_insert(t, "carlos");
    tree_insert(t, "charlos");
    tree_print(t);
    tree_destroy(t);
    return 0;
}
