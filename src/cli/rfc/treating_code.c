/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** string_utils
*/

#include "client.h"

const treat_code_t funcs[] = {\
{EVENT_LOGGEDIN, &event_loggedin}, \
{EVENT_LOGGEDOUT, &event_loggedout}, \
{EVENT_MP_RECEIVED, &event_mp_received}, \
{EVENT_THREAD_MSG_RECEIVED, &event_thread_msg_received}, \
{EVENT_PRINT_USERS, &event_print_users}, \
{EVENT_PRINT_TEAMS, &event_print_teams}, \
{EVENT_TEAM_PRINT_CHANNELS, &event_team_print_channels}, \
{EVENT_CHANNEL_PRINT_THREADS, &event_channel_print_thread}, \
{EVENT_THREAD_PRINT_REPLIES, &event_thread_print_replies}, \
{EVENT_MP_PRINT_MSG, &event_mp_print_msg}, \
{ERR_UNKNOWN_TEAM, &event_unknown_team}, \
{ERR_UNKNOWN_CHANN, &event_unknown_channel}, \
{ERR_UNKNOWN_THREAD, &event_unknown_thread}, \
{EVENT_ERROR_UNKNOWN_USER, &event_unknown_user}, \
{EVENT_ERROR_UNAUTHORIZED, &event_unauthorized}, \
{EVENT_ERROR_ALREADY_EXIST, &event_already_exist}, \
{EVENT_PRINT_USER, &event_print_user}, \
{EVENT_PRINT_TEAM, &event_print_team}, \
{EVENT_PRINT_CHANNEL, &event_print_channel}, \
{EVENT_PRINT_THREAD, &event_print_thread}, \
{EVENT_TEAM_CREATED, &event_team_created}, \
{EVENT_CHANNEL_CREATED, &event_channel_created}, \
{EVENT_THREAD_CREATED, &event_thread_created}, \
{EVENT_PRINT_TEAM_CREATED, &event_print_team_created}, \
{EVENT_PRINT_CHANNEL_CREATED, &event_print_channel_created}, \
{EVENT_PRINT_THREAD_CREATED, &event_print_thread_created}, \
{EVENT_PRINT_REPLY_CREATED, &event_print_replies_created}, \
{EVENT_PRINT_SUBSCRIBED, &event_subscribed}, \
{EVENT_PRINT_UNSUBSCRIBED, &event_unsubscribed}, \
{NO_EVENT, &event_no_event}, \
{EXIT_FAILURE, NULL}\
};

char * get_last_reponse(char * line)
{
    static char buffer[4096] = {0};
    char * temp = NULL;

    if (line == NULL) {
        temp = strdup(buffer);
        memset(buffer, 0, 4096);
        return temp;
    } else {
        memset(buffer, 0, 4096);
        strcpy(buffer, line);
        return NULL;
    }
}

void treat_code(int code, account_t * account, char * line)
{
    char ** tab = split_no_delim(line, " : ");
    char * new_line = NULL;

    for (int i = 0; funcs[i].ptr != NULL; ++i) {
        if (code == funcs[i].code) {
            new_line = funcs[i].ptr(line, account, tab);
            break;
        }
    }
    printf("[SERVER] > %s\n", new_line);
    free(new_line);
    free_2darray((void **)tab);
}