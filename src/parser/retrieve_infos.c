/*
** EPITECH PROJECT, 2024
** Amazed
** File description:
** Retrieve the user inputs to build the maze
*/

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include "my_macros.h"
#include "my_types.h"
#include "my.h"

static void assign_value(char **arr, char **buf, size_t *k)
{
    if (arr[(*k)][my_strlen(arr[(*k)]) - 1] == '\n')
        arr[(*k)][my_strlen(arr[(*k)]) - 1] = '\0';
    (*k) += 1;
    (*buf) = NULL;
}

static char **retrieve_map(void)
{
    char *buf = NULL;
    char **arr = NULL;
    size_t size_initial = 0;
    size_t size = 0;
    size_t size_final = 0;
    size_t k = 0;

    while (getline(&buf, &size, stdin) > 0) {
        size_final += 8;
        arr = my_realloc(arr, size_initial, size_final);
        size_initial = size_final;
        arr[k] = buf;
        assign_value(arr, &buf, &k);
    }
    arr = my_realloc(arr, size_initial, size_final + 8);
    arr[k] = NULL;
    if (buf != NULL)
        free(buf);
    return arr;
}

char **retrieve_info(void)
{
    char **map = retrieve_map();

    return map;
}
