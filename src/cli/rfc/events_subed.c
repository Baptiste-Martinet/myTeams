/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** string_utils
*/

#include "client.h"

static void add_user_to_newline(char * name, char * timee, char ** new_line)
{
    size_t size = 40 + strlen(name) + strlen(timee) + \
((*new_line == NULL) ? 0 : strlen(*new_line));
    char * warning = NULL;

    if (*new_line == NULL) {
        *new_line = malloc(sizeof(char) * (size + \
strlen("Subscribed teams :\n")));
        sprintf(*new_line, "Subscribed teams :\n");
    } else
        *new_line = realloc(*new_line, size);
    warning = strdup(*new_line);
    sprintf(*new_line, "%sTeam %s [%s]\n", warning, timee, name);
    free(warning);
}

char * event_subscribed(char * line, account_t * account, char ** tab)
{
    char * new_line = NULL;
    char * params[2] = {NULL, NULL};

    for (int user = 0; tab != NULL && tab[(user * 2)] != NULL; ++user) {
        params[0] = tab[user * 2];
        params[1] = tab[(user * 2) + 1];
        client_print_subscribed(params[0], params[1]);
        add_user_to_newline(params[0], params[1], &new_line);
    }
    (new_line == NULL) ? new_line = strdup("No replies.") : 0;
    return new_line;
}

char * event_unsubscribed(char * line, account_t * account, char ** tab)
{
    char * new_line = NULL;

    client_print_unsubscribed(tab[0], tab[1]);
    new_line = malloc(50 + strlen(tab[0]) + strlen(tab[1]));
    sprintf(new_line, "Unsubscribed from team : %s [%s]", tab[0], tab[1]);
    return new_line;
}