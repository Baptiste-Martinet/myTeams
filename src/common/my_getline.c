/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** string_utils
*/

#include "common.h"

static int exit_here(char ** line)
{
    if (*line != NULL)
        free(*line);
    *line = NULL;
    return -1;
}

static void * first_malloc(char ** line, int total_red, char ** old_buffer)
{
    if (*old_buffer != NULL) {
        *line = *old_buffer;
        *old_buffer = NULL;
        return *line;
    }
    if (*line != NULL)
        return *line;
    if ((*line = malloc(total_red)) == NULL)
        return NULL;
    memset(*line, 0, total_red);
    return *line;
}

int my_getline2(char ** line, int fd)
{
    char buffer[BUFFER_SIZE] = {0};
    int red = 0;
    int total_red = (*line == NULL) ? 0 : strlen(*line);

    memset(buffer, 0, BUFFER_SIZE);
    if ((red = read(fd, buffer, BUFFER_SIZE - 1)) < 0)
        return exit_here(line);
    if (red == 0)
        return 0;
    total_red += red;
    if ((*line = realloc(*line, total_red + 1)) == NULL)
        return exit_here(line);
    strcat(*line, buffer);
    return total_red;
}

int my_getline(char ** line, int fd, char ** old_buffer)
{
    int ret = 1;

    if (*line == NULL && first_malloc(line, 1, old_buffer) == NULL)
        return -1;
    if ((ret = my_getline2(line, fd)) < 0)
        return -1;
    if (ret == 0)
        return 0;
    return 1;
}