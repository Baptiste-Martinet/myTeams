/*
** EPITECH PROJECT, 2020
** main.c
** File description:
** server main
*/

#include "server.h"

static void signal_handler(int sig)
{
    if (sig == SIGINT) {
        stop_the_program(true);
    }
}

int main(int ac, char ** av)
{
    signal(SIGINT, signal_handler);
    if (help(ac, av, "./src/server/help_msg", 2) == EXIT_FAILURE)
        return EXIT_SUCCESS;
    return (start_server(atoi(av[1])));
}