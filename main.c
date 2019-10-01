//
// Created by renorram on 17/09/2019.
//
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "reader.h"
#include "name_tree.h"

int main(void) {
//    const char * file_path = "/home/renorram/Documentos/tramped2/resources/names.txt";
    const char * file_path = "/mnt/c/Users/1611331/Documents/tramped2/resources/names.txt";
    const char * file_path2 = "/mnt/c/Users/1611331/Documents/tramped2/resources/names2.txt";
    Tree * t = tree_create();

    name_tree_load_from_file(file_path, t);
//    tree_as_string_vector(t);
    tree_remove(t, "yuri");
    name_tree_save_to_file(file_path2, t);
//    tree_insert(t, "beto");
//    tree_insert(t, "ana");
//    tree_insert(t, "joão");
//    tree_insert(t, "carlos");
//    tree_insert(t, "charlos");
//    tree_print(t);
    tree_destroy(t);
    return 0;
}
