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
int check_visited(map_t const *map, encountered_room_t *visited)
{
    if (map == NULL) {
        display_error("Unable to check map\n");
        return FALSE;
    }
    if (visited == NULL) {
        display_error("Unable to check visited\n");
        return FALSE;
    }
    while (visited != NULL) {
        if (my_strcmp(visited->map->name, map->name) == 0)
            return TRUE;
        visited = visited->next;
    }
    return FALSE;
}

static
int add_visited_room(encountered_room_t *visited, map_t *current_room)
{
    if (visited == NULL || current_room == NULL) {
        return display_error("Unable to retrieve the visited room\n");
    }
    if (visited->map == NULL) {
        visited->map = current_room;
        visited->next = NULL;
        return FAILURE;
    }
    while (visited->next != NULL) {
        visited = visited->next;
    }
    visited->next = malloc(sizeof(encountered_room_t));
    if (visited->next == NULL)
        return display_error("Unable to add visited room\n");
    visited->next->map = current_room;
    visited->next->next = NULL;
    return SUCCESS;
}

static
int add_room_to_queue(room_queue_t *queue, map_t *room)
{
    if (queue == NULL)
        return display_error("Unable to load queue\n");
    while (queue->next != NULL)
        queue = queue->next;
    queue->next = malloc(sizeof(room_queue_t));
    if (queue->next == NULL)
        return display_error("Unable to add another room to queue\n");
    queue->next->map = room;
    queue->next->next = NULL;
    return SUCCESS;
}

static
int check_linked_room(room_queue_t *queue,
    encountered_room_t *visited, char const *end_room)
{
    for (size_t i = 0; queue->map->link[i] != NULL; i += 1) {
        if (check_visited(queue->map->link[i], visited) == TRUE)
            continue;
        add_visited_room(visited, queue->map->link[i]);
        if (my_strcmp(queue->map->link[i]->name, end_room) == 0)
            return SUCCESS;
        add_room_to_queue(queue, queue->map->link[i]);
    }
    return FAILURE;
}

static
int execute_bfs(encountered_room_t *visited, room_queue_t *queue,
    info_t *info, shortest_path_t **shortest_path)
{
    if (queue == NULL || queue->map == NULL || queue->map->name == NULL
        || queue->map->link == NULL || visited == NULL || info == NULL)
        return display_error("Unable to access the room info\n");
    while (queue != NULL) {
        if (check_linked_room(queue, visited, info->end_name) == SUCCESS)
            break;
        queue = queue->next;
    }
    *shortest_path = retrieve_bfs_shortest_path(info->start_name,
        info->end_name, visited);
    return SUCCESS;
}

static
map_t *retrieve_first_map(map_t *map, info_t *info)
{
    while (map != NULL) {
        if (my_strcmp(map->name, info->start_name) == 0)
            return map;
        map = map->next;
    }
    return NULL;
}

int get_shortest_path(map_t *map, info_t *info,
    shortest_path_t **shortest_path)
{
    encountered_room_t *visited = NULL;
    room_queue_t *queue = NULL;

    if (info == NULL || map == NULL)
        return display_error("Struct null for algorithme\n");
    visited = malloc(sizeof(encountered_room_t));
    if (visited == NULL)
        return display_error("Unable to allocate visited memory\n");
    queue = malloc(sizeof(room_queue_t));
    if (queue == NULL) {
        free(visited);
        return display_error("Unable to allocate queue memory\n");
    }
    queue->map = retrieve_first_map(map, info);
    queue->next = NULL;
    visited->map = queue->map;
    visited->next = NULL;
    return execute_bfs(visited, queue, info, shortest_path);
}
