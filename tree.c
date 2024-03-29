//
// Created by renorram on 17/09/2019.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"

#define NAME_MAX_SIZE 31

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

void tree_strcpy(char *dest, const char *source) {
    int i, x;
    char c;

    for (i = 0, x = 0; (c = *(source + i)); i++) {
        if (c != '\n') {
            dest[x] = c;
            x++;
        }
    }
    dest[x] = '\0';
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

void tree_clean(Tree *t) {
    tree_destroy_recursive(t->root);
    t->root = NULL;
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
        root = cmp_holder > 0 ? root->left : root->right;
    }

    root = malloc(sizeof(No));
    root->info = malloc(sizeof(word) * strlen(word));
    tree_strcpy(root->info, word);
    root->left = NULL;
    root->right = NULL;

    if (father == NULL) {
        t->root = root;
    } else {
        if (strcmp(father->info, word) > 0) {
            father->left = root;
        } else {
            father->right = root;
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
            root->left = tree_remove_recursive(root->left, word);
        } else {
            if (strcmp(root->info, word) < 0) {
                root->right = tree_remove_recursive(root->right, word);
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
    char * nword = malloc(sizeof(char) * strlen(word));
    tree_strcpy(nword, word);
    t->root = tree_remove_recursive(t->root, nword);
    free(nword);
}

void tree_print_by_substring_recursive(No *root, const char *substring) {
    if (root != NULL) {
        tree_print_by_substring_recursive(root->left, substring);
        tree_print_by_substring_recursive(root->right, substring);
        if (strstr(root->info, substring) != NULL) {
            printf(" %s ", root->info);
        }
    }
}

void tree_print_by_substring(Tree *t, const char *substring) {
    char * nword = malloc(sizeof(char) * strlen(substring));
    tree_strcpy(nword, substring);
    tree_print_by_substring_recursive(t->root, nword);
    free(nword);
}

No *tree_remove_bigger_substring_recursive(No *root, const char *substring) {
    if (root != NULL) {
        int cmp_holder = strcmp(root->info, substring);
        if (cmp_holder == 0) {
            tree_destroy_recursive(root->right);
            root->right = NULL;
        } else if (cmp_holder > 0) {
            No *aux = root->left;
            tree_destroy_recursive(root->right);
            root = tree_remove_bigger_substring_recursive(aux, substring);
        } else {
            root->right = tree_remove_bigger_substring_recursive(root->right, substring);
        }
    }

    return root;
}

void tree_remove_bigger_substring(Tree *t, const char *substring) {
    char * nword = malloc(sizeof(char) * strlen(substring));
    tree_strcpy(nword, substring);
    t->root = tree_remove_bigger_substring_recursive(t->root, nword);
    free(nword);
}

No *tree_remove_smaller_substring_recursive(No *root, const char *substring) {
    if (root != NULL) {
        int cmp_holder = strcmp(root->info, substring);
        if (cmp_holder == 0) {
            tree_destroy_recursive(root->left);
            root->left = NULL;
        } else if (cmp_holder < 0) {
            No *aux = root->right;
            tree_destroy_recursive(root->left);
            root = tree_remove_smaller_substring_recursive(aux, substring);
        } else {
            root->left = tree_remove_smaller_substring_recursive(root->left, substring);
        }
    }

    return root;
}

void tree_remove_smaller_substring(Tree *t, const char *substring) {
    char * nword = malloc(sizeof(char) * strlen(substring));
    tree_strcpy(nword, substring);
    t->root = tree_remove_smaller_substring_recursive(t->root, nword);
    free(nword);
}

void tree_print_recursive(No *root) {
    if (root != NULL) {
        tree_print_recursive(root->left);
        printf("\t%s\n", root->info);
        tree_print_recursive(root->right);
    }
}

void tree_print(Tree *t) {
    printf("******\tImprimindo\t******\n");
    tree_print_recursive(t->root);
    printf("**************************\n");
}

int tree_count_nodes_recursive(No *root) {
    if (root != NULL) {
        int right = tree_count_nodes_recursive(root->right);
        int left = tree_count_nodes_recursive(root->left);

        return right + left + 1;
    }

    return 0;
}

int tree_count_nodes(Tree *t) {
    return tree_count_nodes_recursive(t->root);
}

void tree_as_string_vector_recursive(No *root, char **string_vector, int *counter) {
    if (root != NULL) {
        tree_as_string_vector_recursive(root->left, string_vector, counter);

        *(string_vector + *(counter)) = malloc(sizeof(char) * strlen(root->info));
        strcpy(*(string_vector + *(counter)), root->info);
        *counter = *(counter) + 1;

        tree_as_string_vector_recursive(root->right, string_vector, counter);
    }
}

char **tree_as_string_vector(Tree *t) {
    int node_count = tree_count_nodes(t);
    char **strings = malloc(sizeof(char *) * node_count * NAME_MAX_SIZE);
    int  i = 0;
    tree_as_string_vector_recursive(t->root, strings, &i);

    return strings;
}
