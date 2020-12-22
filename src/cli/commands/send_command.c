/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** string_utils
*/

#include "client.h"

static const command_parse_t commands[] = { \
{"login", &send_login}, \
{"logout", &send_logout}, \
{"users", &send_users}, \
{"user", &send_user}, \
{"send", &send_send}, \
{"messages", &send_messages}, \
{"subscribe", &send_subscribe}, \
{"subscribed", &send_subscribed}, \
{"unsubscribe", &send_unsubscribe}, \
{"use", &send_use}, \
{"create", &send_create}, \
{"list", &send_list}, \
{"info", &send_info}, \
{"NULL", NULL}\
};

static int parse_commands(char ** parameter, account_t * account)
{
    int i = 0;

    for (; commands[i].ptr != NULL; ++i) {
        if (strcmp(commands[i].title, parameter[0]) == 0) {
            commands[i].ptr(parameter, account->distant_fd);
            (i == 0 && ptr_number((void **)parameter) >= 2) ? \
account->username = strdup(parameter[1]) : 0;
            break;
        }
    }
    return EXIT_SUCCESS;
}

int send_command(char * line, account_t * account)
{
    char ** parameter = treat_arguments(line);

    if (ptr_number((void **)parameter) != 1 && \
verify_arguments(line) == EXIT_FAILURE) {
        free_2darray((void **)parameter);
        return EXIT_SUCCESS;
    }
    if (parse_commands(parameter, account) == EXIT_FAILURE) {
        free_2darray((void **)parameter);
        return EXIT_FAILURE;
    }
    free_2darray((void **)parameter);
    return EXIT_SUCCESS;
}