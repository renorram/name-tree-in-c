//
// Created by renorram on 04/10/2019.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "utils.h"

#ifdef _WIN32
#include <windows.h>
#include <tchar.h>

// @todo
char * get_current_dir()
{
   perror("get current dir not implemented");
}

#endif

#ifdef __linux__
#include <unistd.h>

char *get_current_dir() {
    long path_max;
    size_t size;
    char *buffer;

    path_max = pathconf(".", _PC_PATH_MAX);
    size = path_max == -1 ? 1024 :
           (path_max > 10240 ? 10240 : path_max);

    for (buffer = NULL; buffer == NULL; size *= 2) {
        if ((buffer = realloc(buffer, size)) == NULL) {
            perror("get current dir error on getcwd");
            exit(errno);
        }


        getcwd(buffer, size);
        if (buffer == NULL && errno != ERANGE) {
            continue;
        }
    }

    return buffer;
}
#endif

char * get_file_path_on_curr_dir(const char * path)
{
    char * full_path = get_current_dir(),
    *tmp = realloc(full_path, sizeof(char) * (strlen(full_path) + strlen(path) + 2));

    if (tmp != NULL) {
        full_path = tmp;
    } else {
        exit(errno);
    }

    strcat(full_path, "/");
    strcat(full_path, path);

    return full_path;
}