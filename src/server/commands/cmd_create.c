/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** cmd_connect
*/

#include "server.h"

static int add_team(create_t *create, client_t *cli, global_t *glob)
{
    team_t *new_team = NULL;

    if (frm_name(glob->teams, create->name)) {
        dprintf(cli->fd, "%d Team already exist\r\n",
            EVENT_ERROR_ALREADY_EXIST);
        return (EXIT_FAILURE);
    }
    new_team = create_team(create->name, create->body, \
cli->base.uuid, false);
    server_event_team_created(new_team->base.uuid, new_team->base.name, \
new_team->uuid_creator);
    if (!glob->teams)
        glob->teams = bvector_create(new_team, TEAM);
    else
        bvector_push_back(glob->teams, new_team, TEAM);
    add_team_helper(new_team, cli, glob);
    return (EXIT_SUCCESS);
}

static int add_channel(create_t *create, team_t *team, \
client_t *cli, global_t *glob)
{
    channel_t *new_channel = NULL;

    if (!is_client_sub_to_team(cli, team)) {
        dprintf(cli->fd, "%d Not sub to team\r\n", EVENT_ERROR_UNAUTHORIZED);
        return (EXIT_FAILURE);
    }
    if (frm_name(team->channels, create->name)) {
        dprintf(cli->fd, "%d Channel already exist\r\n",
            EVENT_ERROR_ALREADY_EXIST);
        return (EXIT_FAILURE);
    }
    new_channel = create_channel(create->name, create->body);
    server_event_channel_created(team->base.uuid, new_channel->base.uuid, \
new_channel->base.name);
    if (!team->channels)
        team->channels = bvector_create(new_channel, CHANNEL);
    else
        bvector_push_back(team->channels, new_channel, CHANNEL);
    add_channel_helper(new_channel, cli, glob);
    return (EXIT_SUCCESS);
}

static int add_thread(create_t *create, channel_t *channel, \
client_t *cli, global_t *glob)
{
    gthread_t *new_thread = NULL;

    if (!is_client_sub_to_team(cli, cli->team)) {
        dprintf(cli->fd, "%d Not sub to team\r\n", EVENT_ERROR_UNAUTHORIZED);
        return (EXIT_FAILURE);
    }
    if (frm_name(channel->threads, create->name)) {
        dprintf(cli->fd, "%d Thread already exist\r\n",
            EVENT_ERROR_ALREADY_EXIST);
        return (EXIT_FAILURE);
    }
    new_thread = create_thread(create->name, create->body, cli->base.uuid);
    server_event_thread_created(channel->base.uuid, new_thread->base.uuid, \
new_thread->uuid_creator, new_thread->message);
    if (!channel->threads)
        channel->threads = bvector_create(new_thread, THREAD);
    else
        bvector_push_back(channel->threads, new_thread, THREAD);
    add_thread_helper(new_thread, cli, glob);
    return (EXIT_SUCCESS);
}

static int add_reply(create_t *create, gthread_t *thread, client_t *cli, \
global_t *glob)
{
    reply_t *new_reply = NULL;

    if (!is_client_sub_to_team(cli, cli->team)) {
        dprintf(cli->fd, "%d Not sub to team\r\n", EVENT_ERROR_UNAUTHORIZED);
        return (EXIT_FAILURE);
    }
    new_reply = create_reply(cli->base.name, create->body, cli->base.uuid);
    server_event_thread_new_message(thread->base.uuid, \
new_reply->uuid_creator, new_reply->message);
    if (!thread->replies)
        thread->replies = bvector_create(new_reply, REPLY);
    else
        bvector_push_back(thread->replies, new_reply, REPLY);
    return (add_reply_helper(cli, thread, new_reply, glob));
}

int cmd_create(client_t *cli, header_t *header, global_t *glob)
{
    create_t *create = (create_t *)header;

    if (cli->thread) {
        if (create->name[0] != 0 || create->body[0] == 0) {
            dprintf(cli->fd, "%d Too many argument\r\n", NO_EVENT);
            return (EXIT_FAILURE);
        }
        return (add_reply(create, cli->thread, cli, glob));
    }
    if (create->name[0] == 0 || create->body[0] == 0) {
        dprintf(cli->fd, "%d Two argument needed\r\n", NO_EVENT);
        return (EXIT_FAILURE);
    }
    if (cli->channel)
        return (add_thread(create, cli->channel, cli, glob));
    if (cli->team)
        return (add_channel(create, cli->team, cli, glob));
    return (add_team(create, cli, glob));
}