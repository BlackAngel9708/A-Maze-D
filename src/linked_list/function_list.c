/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** function_list.c
*/

#include "map.h"
#include "my_macros.h"
#include "my.h"
#include "amazed.h"
#include "comment_handling.h"
#include "coordinate_handling.h"
#include "link_handling.h"
#include <stdlib.h>

static int check_link(char **room, size_t *i, size_t *j, int **link)
{
    if (room[*i][*j] == '-') {
        **link = TRUE;
    }
    return SUCCESS;
}

static int find_link(char **room, int *link)
{
    for (size_t i = 0; room[i] != NULL; i += 1)
        for (size_t j = 0; room[i][j] != '\0'; j += 1)
            check_link(room, &i, &j, &link);
    return SUCCESS;
}

static int handle_room(char **room, info_t *info)
{
    size_t i = 0;
    int link = FALSE;

    for (size_t j = 0; room[j] != NULL; j += 1) {
        i += 1;
    }
    if (i == 1) {
        find_link(room, &link);
        if (link == TRUE) {
            info->rooms = TRUE;
            return SUCCESS;
        }
    }
    if (i != 3)
        return FAILURE;
    return SUCCESS;
}

static int check_same_name(info_t *info, size_t i)
{
    for (size_t j = i + 1; info->rooms_name[j] != NULL; j += 1) {
        if (my_strcmp(info->rooms_name[i], info->rooms_name[j]) == 0) {
            return FAILURE;
        }
    }
    return SUCCESS;
}

static int print_rooms(char *instruction, info_t *info)
{
    if (info->rooms_name == NULL)
        return FAILURE;
    for (size_t i = 0; info->rooms_name[i] != NULL; i += 1) {
        if (check_same_name(info, i) == FAILURE)
            return FAILURE;
    }
    if (info->rooms != TRUE) {
        if (info->nb_rooms == 1)
            write(1, "#rooms\n", my_strlen("#rooms\n"));
        write(1, instruction, my_strlen(instruction));
        write(1, "\n", 1);
    }
    return SUCCESS;
}

static void handle_first_room(map_t *map, info_t *info, char **room)
{
    if (map == NULL || info == NULL || room == NULL || room[0] == NULL)
        return;
    map->name = room[0];
    info->rooms_name = my_realloc(info->rooms_name,
        info->size_initial, info->size_final);
    info->size_initial = info->size_final;
    info->size_final += 8;
    info->rooms_name[info->i] = my_strdup(room[0]);
    info->i += 1;
    info->rooms_name[info->i] = NULL;
    map->link = malloc(sizeof(map_t));
    map->link[0] = NULL;
    map->x = my_strdup(room[1]);
    map->y = my_strdup(room[2]);
}

static
void handle_other_rooms(map_t *map, info_t *info, map_t *tmp, char **room)
{
    map->next = tmp;
    tmp->name = my_strdup(room[0]);
    info->rooms_name = my_realloc(info->rooms_name,
        info->size_initial, info->size_final);
    info->size_initial = info->size_final;
    info->size_final += 8;
    info->rooms_name[info->i] = my_strdup(room[0]);
    info->i += 1;
    info->rooms_name[info->i] = NULL;
    tmp->link = malloc(sizeof(map_t));
    tmp->link[0] = NULL;
    tmp->x = my_strdup(room[1]);
    tmp->y = my_strdup(room[2]);
    tmp->next = NULL;
}

static int retrieve_room(char **room, map_t *map, info_t *info)
{
    map_t *tmp = malloc(sizeof(map_t));

    if (room == NULL || *room == NULL || map == NULL ||
        room[1] == NULL || room[2] == NULL)
        return FAILURE;
    if (info->nb_rooms == 1) {
        handle_first_room(map, info, room);
        if (tmp != NULL)
            free(tmp);
        return SUCCESS;
    }
    while (map->next != NULL)
        map = map->next;
    handle_other_rooms(map, info, tmp, room);
    return SUCCESS;
}

static int handle_start_end(info_t *info, char **room)
{
    if (info == NULL || room == NULL || room[0] == NULL)
        return FAILURE;
    if (info->start == TRUE) {
        info->start_name = my_strdup(room[0]);
        info->start += 1;
        return SUCCESS;
    }
    if (info->end == TRUE) {
        info->end_name = my_strdup(room[0]);
        info->end += 1;
        return SUCCESS;
    }
    return SUCCESS;
}

int adding_rooms(map_t *map, char *instruction, info_t *info)
{
    char **room = NULL;
    size_t error = 0;

    if (map == NULL || instruction == NULL)
        return FAILURE;
    if (handle_comment(instruction, info, &error) == 1)
        return SUCCESS;
    if (error != 0)
        return FAILURE;
    room = my_str_to_word_array(instruction, " ");
    if (handle_room(room, info) == FAILURE ||
        handle_coordinate(room) == FAILURE)
        return FAILURE;
    handle_start_end(info, room);
    info->nb_rooms += 1;
    if (info->rooms != TRUE)
        retrieve_room(room, map, info);
    if (print_rooms(instruction, info) == FAILURE)
        return FAILURE;
    return SUCCESS;
}
