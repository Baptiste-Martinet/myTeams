/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** string_utils
*/

#include "client.h"

static int exit_here(char * line)
{
    free(line);
    return EXIT_FAILURE;
}

static void remove_rn(char * total_buffer)
{
    while (ends_with(total_buffer, CRLF)) {
        total_buffer[strlen(total_buffer) - 1] = 0;
        total_buffer[strlen(total_buffer) - 1] = 0;
    }
}

int read_server(int distand_fd, account_t * account)
{
    char buffer[BUFFER_SIZE] = {0};
    char * total_buffer = malloc(1);
    size_t total_size = 0;
    ssize_t ret = BUFFER_SIZE;

    total_buffer[0] = 0;
    while (ret > 0 && !ends_with(total_buffer, CRLF)) {
        memset(buffer, 0, BUFFER_SIZE);
        if ((ret = read(distand_fd, buffer, BUFFER_SIZE)) <= 0)
            return exit_here(total_buffer);
        total_size += ret;
        if ((total_buffer = realloc(total_buffer, total_size + 1)) == NULL)
            return exit_here(total_buffer);
        strcat(total_buffer, buffer);
    }
    remove_rn(total_buffer);
    if (rfc_loop(total_buffer, account) == EXIT_FAILURE)
        return exit_here(total_buffer);
    free(total_buffer);
    return EXIT_SUCCESS;
}