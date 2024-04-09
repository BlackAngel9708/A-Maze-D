/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** create_list.c
*/

#include "map.h"
#include <stdlib.h>
#include <stdio.h>

map_t *create_map(void)
{
    map_t *map = malloc(sizeof(map_t));

    if (map == NULL)
        return NULL;
    map->name = NULL;
    map->link = NULL;
    map->next = NULL;
    return map;
}
