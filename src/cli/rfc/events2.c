/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** string_utils
*/

#include "client.h"

char * event_no_event(char * line, account_t * account, char ** tab)
{
    char * new_line = strdup(line);

    return new_line;
}

char * event_loggedout(char * line, account_t * account, char ** tab)
{
    char * user_id = tab[0];
    char * user_name = tab[1];
    char * new_line = malloc(strlen(line) + 20);

    client_event_loggedout(user_id, user_name);
    sprintf(new_line, "%s has disconnected !", line);
    return new_line;
}

char * event_mp_received(char * line, account_t * account, char ** tab)
{
    const char * name = tab[0];
    const char * user_id = tab[1];
    const char * message = tab[2];
    char * new_line = malloc(sizeof(char) * + strlen(user_id) +\
(1 + strlen(name) + strlen(message)));

    client_event_private_message_received(user_id, message);
    sprintf(new_line, "%s whispers: %s", name, message);
    return new_line;
}