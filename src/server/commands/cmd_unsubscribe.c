/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** cmd_connect
*/

#include "server.h"

int cmd_unsubscribe(client_t *cli, header_t *header, global_t *glob)
{
    team_t *team = frm_uuid(glob->teams, ((uuidx1_t *)header)->uuid);

    if (!team) {
        dprintf(cli->fd, "%d Team does not exist\r\n", ERR_UNKNOWN_TEAM);
        return (EXIT_FAILURE);
    }
    server_event_user_leave_a_team(team->base.uuid, cli->base.uuid);
    dprintf(cli->fd, "%d %s : %s\r\n", EVENT_PRINT_SUBSCRIBED, cli->base.uuid, \
team->base.uuid);
    if (!bvector_erase_at_pointer(&cli->subs, team)) {
        dprintf(cli->fd, "%d Error: Can't delete team\r\n", NO_EVENT);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}