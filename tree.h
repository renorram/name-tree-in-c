//
// Created by renorram on 17/09/2019.
//

#ifndef NAMELIST_TREE_H
#define NAMELIST_TREE_H

typedef struct tree Tree;

Tree * tree_create();
void tree_destroy(Tree * t);
void tree_insert(Tree * t, const char * word);
void tree_remove(Tree *t, const char * word);
void tree_print_by_substring(Tree * t, const char * substring);
void tree_remove_bigger_substring(Tree * t, const char * substring);
void tree_remove_smaller_substring(Tree * t, const char * substring);
void tree_print(Tree * t);

#endif //NAMELIST_TREE_H
