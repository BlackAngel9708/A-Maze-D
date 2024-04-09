/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** link_handling.c
*/

#include "my_macros.h"
#include "map.h"
#include "my.h"
#include <stdio.h>

static int retrieve_len_link(char **link, size_t *len)
{
    if (link == NULL)
        return FAILURE;
    for (size_t i = 0; link[i] != NULL; i += 1)
        *len += 1;
    return SUCCESS;
}

static int find_link(char *instruction)
{
    char **link = 0;
    size_t len = 0;

    if (instruction == NULL)
        return FAILURE;
    link = my_str_to_word_array(instruction, " ");
    if (retrieve_len_link(link, &len) == FAILURE)
        return FAILURE;
    if (len == 1 && my_strncmp(instruction, "#", 1) != 0)
        return 1;
    return SUCCESS;
}

static int find_len_first_link(map_t *map)
{
    size_t len = 0;

    if (map->link == NULL)
        return 0;
    for (size_t i = 0; map->link[i] != NULL; i += 1)
        len += 1;
    return len;
}

static int find_second_room(map_t *map, map_t *head, char **arr)
{
    size_t size_initial = find_len_first_link(map);

    while (head != NULL) {
        if (my_strcmp(head->name, arr[1]) == 0) {
            map->link = my_realloc(map->link, size_initial *
                sizeof(map_t), (size_initial + 2) * sizeof(map_t));
            map->link[size_initial] = head;
            map->link[size_initial + 1] = NULL;
        }
        head = head->next;
    }
    return SUCCESS;
}

static int assign_first_link(map_t *map, map_t *head, char **arr)
{
    if (my_strcmp(map->name, arr[0]) == SUCCESS)
        find_second_room(map, head, arr);
    return SUCCESS;
}

static int find_second_room_other_link(map_t *map, map_t *head, char **arr)
{
    size_t size_initial = find_len_first_link(map);

    while (head != NULL) {
        if (my_strcmp(head->name, arr[0]) == 0) {
            map->link = my_realloc(map->link, size_initial *
                sizeof(map_t), (size_initial + 2) * sizeof(map_t));
            map->link[size_initial] = head;
            map->link[size_initial + 1] = NULL;
        }
        head = head->next;
    }
    return SUCCESS;
}

static int assign_second_link(map_t *map, map_t *head, char **arr)
{
    if (my_strcmp(map->name, arr[1]) == SUCCESS)
        find_second_room_other_link(map, head, arr);
    return SUCCESS;
}

static int retrieve_link(map_t *map, char *link)
{
    char **arr = NULL;
    map_t *head = map;

    if (link == NULL)
        return FAILURE;
    arr = my_str_to_word_array(link, "-");
    if (arr == NULL || arr[0] == NULL || arr[1] == NULL)
        return FAILURE;
    while (map != NULL) {
        if (my_strcmp(map->name, arr[0]) == SUCCESS)
            assign_first_link(map, head, arr);
        if (my_strcmp(map->name, arr[1]) == SUCCESS)
            assign_second_link(map, head, arr);
        map = map->next;
    }
    return SUCCESS;
}

int handle_link(map_t *map, char **instruction)
{
    size_t beginning = 0;

    if (map == NULL || instruction == NULL)
        return FAILURE;
    for (size_t i = 1; instruction[i] != NULL; i += 1)
        if (find_link(instruction[i]) == 1) {
            beginning = i;
            break;
        }
    if (beginning == 0)
        return FAILURE;
    for (size_t i = beginning; instruction[i] != NULL; i += 1)
        retrieve_link(map, instruction[i]);
    write(1, "#tunnels\n", my_strlen("#tunnels\n"));
    for (size_t i = beginning; instruction[i] != NULL; i += 1) {
        write(1, instruction[i], my_strlen(instruction[i]));
        write(1, "\n", 1);
    }
    return SUCCESS;
}
