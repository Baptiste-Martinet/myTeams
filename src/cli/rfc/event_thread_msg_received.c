/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** string_utils
*/

#include "client.h"

char * event_thread_msg_received(char * line, account_t * account, char ** tab)
{
    const char * team_name = tab[0];
    const char * thread_name = tab[1];
    const char * user_name = tab[2];
    const char * team_id = tab[3];
    const char * thread_id = tab[4];
    const char * user_id = tab[5];
    const char * msg = tab[6];
    char * new_line = malloc(sizeof(char) * (1 + strlen(team_name) + \
strlen(thread_name) + strlen(user_name) + strlen(team_id) + strlen(thread_id) \
+ strlen(user_id) + strlen(msg) + 90));

    client_event_thread_message_received(team_id, thread_id, user_id, msg);
    sprintf(new_line, "Thread Message Received :\nTeam %s [%s]:\n\t"\
"Thread %s [%s]:\n\t\t%s [%s] said: %s\n", team_name, team_id, \
thread_name, thread_id, user_name, user_id, msg);
    return new_line;
}