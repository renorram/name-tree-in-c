//
// Created by renorram on 27/09/2019.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef NAMELIST_READER_H
#define NAMELIST_READER_H

#define READER_LINE_MAX 30

char ** reader_get_file_lines(const char * file_path)
{
    FILE * file = fopen(file_path, "r");
    char **lines = malloc(sizeof(char*) * 153);
    char * buffer = malloc(sizeof(char) * READER_LINE_MAX);
    int counter = 0;

    while (!feof(file)) {
        fgets(buffer, READER_LINE_MAX, file);
        *(lines + counter) = malloc(sizeof(char) * strlen(buffer));
        strcpy( *(lines + counter), buffer);
        counter++;
    }
    printf("linhas %d\n",counter);


    fclose(file);

    return lines;
}

#endif //NAMELIST_READER_H
