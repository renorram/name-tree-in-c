//
// Created by renorram on 01/10/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "reader.h"
#include "tree.h"
#include "name_tree.h"

void name_tree_load_from_file(const char *file_path, Tree *tree) {
    tree_clean(tree);
    char **lines = reader_get_file_lines(file_path);
    int i;
    char *string;

    if (lines == NULL) {
        free(lines);
        perror("None lines were read, file is empty.");
        exit(1);
    }

    for (i = 0; (string = *(lines + i)); i++) {
        tree_insert(tree, string);
    }

    reader_free_string_vector(lines);
}

void name_tree_save_to_file(const char *file_path, Tree *tree) {
    FILE *file = fopen(file_path, "w");

    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir arquivo: %s\n", strerror(errno));
        exit(errno);
    }

    char **strings = tree_as_string_vector(tree);
    int str_counter = 0, total = tree_count_nodes(tree);
    char * aux = malloc(sizeof(char) * strlen(*(strings + str_counter)) + 1);
    strcpy(aux, *(strings + str_counter));
    strcat(aux, "\n");

    fwrite(aux, sizeof(char), strlen(aux), file);
    str_counter++;

    file = freopen(file_path, "a", file);

    for (;*(strings + str_counter) && str_counter < total;str_counter++) {
        aux = realloc(aux, sizeof(char) * strlen(*(strings + str_counter)) + 1);
        strcpy(aux, *(strings + str_counter));
        strcat(aux, "\n");
        fwrite(aux, sizeof(char), strlen(aux), file);
    }

    fclose(file);
}
