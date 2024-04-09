/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** amazed
*/

#include "algorithme/bfs.h"
#include "retrieve_infos.h"
#include "my_macros.h"
#include "parser.h"
#include "map.h"
#include "linked_list.h"
#include "amazed.h"
#include "my.h"
#include <stdio.h>
#include <stdlib.h>

static
int display_shortest_path(shortest_path_t *shortest_path)
{
    if (shortest_path == NULL || shortest_path->room == NULL)
        return FAILURE;
    display_shortest_path(shortest_path->next);
    my_putstr(shortest_path->room->name);
    my_putchar('\n');
    return SUCCESS;
}

int amazed(void)
{
    map_t *map = create_map();
    shortest_path_t *shortest_path = NULL;
    info_t *info = malloc(sizeof(info_t));
    char **instruction = parse_map(map, info);

    if (instruction == NULL)
        return EPITECH_FAILURE;
    if (get_shortest_path(map, info, &shortest_path) == FAILURE)
        return EPITECH_FAILURE;
    display_shortest_path(shortest_path);
    return SUCCESS;
}
