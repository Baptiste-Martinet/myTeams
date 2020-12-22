/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** disconnect_client
*/

#include "server.h"

static int disconnect_client_helper(client_t *cli, global_t *glob)
{
    client_t *test = NULL;

    close(cli->fd);
    cli->fd = -1;
    cli->is_connected = false;
    if ((test = frm_uuid_not_same(glob->clients, \
cli->base.uuid, cli))) {
        test->is_copy = false;
        bvector_erase_at_pointer(&glob->clients, cli);
    }
    return (EXIT_SUCCESS);
}

int disconnect_client(client_t *cli, global_t *glob)
{
    char *event = NULL;

    if (cli->base.name[0] == 0) {
        bvector_erase_at_fd(&glob->clients, cli->fd);
        return (EXIT_FAILURE);
    }
    server_event_user_logged_out(cli->base.uuid);
    if (!(event = malloc(snprintf(NULL, 0, "%d %s : %s", EVENT_LOGGEDOUT,
        cli->base.uuid, cli->base.name) + 1)))
        return (EXIT_FAILURE);
    sprintf(event, "%d %s : %s", EVENT_LOGGEDOUT, \
cli->base.uuid, cli->base.name);
    send_event_to_clients(event, glob, NULL);
    return (disconnect_client_helper(cli, glob));
}