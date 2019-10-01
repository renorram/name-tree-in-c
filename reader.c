//
// Created by renorram on 27/09/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "reader.h"

int reader_count_lines(FILE *file) {
    rewind(file);

    int i = 0;
    char c;
    do {
        c = (char) fgetc(file);
        if (feof(file)) {
            break;
        }

        if (c == '\n') {
            i++;
        }
    } while (1);

    // se o arquivo não terminar em \n o contador retorna errado
    if (c != '\n') {
        i++;
    }

    rewind(file);

    return i;
}

char **reader_get_file_lines(const char *file_path) {
    FILE *file = fopen(file_path, "r");

    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir arquivo: %s\n", strerror(errno));
        exit(errno);
    }

    int counter = 0, line_number = reader_count_lines(file);
    char **lines = malloc(sizeof(char *) * line_number * READER_LINE_MAX);
    char *buffer = malloc(sizeof(char) * READER_LINE_MAX);

    while (fgets(buffer, READER_LINE_MAX, file) != NULL) {
        reader_str_tolower(buffer);
        *(lines + counter) = malloc(sizeof(char) * strlen(buffer));
        strcpy(*(lines + counter), buffer);
        counter++;
    }
    free(buffer);
    fclose(file);

    return lines;
}

void reader_str_tolower(char *str) {
    while (*str != '\0') {
        *str = (char) tolower(*str);
        str++;
    }
}

void reader_free_string_vector(char ** vector)
{
    int i;
    char * string;

    for (i = 0; (string = *(vector + i)); i++) {
        free(string);
    }

    free(vector);
}