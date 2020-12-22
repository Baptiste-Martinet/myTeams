/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** string_utils
*/

#include "client.h"

static void add_user_to_newline(char * name, char * timee, char * msg, \
char ** new_line)
{
    size_t size = 40 + strlen(msg) + strlen(name) + strlen(timee) + \
((*new_line == NULL) ? 0 : strlen(*new_line));
    char * warning = NULL;

    if (*new_line == NULL) {
        *new_line = malloc(sizeof(char) * (size + strlen("Replies :\n")));
        sprintf(*new_line, "Replies :\n");
    } else
        *new_line = realloc(*new_line, size);
    warning = strdup(*new_line);
    sprintf(*new_line, "%s[%s] Reply from [%s]: %s\n", warning, timee, \
name, msg);
    free(warning);
}

char * event_thread_print_replies(char * line, account_t * account, char ** tab)
{
    char * new_line = NULL;
    char * params[4] = {NULL, NULL, NULL, NULL};

    for (int user = 0; tab != NULL && tab[(user * 4)] != NULL; ++user) {
        params[0] = tab[user * 4];
        params[1] = tab[(user * 4) + 1];
        params[2] = tab[(user * 4) + 2];
        params[3] = tab[(user * 4) + 3];
        client_thread_print_replies(params[0], params[1], \
string_to_time_t(params[2]), params[3]);
        add_user_to_newline(params[0], params[2], params[3], &new_line);
    }
    (new_line == NULL) ? new_line = strdup("No replies.") : 0;
    return new_line;
}