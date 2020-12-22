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
        *new_line = malloc(sizeof(char) * (size + strlen("Messages :\n")));
        sprintf(*new_line, "Messages :\n");
    } else
        *new_line = realloc(*new_line, size);
    warning = strdup(*new_line);
    sprintf(*new_line, "%s[%s] %s [%s]", warning, co, name, user_id);
    free(warning);
}

static void add_message_to_newline(char * msg, char ** new_line)
{
    size_t size = 15 + strlen(msg) + strlen(*new_line);
    char * warning = strdup(*new_line);

    *new_line = realloc(*new_line, size);
    sprintf(*new_line, "%s whispered: %s\n", warning, msg);
    free(warning);
}

char * event_mp_print_msg(char * line, account_t * account, char ** tab)
{
    char * new_line = NULL;
    char * user_id = NULL;
    char * name = NULL;
    char * message = NULL;
    char * timee = NULL;

    for (int user = 0; tab != NULL && tab[(user * 4)] != NULL; ++user) {
        name = tab[user * 4];
        user_id = tab[(user * 4) + 1];
        timee = tab[(user * 4) + 2];
        message = tab[(user * 4) + 3];
        if (user_id == NULL || name == NULL || message == NULL)
            break;
        client_private_message_print_messages(user_id, \
string_to_time_t(timee), message);
        add_user_to_newline(user_id, name, timee, &new_line);
        add_message_to_newline(message, &new_line);
    }
    (new_line == NULL) ? new_line = strdup("No private messages.") : 0;
    return new_line;
}