/*
** EPITECH PROJECT, 2024
** amazd
** File description:
** handle_errors.c
*/

#include "my_macros.h"
#include "map.h"
#include "my.h"
#include "amazed.h"
#include "linked_list.h"
#include <stdio.h>

static int check_nb_robots(char **instruction, info_t *info)
{
    char *str = "#number_of_robots\n";

    if (instruction[0] == NULL || info == NULL)
        return FAILURE;
    if (my_str_isnum(instruction[0]) == 0) {
        return FAILURE;
    }
    info->nb_robots = my_getnbr(instruction[0]);
    if (info->nb_robots <= 0)
        return FAILURE;
    write(1, str, my_strlen(str));
    write(1, instruction[0], my_strlen(instruction[0]));
    write(1, "\n", 1);
    return SUCCESS;
}

int handle_robots_rooms(map_t *map, char **instruction, info_t *info)
{
    if (instruction == NULL)
        return EPITECH_FAILURE;
    if (check_nb_robots(instruction, info) == FAILURE)
        return FAILURE;
    for (int i = 1; instruction[i] != NULL && info->rooms != TRUE; i += 1)
        if (adding_rooms(map, instruction[i], info) == FAILURE)
            return FAILURE;
    return SUCCESS;
}
