/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** string_utils
*/

#include "client.h"

char * event_already_exist(char * line, account_t * account, char ** tab)
{
    char * new_line = strdup(line);

    client_error_already_exist();
    return new_line;
}