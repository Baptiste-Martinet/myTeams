/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** string_utils
*/

#include "client.h"

static const command_id_t commands[] = {\
{"help", &help_command}, \
{"login", &send_command}, \
{"logout", &send_command}, \
{"users", &send_command}, \
{"user", &send_command}, \
{"send", &send_command}, \
{"messages", &send_command}, \
{"subscribe", &send_command}, \
{"subscribed", &send_command}, \
{"unsubscribe", &send_command}, \
{"use", &send_command}, \
{"create", &send_command}, \
{"list", &send_command}, \
{"info", &send_command}, \
{"NULL", NULL}\
};

static int unknown_comm(void)
{
    printf("Unknown Command.\n");
    return UNKNOWN_COMMAND;
}

static int identify_command(char * line, account_t * account)
{
    char ** parameters = NULL;
    int ret = EXIT_SUCCESS;

    if (line[0] != '/')
        return unknown_comm();
    ++line;
    parameters = treat_arguments(line);
    for (int i = 0; commands[i].func != NULL; ++i) {
        if (strcmp(parameters[0], commands[i].title) == 0) {
            ret = commands[i].func(line, account);
            free_2darray((void **)parameters);
            account->last_fd_read = STDIN_FD;
            return ret;
        }
    }
    free_2darray((void **)parameters);
    return unknown_comm();
}

static int split_command(char * line, account_t * account)
{
    char ** tab_check = split(line, "\n");
    char ** tab = split_no_delim(line, "\n");
    int ret = EXIT_SUCCESS;

    if (tab == NULL || tab_check == NULL)
        return ret;
    for (int i = 0; tab[i] != NULL; ++i) {
        if ((!ends_with(tab_check[i], "\n") && tab[i + 1] != NULL) || \
(tab[i + 1] == NULL && line[strlen(line) - 1] != '\n')) {
            stock_rest(tab_check, i, account);
            break;
        }
        if ((ret = identify_command(tab[i], account)) != EXIT_SUCCESS)
            break;
    }
    free_2darray((void **)tab);
    free_2darray((void **)tab_check);
    return ret;
}

int check_command(char * line, account_t * account)
{
    while (line[0] <= 32 || line[0] >= 127) {
        if (line[0] == 0)
            return UNKNOWN_COMMAND;
        ++line;
    }
    if (contains(line, "\n") == 0) {
        account->old_buffer = strdup(line);
        return EXIT_SUCCESS;
    }
    return split_command(line, account);
}