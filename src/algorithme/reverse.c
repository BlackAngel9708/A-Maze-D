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

static
void increment_reverse(int *do_reverse, int *size)
{
    *do_reverse += 1;
    *size -= 1;
}

static
shortest_path_t *do_reverse_list(shortest_path_t **list, int *do_reverse)
{
    while (*do_reverse > 0) {
        *list = reverse_list(*list);
        *do_reverse -= 1;
    }
    return *list;
}

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
