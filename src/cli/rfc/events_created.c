/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** string_utils
*/

#include "client.h"

char * event_print_team_created(char * line, account_t * account, char ** tab)
{
    char * new_line = NULL;

    client_print_team_created(tab[0], tab[1], tab[2]);
    new_line = malloc(50 + strlen(tab[0]) + strlen(tab[1]) + strlen(tab[2]));
    sprintf(new_line, "Created Team %s [%s]: %s.", tab[1], tab[0], tab[2]);
    return new_line;
}

char * event_print_channel_created(char * li, account_t * account, char ** tab)
{
    char * new_line = NULL;

    client_print_channel_created(tab[0], tab[1], tab[2]);
    new_line = malloc(50 + strlen(tab[0]) + strlen(tab[1]) + strlen(tab[2]));
    sprintf(new_line, "Created Channel %s [%s]: %s.", tab[1], tab[0], tab[2]);
    return new_line;
}

char * event_print_thread_created(char * lie, account_t * account, char ** tab)
{
    char * new_line = NULL;

    client_print_thread_created(tab[0], tab[1], string_to_time_t(tab[2]), \
tab[3], tab[4]);
    new_line = malloc(50 + strlen(tab[0]) + strlen(tab[1]) + strlen(tab[2]) \
+ strlen(tab[3]) + strlen(tab[4]));
    sprintf(new_line, "Created Thread %s [%s] by %s at [%s] : %s", \
tab[3], tab[0], tab[1], tab[2], tab[4]);
    return new_line;
}

char * event_print_replies_created(char * lin, account_t * account, char ** tab)
{
    char * new_line = NULL;

    client_print_reply_created(tab[0], tab[1], string_to_time_t(tab[2]), \
tab[3]);
    new_line = malloc(50 + strlen(tab[0]) + strlen(tab[1]) + strlen(tab[2]) \
+ strlen(tab[3]));
    sprintf(new_line, "Created Reply [%s] by %s at [%s] : %s", \
tab[0], tab[1], tab[2], tab[3]);
    return new_line;
}