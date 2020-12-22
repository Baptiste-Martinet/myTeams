/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** cmd_create_utils
*/

#include "server.h"

int add_team_helper(team_t *new_team, client_t *cli, global_t *glob)
{
    char *event = NULL;

    dprintf(cli->fd, "%d %s : %s : %s\r\n", EVENT_PRINT_TEAM_CREATED, \
new_team->base.uuid, new_team->base.name, new_team->description);
    if (!(event = malloc(snprintf(NULL, 0, "%d %s : %s : %s",
        EVENT_TEAM_CREATED, new_team->base.uuid, new_team->base.name,
        new_team->description) + 1)))
        return (EXIT_FAILURE);
    sprintf(event, "%d %s : %s : %s", EVENT_TEAM_CREATED, \
new_team->base.uuid, new_team->base.name, new_team->description);
    send_event_to_clients(event, glob, NULL);
    return (EXIT_SUCCESS);
}

int add_channel_helper(channel_t *new_channel, client_t *cli, global_t *glob)
{
    char *event = NULL;

    dprintf(cli->fd, "%d %s : %s : %s\r\n",
        EVENT_PRINT_CHANNEL_CREATED, new_channel->base.uuid,
        new_channel->base.name, new_channel->description);
    if (!(event = malloc(snprintf(NULL, 0, "%d %s : %s : %s",
        EVENT_CHANNEL_CREATED, new_channel->base.uuid,
        new_channel->base.name, new_channel->description) + 1)))
        return (EXIT_FAILURE);
    sprintf(event, "%d %s : %s : %s", EVENT_CHANNEL_CREATED,
    new_channel->base.uuid, new_channel->base.name, new_channel->description);
    send_event_to_clients(event, glob, cli->team);
    return (EXIT_SUCCESS);
}

int add_thread_helper(gthread_t *new_thread, client_t *cli, global_t *glob)
{
    char *event = NULL;

    dprintf(cli->fd, "%d %s : %s : %s : %s : %s\r\n",
        EVENT_PRINT_THREAD_CREATED, new_thread->base.uuid,
        new_thread->uuid_creator, new_thread->timestamp,
        new_thread->base.name, new_thread->message);
    if (!(event = malloc(snprintf(NULL, 0, "%d %s : %s : %s : %s : %s",
        EVENT_THREAD_CREATED, new_thread->base.uuid,
        new_thread->uuid_creator, new_thread->timestamp,
        new_thread->base.name, new_thread->message) + 1)))
        return (EXIT_FAILURE);
    sprintf(event, "%d %s : %s : %s : %s : %s", EVENT_THREAD_CREATED,
    new_thread->base.uuid, new_thread->uuid_creator, new_thread->timestamp,
    new_thread->base.name, new_thread->message);
    send_event_to_clients(event, glob, cli->team);
    return (EXIT_SUCCESS);
}

static int add_reply_helper2(client_t *cli, gthread_t *thread, \
reply_t *new_reply, global_t *glob)
{
    dprintf(cli->fd, "%d %s : %s : %s : %s\r\n", \
EVENT_PRINT_REPLY_CREATED, thread->base.uuid, \
new_reply->uuid_creator, new_reply->timestamp, \
new_reply->message);
    return (EXIT_SUCCESS);
}

int add_reply_helper(client_t *cli, gthread_t *thread, reply_t *new_reply, \
global_t *glob)
{
    char *event = NULL;

    add_reply_helper2(cli, thread, new_reply, glob);
    if (!(event = malloc(snprintf(NULL, 0, \
"%d %s : %s : %s : %s : %s : %s : %s", \
EVENT_THREAD_MSG_RECEIVED, cli->team->base.name, \
thread->base.name, cli->base.name, cli->team->base.uuid, \
thread->base.uuid, cli->base.uuid, new_reply->message) + 1)))
        return (EXIT_FAILURE);
    sprintf(event, "%d %s : %s : %s : %s : %s : %s : %s", \
EVENT_THREAD_MSG_RECEIVED, cli->team->base.name, \
thread->base.name, cli->base.name, cli->team->base.uuid, \
thread->base.uuid, cli->base.uuid, new_reply->message);
    send_event_to_clients(event, glob, cli->team);
    return (EXIT_SUCCESS);
}