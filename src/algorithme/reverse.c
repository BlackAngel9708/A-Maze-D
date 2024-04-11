/*
** EPITECH PROJECT, 2024
** Amazed
** File description:
** Reverse the linked list given by the shortest path
*/
/*
** EPITECH PROJECT, 2023
** Reverse
** File description:
** Reverse function for the organized workshop
*/

#include <stddef.h>
#include "my_macros.h"
#include "my.h"
#include "algorithme/bfs.h"

shortest_path_t *reverse_list(shortest_path_t *list)
{
    shortest_path_t *tmp = NULL;
    shortest_path_t *head = NULL;

    if (list == NULL)
        return NULL;
    while (list != NULL) {
        head = list;
        tmp = list->next;
        list->next = list->previous;
        list->previous = tmp;
        list = list->previous;
    }
    return head;
}
