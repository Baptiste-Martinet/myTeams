/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** cmd_connect
*/

#include "server.h"

int cmd_users(client_t *cli, header_t *header, global_t *glob)
{
    bvector_t *tmp = glob->clients;
    client_t *tmp_cli = NULL;

    dprintf(cli->fd, "%d ", EVENT_PRINT_USERS);
    for (size_t i = 0; tmp; tmp = tmp->next) {
        tmp_cli = (client_t *)tmp->data;
        if (tmp_cli->base.name[0] == 0 || tmp_cli->is_copy)
            continue;
        if (i != 0)
            dprintf(cli->fd, " : ");
        dprintf(cli->fd, "%s : %s : %d", tmp_cli->base.uuid, \
tmp_cli->base.name, tmp_cli->is_connected);
        ++i;
    }
    dprintf(cli->fd, "\r\n");
    return (EXIT_SUCCESS);
}