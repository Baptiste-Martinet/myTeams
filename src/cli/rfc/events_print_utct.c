/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** string_utils
*/

#include "client.h"

char * event_print_user(char * line, account_t * account, char ** tab)
{
    char * new_line = NULL;

    client_print_user(tab[0], tab[1], atoi(tab[2]));
    new_line = malloc(50 + strlen(tab[0]) + strlen(tab[1]) + strlen(tab[2]));
    sprintf(new_line, "User %s [%s]: %s.", tab[1], tab[0], \
((atoi(tab[2]) == 1) ? "Connected" : "Not connected"));
    return new_line;
}

char * event_print_team(char * line, account_t * account, char ** tab)
{
    char * new_line = NULL;

    client_print_team(tab[0], tab[1], tab[2]);
    new_line = malloc(50 + strlen(tab[0]) + strlen(tab[1]) + strlen(tab[2]));
    sprintf(new_line, "Team %s [%s]: %s.", tab[1], tab[0], tab[2]);
    return new_line;
}

char * event_print_channel(char * line, account_t * account, char ** tab)
{
    char * new_line = NULL;

    client_print_channel(tab[0], tab[1], tab[2]);
    new_line = malloc(50 + strlen(tab[0]) + strlen(tab[1]) + strlen(tab[2]));
    sprintf(new_line, "Channel %s [%s]: %s.", tab[1], tab[0], tab[2]);
    return new_line;
}

char * event_print_thread(char * line, account_t * account, char ** tab)
{
    char * new_line = NULL;

    client_print_thread(tab[0], tab[1], string_to_time_t(tab[2]), tab[3], \
tab[4]);
    new_line = malloc(50 + strlen(tab[0]) + strlen(tab[1]) + strlen(tab[2]) \
+ strlen(tab[3]) + strlen(tab[4]));
    sprintf(new_line, "Thread %s [%s] created by %s at [%s] : %s", \
tab[3], tab[0], tab[1], tab[2], tab[4]);
    return new_line;
}