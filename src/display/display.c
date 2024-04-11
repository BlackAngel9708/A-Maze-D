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
    shortest_path_t *robot_rooms[info->nb_robots + 1];
    int robot_finished = 0;
    int line_print = 0;

    for (int i = 0; i <= info->nb_robots; i += 1)
        robot_rooms[i] = NULL;
    robot_rooms[0] = shortest_path;
    while (robot_finished < info->nb_robots) {
        for (int current_robot = 0; current_robot < info->nb_robots; current_robot += 1) {
            if (robot_rooms[current_robot] == NULL)
                continue;
            if (my_strcmp(robot_rooms[current_robot]->room->name, info->start_name) != 0) {
                if (line_print == TRUE)
                    my_putchar(' ');
                line_print = TRUE;
                my_putstr("P");
                my_put_nbr(current_robot + 1);
                my_putstr("-");
                my_putstr(robot_rooms[current_robot]->room->name);
                robot_rooms[current_robot + 1] = robot_rooms[current_robot]->previous;
            }
            if (my_strcmp(robot_rooms[current_robot]->room->name, info->end_name) == 0) {
                robot_finished += 1;
            }
            robot_rooms[current_robot] = robot_rooms[current_robot]->next;
        }
        if (line_print == TRUE)
            my_putchar('\n');
        line_print = FALSE;
    }
    return SUCCESS;
}
