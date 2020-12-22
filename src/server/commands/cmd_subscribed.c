/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** cmd_connect
*/

#include "server.h"

static int display_team_subs(client_t *cli, team_t *team, global_t *glob)
{
    bvector_t *vec = glob->clients;
    client_t *tmp_cli = NULL;

    dprintf(cli->fd, "%d ", EVENT_PRINT_USERS);
    for (size_t i = 0; vec; vec = vec->next) {
        tmp_cli = (client_t *)vec->data;
        if (is_client_sub_to_team(tmp_cli, team)) {
            if (i != 0)
                dprintf(cli->fd, " : ");
            dprintf(cli->fd, "%s : %s : %d", tmp_cli->base.uuid, \
tmp_cli->base.name, tmp_cli->is_connected);
            ++i;
        }
    }
    dprintf(cli->fd, "\r\n");
    return (EXIT_SUCCESS);
}

static int display_subscribed(client_t *cli)
{
    bvector_t *vec = cli->subs;
    team_t *team = NULL;

    dprintf(cli->fd, "%d ", EVENT_PRINT_TEAMS);
    for (size_t i = 0; vec; vec = vec->next) {
        team = (team_t *)vec->data;
        if (team->initial_sub)
            continue;
        if (i != 0)
            dprintf(cli->fd, " : ");
        dprintf(cli->fd, "%s : %s : %s", team->base.uuid, \
team->base.name, team->description);
        ++i;
    }
    dprintf(cli->fd, "\r\n");
    return (EXIT_SUCCESS);
}

int cmd_subscribed(client_t *cli, header_t *header, global_t *glob)
{
    uuidx1_t *uuid_x1 = (uuidx1_t *)header;
    team_t *team = NULL;

    if (uuid_x1->uuid[0] == 0) {
        return (display_subscribed(cli));
    }
    if (!(team = frm_uuid(glob->teams, uuid_x1->uuid))) {
        dprintf(cli->fd, "%d %s\r\n", ERR_UNKNOWN_TEAM, uuid_x1->uuid);
        return (EXIT_FAILURE);
    }
    return (display_team_subs(cli, team, glob));
}