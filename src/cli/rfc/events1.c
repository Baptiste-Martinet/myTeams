/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** string_utils
*/

#include "client.h"

char * event_loggedin(char * line, account_t * account, char ** tab)
{
    char * user_id = tab[0];
    char * user_name = tab[1];
    char * new_line = malloc(sizeof(char) * (1 + strlen(user_name) + \
strlen(" is logged on the server !")));

    client_event_loggedin(user_id, user_name);
    sprintf(new_line, "%s is logged on the server !", user_name);
    return new_line;
}

static void add_user_to_newline(char * user_id, char * name, int co, \
char ** new_line)
{
    size_t size = 21 + strlen(user_id) + strlen(name) + \
((*new_line == NULL) ? 0 : strlen(*new_line));
    char * warning = NULL;

    if (*new_line == NULL) {
        *new_line = malloc(sizeof(char) * (size + strlen("Users :\n")));
        sprintf(*new_line, "Users :\n");
    } else
        *new_line = realloc(*new_line, size);
    warning = strdup(*new_line);
    sprintf(*new_line, "%s%s\t[%s]:\t%sConnected.\n", \
warning, name, user_id, ((co == 1) ? "" : "Not "));
    free(warning);
}

char * event_print_users(char * line, account_t * account, char ** tab)
{
    char * new_line = NULL;
    char * user_id = NULL;
    char * name = NULL;
    char * connected = NULL;

    for (int user = 0; tab != NULL && tab[(user * 3)] != NULL; ++user) {
        user_id = tab[user * 3];
        name = tab[(user * 3) + 1];
        connected = tab[(user * 3) + 2];
        if (user_id == NULL || name == NULL || connected == NULL)
            break;
        client_print_users(user_id, name, atoi(connected));
        add_user_to_newline(user_id, name, atoi(connected), &new_line);
    }
    (new_line == NULL) ? new_line = strdup("No users.") : 0;
    return new_line;
}