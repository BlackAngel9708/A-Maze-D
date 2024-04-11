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
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static
void destroy_map(map_t *map)
{
    if (map == NULL)
        return;
    destroy_map(map->next);
    if (map->link != NULL) {
        free(map->link);
    }
    if (map->name != NULL)
        free(map->name);
    free(map);
}

static
void destroy_shortest_path(shortest_path_t *shortest_path)
{
    if (shortest_path == NULL)
        return;
    destroy_shortest_path(shortest_path->next);
    free(shortest_path);
}

static
void destroy_info(info_t *info)
{
    if (info == NULL)
        return;
    if (info->end_name != NULL)
        free(info->end_name);
    if (info->start_name != NULL)
        free(info->start_name);
    if (info->rooms_name != NULL) {
        for (size_t i = 0; info->rooms_name[i] != NULL; i += 1) {
            free(info->rooms_name[i]);
        }
        free(info->rooms_name);
    }
    free(info);
}

static
void destroy_instructions(char **instructions)
{
    if (instructions == NULL)
        return;
    for (size_t i = 0; instructions[i] != NULL; i += 1) {
        free(instructions[i]);
    }
    free(instructions);
}

static
void destroy_end(map_t *map, shortest_path_t *shortest_path,
    info_t *info, char **instructions)
{
    if (map != NULL)
        destroy_map(map);
    if (shortest_path != NULL)
        destroy_shortest_path(shortest_path);
    if (info != NULL)
        destroy_info(info);
    if (instructions != NULL)
        destroy_instructions(instructions);
}

static
int display_shortest_path(shortest_path_t *shortest_path, int nb_robots)
{
    if (shortest_path == NULL || shortest_path->room == NULL)
        return FAILURE;
    if (shortest_path->next == NULL)
        return FAILURE;
    display_shortest_path(shortest_path->next, nb_robots);
    for (int i = 1; i <= nb_robots; i += 1) {
        if (i > 1)
            my_putchar(' ');
        my_putstr("P");
        my_put_nbr(i);
        my_putstr("-");
        my_putstr(shortest_path->room->name);
    }
    my_putchar('\n');
    return SUCCESS;
}

int amazed(void)
{
    map_t *map = create_map();
    shortest_path_t *shortest_path = NULL;
    info_t *info = malloc(sizeof(info_t));
    char **instruction = parse_map(map, info);

    if (instruction == NULL || info == NULL)
        return EPITECH_FAILURE;
    if (get_shortest_path(map, info, &shortest_path) == FAILURE)
        return EPITECH_FAILURE;
    my_putstr("#moves\n");
    display_shortest_path(shortest_path, info->nb_robots);
    destroy_end(map, shortest_path, info, instruction);
    return SUCCESS;
}
