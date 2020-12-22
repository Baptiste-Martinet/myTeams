/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** string_utils
*/

#include "client.h"

char * event_unknown_team(char * line, account_t * account, char ** tab)
{
    const char * user_id = tab[0];
    char * new_line = malloc(sizeof(char) * strlen(user_id) + 50);
    client_error_unknown_team(user_id);
    sprintf(new_line, "Wrong Command : [%s] Team UUID is unknown.", user_id);
    return new_line;
}

char * event_unknown_channel(char * line, account_t * account, char ** tab)
{
    const char * user_id = tab[0];
    char * new_line = malloc(sizeof(char) * strlen(user_id) + 50);
    client_error_unknown_channel(user_id);
    sprintf(new_line, "Wrong Command : [%s] Channel UUID is unknown.", user_id);
    return new_line;
}

char * event_unknown_thread(char * line, account_t * account, char ** tab)
{
    const char * user_id = tab[0];
    char * new_line = malloc(sizeof(char) * strlen(user_id) + 50);
    client_error_unknown_thread(user_id);
    sprintf(new_line, "Wrong Command : [%s] Thread UUID is unknown.", user_id);
    return new_line;
}

char * event_unknown_user(char * line, account_t * account, char ** tab)
{
    const char * user_id = tab[0];
    char * new_line = malloc(sizeof(char) * strlen(user_id) + 50);
    client_error_unknown_user(user_id);
    sprintf(new_line, "Wrong Command : [%s] User UUID is unknown.", user_id);
    return new_line;
}

char * event_unauthorized(char * line, account_t * account, char ** tab)
{
    char * new_line = malloc(sizeof(char) * strlen(line) + 50);
    client_error_unauthorized();
    sprintf(new_line, "Unauthorized Command : %s", line);
    return new_line;
}