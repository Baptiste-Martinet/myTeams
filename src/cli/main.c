/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** string_utils
*/

#include "client.h"

static void signal_handler(int sig)
{
    if (sig == SIGINT) {
        stop_the_program(true);
    }
}

static int client_part(int ac, char ** av)
{
    uint16_t port = atoi(av[2]);
    char * ip = av[1];
    client_socket_t socket;

    if (strcmp(ip, "localhost") == 0)
        ip = "127.0.0.1";
    socket = create_socket(ip, port);
    if (socket.error)
        return EXIT_FAILURE;
    client_loop(socket.distant_fd);
    close_socket(&socket);
    return EXIT_SUCCESS;
}

int main(int ac, char ** av)
{
    signal(SIGINT, signal_handler);
    more_pipe(5);
    if (help(ac, av, "./src/cli/help_msg", 3) == EXIT_FAILURE)
        return EXIT_SUCCESS;
    return client_part(ac, av);
}