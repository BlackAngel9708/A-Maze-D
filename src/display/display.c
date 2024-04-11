/*
** EPITECH PROJECT, 2024
** Amazed
** File description:
** Display the moves of the robot
*/

#include "algorithme/bfs.h"
#include "my_macros.h"
#include "my.h"

int display_shortest_path(shortest_path_t *shortest_path, info_t *info)
{
    shortest_path_t *robot_room = NULL;
    int robot_finished = 0;

    while (shortest_path != NULL) {
        if (shortest_path->room == NULL)
            return FAILURE;
        if (my_strcmp(shortest_path->room->name, info->start_name) == 0) {
            shortest_path = shortest_path->next;
            break;
        }
        shortest_path = shortest_path->next;
    }
    if (shortest_path == NULL || shortest_path->room == NULL || info == NULL)
        return FAILURE;
    while (robot_finished < info->nb_robots && shortest_path != NULL) {
        robot_room = shortest_path;
        for (int current_robot = robot_finished + 1; current_robot <= info->nb_rooms; current_robot += 1) {
            if (current_robot > robot_finished + 1)
                my_putchar(' ');
            my_putstr("P");
            my_put_nbr(current_robot);
            my_putstr("-");
            my_putstr(robot_room->room->name);
            if (robot_room->previous == NULL
                || my_strcmp(robot_room->previous->room->name, info->start_name) == 0) {
                    break;
            }
            robot_room = robot_room->previous;
        }
        my_putchar('\n');
        robot_finished += 1;
        shortest_path = shortest_path->next;
    }
    return SUCCESS;
}
