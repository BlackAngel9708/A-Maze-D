/*
** EPITECH PROJECT, 2024
** Amazed
** File description:
** Pathfinding algorithme
*/

#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "algorithme/bfs.h"
#include "my_alloc.h"
#include "amazed.h"
#include "map.h"
#include "my_macros.h"
#include "my.h"
#include "my_types.h"

static
void initialize_shortest_path(char const *end_room,
    encountered_room_t *visited, shortest_path_t *shortest_path)
{
    while (visited != NULL) {
        if (visited->map == NULL) {
            visited = visited->next;
            continue;
        }
        if (my_strcmp(end_room, visited->map->name) == 0
            && shortest_path->room == NULL) {
            shortest_path->room = visited->map;
            visited->map = NULL;
            break;
        }
        visited = visited->next;
    }
}

static
int add_previous_room(encountered_room_t *visited,
    shortest_path_t **shortest_path, int index)
{
    encountered_room_t *tmp = NULL;

    if (visited->map == (*shortest_path)->room->link[index]) {
        (*shortest_path)->next = malloc(sizeof(shortest_path_t));
        if ((*shortest_path)->next == NULL)
            return FAILURE;
        (*shortest_path) = (*shortest_path)->next;
        (*shortest_path)->room = visited->map;
        (*shortest_path)->next = NULL;
        visited->map = (visited->next == NULL) ? NULL : visited->next->map;
        tmp = visited->next;
        visited->next = (visited->next == NULL) ? NULL : visited->next->next;
        if (tmp != NULL)
            free(tmp);
    }
    return SUCCESS;
}

static
int check_already_visited(encountered_room_t *visited,
    shortest_path_t *shortest_path)
{
    if (visited == NULL || visited->map == NULL || shortest_path == NULL)
        return TRUE;
    while (shortest_path != NULL) {
        if (shortest_path->room == NULL) {
            shortest_path = shortest_path->next;
            continue;
        }
        if (my_strcmp(shortest_path->room->name, visited->map->name) == 0)
            return TRUE;
        shortest_path = shortest_path->next;
    }
    return FALSE;
}

static
shortest_path_t *parse_shortest_path_link(shortest_path_t *shortest_path,
    encountered_room_t *visited, char const *start_room, int const index)
{
    shortest_path_t *shortest_path_head = shortest_path;

    while (visited != NULL) {
        if (visited->map == NULL
            || check_already_visited(visited, shortest_path_head) == TRUE) {
            visited = visited->next;
            break;
        }
        if (add_previous_room(visited, &shortest_path, index) == FAILURE)
            return NULL;
        if (my_strcmp(shortest_path->room->name, start_room) == 0)
            return shortest_path_head;
        visited = visited->next;
    }
    return shortest_path_head;
}

shortest_path_t *retrieve_bfs_shortest_path(char const *start_room,
    char const *end_room, encountered_room_t *visited)
{
    shortest_path_t *shortest_path = malloc(sizeof(shortest_path_t));
    shortest_path_t *shortest_path_head = shortest_path;
    encountered_room_t *visited_head = visited;

    if (shortest_path == NULL)
        return NULL;
    initialize_shortest_path(end_room, visited, shortest_path);
    visited = visited_head;
    if (shortest_path->room == NULL || shortest_path->room->link == NULL) {
        display_error("Algorith couldn't find the end_room\n");
        return free(shortest_path), NULL;
    }
    while (shortest_path != NULL) {
        if (my_strcmp(shortest_path->room->name, start_room) == 0)
            return shortest_path_head;
        for (size_t i = 0; shortest_path->room->link[i] != NULL; i += 1)
            parse_shortest_path_link(shortest_path, visited, start_room, i);
        shortest_path = shortest_path->next;
    }
    return shortest_path_head;
}
