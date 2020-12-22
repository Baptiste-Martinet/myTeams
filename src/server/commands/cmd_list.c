/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** cmd_connect
*/

#include "server.h"

static int list_teams(client_t *cli, global_t *glob)
{
    bvector_t *vec = glob->teams;
    team_t *tmp_team;

    dprintf(cli->fd, "%d ", EVENT_PRINT_TEAMS);
    for (size_t i = 0; vec; vec = vec->next, ++i) {
        tmp_team = (team_t *)vec->data;
        if (i != 0)
            dprintf(cli->fd, " : ");
        dprintf(cli->fd, "%s : %s : %s", tmp_team->base.uuid, \
tmp_team->base.name, tmp_team->description);
    }
    dprintf(cli->fd, "\r\n");
    return (EXIT_SUCCESS);
}

static int list_channels(client_t *cli, team_t *team, global_t *glob)
{
    bvector_t *vec = team->channels;
    channel_t *tmp_channel;

    dprintf(cli->fd, "%d ", EVENT_TEAM_PRINT_CHANNELS);
    for (size_t i = 0; vec; vec = vec->next, ++i) {
        tmp_channel = (channel_t *)vec->data;
        if (i != 0)
            dprintf(cli->fd, " : ");
        dprintf(cli->fd, "%s : %s : %s", tmp_channel->base.uuid, \
tmp_channel->base.name, tmp_channel->description);
    }
    dprintf(cli->fd, "\r\n");
    return (EXIT_SUCCESS);
}

static int list_threads(client_t *cli, channel_t *channel, global_t *glob)
{
    bvector_t *vec = channel->threads;
    gthread_t *tmp_thread;

    dprintf(cli->fd, "%d ", EVENT_CHANNEL_PRINT_THREADS);
    for (size_t i = 0; vec; vec = vec->next, ++i) {
        tmp_thread = (gthread_t *)vec->data;
        if (i != 0)
            dprintf(cli->fd, " : ");
        dprintf(cli->fd, "%s : %s : %s : %s : %s", tmp_thread->base.uuid, \
tmp_thread->uuid_creator, tmp_thread->timestamp, \
tmp_thread->base.name, tmp_thread->message);
    }
    dprintf(cli->fd, "\r\n");
    return (EXIT_SUCCESS);
}

static int list_replies(client_t *cli, gthread_t *thread, global_t *glob)
{
    bvector_t *vec = thread->replies;
    reply_t *tmp_reply;

    dprintf(cli->fd, "%d ", EVENT_THREAD_PRINT_REPLIES);
    for (size_t i = 0; vec; vec = vec->next, ++i) {
        tmp_reply = (reply_t *)vec->data;
        if (i != 0)
            dprintf(cli->fd, " : ");
        dprintf(cli->fd, "%s : %s : %s : %s", thread->base.uuid,
        tmp_reply->uuid_creator, tmp_reply->timestamp, tmp_reply->message);
    }
    dprintf(cli->fd, "\r\n");
    return (EXIT_SUCCESS);
}

int cmd_list(client_t *cli, header_t *header, global_t *glob)
{
    if (cli->thread)
        return (list_replies(cli, cli->thread, glob));
    if (cli->channel)
        return (list_threads(cli, cli->channel, glob));
    if (cli->team)
        return (list_channels(cli, cli->team, glob));
    return (list_teams(cli, glob));
}