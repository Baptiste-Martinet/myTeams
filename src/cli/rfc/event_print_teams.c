/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** string_utils
*/

#include "client.h"

static void add_user_to_newline(char * user_id, char * name, char * co, \
char ** new_line)
{
    size_t size = 40 + strlen(user_id) + strlen(name) + strlen(co) + \
((*new_line == NULL) ? 0 : strlen(*new_line));
    char * warning = NULL;

    if (*new_line == NULL) {
        *new_line = malloc(sizeof(char) * (size + strlen("Teams :\n")));
        sprintf(*new_line, "Teams :\n");
    } else
        *new_line = realloc(*new_line, size);
    warning = strdup(*new_line);
    sprintf(*new_line, "%sTeam %s [%s] : %s\n", warning, name, user_id, co);
    free(warning);
}

char * event_print_teams(char * line, account_t * account, char ** tab)
{
    char * new_line = NULL;
    char * params[3] = {NULL, NULL, NULL};

    for (int user = 0; tab != NULL && tab[(user * 3)] != NULL; ++user) {
        params[0] = tab[user * 3];
        params[1] = tab[(user * 3) + 1];
        params[2] = tab[(user * 3) + 2];
        client_print_teams(params[0], params[1], params[2]);
        add_user_to_newline(params[0], params[1], params[2], &new_line);
    }
    (new_line == NULL) ? new_line = strdup("No teams.") : 0;
    return new_line;
}