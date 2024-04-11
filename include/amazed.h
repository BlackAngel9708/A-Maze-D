/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** amazed.h
*/

#ifndef AMAZED_H_
    #define AMAZED_H_
    #include <stddef.h>

typedef struct info {
    char **rooms_name;
    char *start_name;
    char *end_name;
    int start;
    int end;
    size_t i;
    size_t size_initial;
    size_t size_final;
    int nb_robots;
    int robots;
    int rooms;
    int link;
    int nb_rooms;
} info_t;

int amazed(void);

#endif
