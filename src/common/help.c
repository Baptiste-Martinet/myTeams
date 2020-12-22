/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** string_utils
*/

#include "common.h"

char *load_file_in_mem(char const *filepath)
{
    struct stat *statbuff = malloc(sizeof(struct stat));
    int size = 0;
    char *buffer = 0;
    int fd;

    stat(filepath, statbuff);
    size = statbuff->st_size;
    buffer = malloc(sizeof(char) * (size + 1));
    fd = open(filepath, O_RDONLY);
    if (read(fd, buffer, size) == (-1))
        return (NULL);
    buffer[size] = 0;
    free(statbuff);
    close(fd);
    return (buffer);
}

static void help_message(const char * path)
{
    char * msg = load_file_in_mem(path);

    printf("%s\n", msg);
    free(msg);
}

int help(int ac, char ** av, const char * help_msg_path, int supposed_arg)
{
    if (ac == supposed_arg)
        return EXIT_SUCCESS;
    help_message(help_msg_path);
    return EXIT_FAILURE;
}