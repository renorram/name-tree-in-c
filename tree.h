//
// Created by renorram on 17/09/2019.
//

#ifndef NAMELIST_TREE_H
#define NAMELIST_TREE_H

typedef struct tree Tree;

Tree * tree_create();
void tree_destroy(Tree * t);
void tree_insert(Tree * t, const char * word);

#endif //NAMELIST_TREE_H
