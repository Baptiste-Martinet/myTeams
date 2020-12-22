/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** cmd_connect
*/

#include "server.h"

static int use_team_helper(client_t *cli, use_t *use)
{
    if (cli->channel) {
        if (!(cli->thread = frm_uuid(cli->channel->threads, use->uuids[0])))
            dprintf(cli->fd, "%d %s\r\n", ERR_UNKNOWN_THREAD, use->uuids[0]);
        else {
            dprintf(cli->fd, "%d %s -> %s -> %s\r\n", NO_EVENT, \
cli->team->base.name, cli->channel->base.name, cli->thread->base.name);
            return (EXIT_SUCCESS);
        }
    } else if (cli->team) {
        if (!(cli->channel = frm_uuid(cli->team->channels, use->uuids[0])))
            dprintf(cli->fd, "%d %s\r\n", ERR_UNKNOWN_CHANN, use->uuids[0]);
        else {
            dprintf(cli->fd, "%d %s -> %s -> NULL\r\n", NO_EVENT, \
cli->team->base.name, cli->channel->base.name);
            return (EXIT_SUCCESS);
        }
    }
    return (EXIT_FAILURE);
}

static int use_team(client_t *cli, use_t *use, global_t *glob)
{
    team_t *team = frm_uuid(glob->teams, use->uuids[0]);

    if (!team) {
        if (use_team_helper(cli, use) == EXIT_FAILURE)
            dprintf(cli->fd, "%d %s\r\n", ERR_UNKNOWN_TEAM, use->uuids[0]);
    } else {
        cli->team = team;
        cli->channel = NULL;
        cli->thread = NULL;
        dprintf(cli->fd, "%d %s -> NULL -> NULL\r\n", NO_EVENT, \
cli->team->base.name);
    }
    return (EXIT_SUCCESS);
}

static int use_channel(client_t *cli, use_t *use, global_t *glob)
{
    team_t *team = NULL;
    channel_t *channel = NULL;

    if (!(team = frm_uuid(glob->teams, use->uuids[0])))
        dprintf(cli->fd, "%d %s\r\n", ERR_UNKNOWN_TEAM, use->uuids[0]);
    else if (!(channel = frm_uuid(team->channels, use->uuids[1])))
        dprintf(cli->fd, "%d, %s\r\n", ERR_UNKNOWN_CHANN, use->uuids[1]);
    else {
        cli->team = team;
        cli->channel = channel;
        cli->thread = NULL;
        dprintf(cli->fd, "%d Using %s -> %s -> NULL\r\n", NO_EVENT, \
team->base.name, channel->base.name);
    }
    return (EXIT_SUCCESS);
}

static int use_thread(client_t *cli, use_t *use, global_t *glob)
{
    team_t *team = NULL;
    channel_t *channel = NULL;
    gthread_t *thread = NULL;

    if (!(team = frm_uuid(glob->teams, use->uuids[0]))) {
        dprintf(cli->fd, "%d %s\r\n", ERR_UNKNOWN_TEAM, use->uuids[0]);
    } else if (!(channel = frm_uuid(team->channels, use->uuids[1]))) {
        dprintf(cli->fd, "%d %s\r\n", ERR_UNKNOWN_CHANN, use->uuids[1]);
    } else {
        if (!(thread = frm_uuid(channel->threads, use->uuids[2]))) {
            dprintf(cli->fd, "%d %s\r\n", ERR_UNKNOWN_THREAD, use->uuids[2]);
        } else {
            cli->team = team;
            cli->channel = channel;
            cli->thread = thread;
            dprintf(cli->fd, "%d %s -> %s -> %s\r\n", NO_EVENT,
            team->base.name, channel->base.name, thread->base.name);
        }
    }
    return (EXIT_SUCCESS);
}

int cmd_use(client_t *cli, header_t *header, global_t *glob)
{
    use_t *use = (use_t *)header;

    if (use->nb_uuid_defined < 1) {
        cli->team = NULL;
        cli->channel = NULL;
        cli->thread = NULL;
        dprintf(cli->fd, "%d You are at the domain's root\r\n", NO_EVENT);
        return (EXIT_SUCCESS);
    }
    if (use->nb_uuid_defined < 2)
        use_team(cli, use, glob);
    else if (use->nb_uuid_defined < 3)
        use_channel(cli, use, glob);
    else
        use_thread(cli, use, glob);
    return (EXIT_SUCCESS);
}