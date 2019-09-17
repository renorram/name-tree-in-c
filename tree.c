//
// Created by renorram on 17/09/2019.
//
#include <stdlib.h>
#include <string.h>
#include "tree.h"

typedef struct no No;

struct tree {
    No *root;
};

struct no {
    char *info;
    No *right;
    No *left;
};

Tree *tree_create() {
    Tree *t = malloc(sizeof(Tree));
    t->root = NULL;

    return t;
}

void tree_destroy_recursive(No *root) {
    if (root != NULL) {
        tree_destroy_recursive(root->right);
        tree_destroy_recursive(root->left);
        free(root);
    }
}

void tree_destroy(Tree *t) {
    tree_destroy_recursive(t->root);
    free(t);
}

void tree_insert(Tree *t, const char *word) {
    No *root = t->root, *father = NULL;
    int cmp_holder;

    while (root != NULL) {
        cmp_holder = strcmp(root->info, word);
        if (cmp_holder == 0) {
            return;
        }

        father = root;
        root = cmp_holder > 0 ? root->right : root->left;
    }

    root = malloc(sizeof(No));
    root->info = malloc(sizeof(word) * strlen(word));
    strcpy(root->info, word);
    root->left = NULL;
    root->right = NULL;

    if (father == NULL) {
        t->root = root;
    } else {
        if (strcmp(father->info, word) > 0) {
            father->right = root;
        } else {
            father->left = root;
        }
    }
}
