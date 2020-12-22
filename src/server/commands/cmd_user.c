/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** cmd_connect
*/

#include "server.h"

int cmd_user(client_t *cli, header_t *header, global_t *glob)
{
    uuidx1_t *uuid_x1 = (uuidx1_t *)header;
    client_t *user = frm_uuid(glob->clients, uuid_x1->uuid);

    if (!user) {
        dprintf(cli->fd, "%d %s\r\n", EVENT_ERROR_UNKNOWN_USER, \
uuid_x1->uuid);
        return (EXIT_FAILURE);
    }
    dprintf(cli->fd, "%d %s : %s : %d\r\n", EVENT_PRINT_USERS, \
user->base.uuid, user->base.name, user->is_connected);
    return (EXIT_SUCCESS);
}