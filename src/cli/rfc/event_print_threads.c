/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** string_utils
*/

#include "client.h"

static void add_user_to_newline(char * name, char * msg, char ** new_line)
{
    size_t size = 40 + strlen(msg) + strlen(name) + \
((*new_line == NULL) ? 0 : strlen(*new_line));
    char * warning = NULL;

    if (*new_line == NULL) {
        *new_line = malloc(sizeof(char) * (size + strlen("Threads :\n")));
        sprintf(*new_line, "Threads :\n");
    } else
        *new_line = realloc(*new_line, size);
    warning = strdup(*new_line);
    sprintf(*new_line, "%sThread %s : %s\n", warning, name, msg);
    free(warning);
}

char * event_channel_print_thread(char * line, account_t * account, char ** tab)
{
    char * new_line = NULL;
    char * params[5] = {NULL, NULL, NULL, NULL, NULL};

    for (int user = 0; tab != NULL && tab[(user * 5)] != NULL; ++user) {
        params[0] = tab[user * 5];
        params[1] = tab[(user * 5) + 1];
        params[2] = tab[(user * 5) + 2];
        params[3] = tab[(user * 5) + 3];
        params[4] = tab[(user * 5) + 4];
        client_channel_print_threads(params[0], params[1], \
string_to_time_t(params[2]), params[3], params[4]);
        add_user_to_newline(params[3], params[4], &new_line);
    }
    (new_line == NULL) ? new_line = strdup("No threads.") : 0;
    return new_line;
}