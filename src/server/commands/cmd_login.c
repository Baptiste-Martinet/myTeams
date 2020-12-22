/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** cmd_connect
*/

#include "server.h"

static int login_helper(client_t *cli, global_t *glob)
{
    char *event = NULL;

    server_event_user_logged_in(cli->base.uuid);
    cli->is_connected = true;
    if (!(event = malloc(snprintf(NULL, 0, "%d %s : %s", EVENT_LOGGEDIN, \
cli->base.uuid, cli->base.name) + 1)))
        return (EXIT_FAILURE);
    sprintf(event, "%d %s : %s", EVENT_LOGGEDIN, cli->base.uuid, \
cli->base.name);
    send_event_to_clients(event, glob, NULL);
    return (EXIT_SUCCESS);
}

int cmd_login(client_t *cli, header_t *header, global_t *glob)
{
    login_t *login = (login_t *)header;
    client_t *existing_cli = NULL;

    if (strcmp(cli->base.name, "") != 0) {
        dprintf(cli->fd, "%d Already logged in\r\n", NO_EVENT);
        return (EXIT_FAILURE);
    }
    if ((existing_cli = frm_name(glob->clients, login->user_name))) {
        strcpy(cli->base.uuid, existing_cli->base.uuid);
        cli->subs = existing_cli->subs;
        if (existing_cli->is_connected == 0) {
            bvector_erase_at_pointer(&glob->clients, existing_cli);
        } else {
            cli->is_copy = true;
        }
        strcpy(cli->base.name, login->user_name);
    } else {
        strcpy(cli->base.name, login->user_name);
        server_event_user_created(cli->base.uuid, cli->base.name);
    }
    return (login_helper(cli, glob));
}