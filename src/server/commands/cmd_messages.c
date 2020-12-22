/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** cmd_connect
*/

#include "server.h"

static int messages_helper(client_t *cli, client_t *cli2, global_t *glob)
{
    bvector_t *vec = glob->messages;
    message_t *tmp_mess = NULL;

    dprintf(cli->fd, "%d ", EVENT_MP_PRINT_MSG);
    for (size_t i = 0; vec; vec = vec->next) {
        tmp_mess = (message_t *)vec->data;
        if ((strcmp(tmp_mess->from_uuid, cli->base.uuid) == 0
        && strcmp(tmp_mess->to_uuid, cli2->base.uuid) == 0)
        || (strcmp(tmp_mess->from_uuid, cli2->base.uuid) == 0
        && strcmp(tmp_mess->to_uuid, cli->base.uuid) == 0)) {
            if (i != 0)
                dprintf(cli->fd, " : ");
            dprintf(cli->fd, "%s : %s : %s : %s", tmp_mess->from_name,
            tmp_mess->from_uuid, tmp_mess->timestamp, tmp_mess->content);
            ++i;
        }
    }
    dprintf(cli->fd, "\r\n");
    return (EXIT_SUCCESS);
}

int cmd_messages(client_t *cli, header_t *header, global_t *glob)
{
    client_t *cli2 = frm_uuid(glob->clients, ((uuidx1_t *)header)->uuid);

    if (!cli2) {
        dprintf(cli->fd, "%d %s\r\n", EVENT_ERROR_UNKNOWN_USER, \
((uuidx1_t *)header)->uuid);
        return (EXIT_FAILURE);
    }
    return (messages_helper(cli, cli2, glob));
}