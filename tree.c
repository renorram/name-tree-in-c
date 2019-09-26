//
// Created by renorram on 17/09/2019.
//
#include <stdlib.h>
#include <stdio.h>
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

void tree_free_node(No *node) {
    free(node->info);
    free(node);
}

void tree_destroy_recursive(No *root) {
    if (root != NULL) {
        tree_destroy_recursive(root->right);
        tree_destroy_recursive(root->left);
        tree_free_node(root);
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

No *tree_remove_biggest(No *root, char **biggest) {
    if (root != NULL) {
        if (root->right != NULL) {
            root->right = tree_remove_biggest(root->right, biggest);
        } else {
            *(biggest) = root->info;
            No *aux = root;
            root = root->left;
            // não utilizei tree_free_node pois ainda vou precisar da string em root->info
            free(aux);
        }
    }

    return root;
}

No *tree_remove_recursive(No *root, const char *word) {
    if (root != NULL) {
        if (strcmp(root->info, word) > 0) {
            root->right = tree_remove_recursive(root->right, word);
        } else {
            if (strcmp(root->info, word) < 0) {
                root->left = tree_remove_recursive(root->left, word);
            } else { // ENCONTROU
                No *aux = root;
                // Folha - Grau (0)
                if (root->left == NULL && root->right == NULL) {
                    root = NULL;
                    tree_free_node(aux);
                } else {

                    // Grau (1)
                    if (root->left == NULL || root->right == NULL) {
                        root = root->left != NULL ? root->left : root->right;
                        tree_free_node(aux);
                    } else { // GRAU 2
                        char *biggest;
                        root->left = tree_remove_biggest(root->left, &biggest);
                        // remove da memoria string antiga
                        free(root->info);
                        root->info = biggest;
                    }

                }

            }
        }
    }

    return root;
}

void tree_remove(Tree *t, const char *word) {
    t->root = tree_remove_recursive(t->root, word);
}

void  tree_print_by_substring_recursive(No * root, const char * substring)
{
    if (root != NULL) {
        tree_print_by_substring_recursive(root->left, substring);
        tree_print_by_substring_recursive(root->right, substring);
        if (strstr(root->info, substring) != NULL) {
            printf(" %s ", root->info);
        }
    }
}

void tree_print_by_substring(Tree * t, const char * substring)
{
    tree_print_by_substring_recursive(t->root, substring);
}

void tree_remove_bigger_substring(Tree * t, const char * substring)
{
    if (t->root == NULL){
        return;
    }

    No * root = t->root, * aux = NULL;
    while (strcmp(root->info, substring) > 0) {
        aux = root;
        root = root->right;
    }

    if (aux == NULL) {
        t->root = root->left;
        root->left = NULL;
        tree_destroy_recursive(root);
    } else {
        tree_destroy_recursive(root->right);
        root->right = NULL;
    }

}

void tree_remove_smaller_substring(Tree * t, const char * substring);

void tree_print_recursive(No *root) {
    if (root != NULL) {
        tree_print_recursive(root->right);
        printf("\t%s\n", root->info);
        tree_print_recursive(root->left);
    }
}

void tree_print(Tree *t) {
    printf("******\tImprimindo\t******\n");
    tree_print_recursive(t->root);
    printf("**************************\n");
}
