//
// Created by renorram on 27/09/2019.
//

#ifndef NAMELIST_READER_H
#define NAMELIST_READER_H

#define READER_LINE_MAX 31

char **reader_get_file_lines(const char *file_path);

void reader_str_tolower(char *str);

void reader_free_string_vector(char ** vector);

#endif //NAMELIST_READER_H
