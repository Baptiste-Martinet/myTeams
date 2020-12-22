/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** cmd_connect
*/

#include "server.h"

static int send_helper(message_t *new_message, global_t *glob)
{
    bvector_t *vec = glob->clients;
    client_t *tmp_cli = NULL;

    for (; vec; vec = vec->next) {
        tmp_cli = (client_t *)vec->data;
        if (!tmp_cli->is_connected || tmp_cli->fd == -1)
            continue;
        if (strcmp(tmp_cli->base.uuid, new_message->to_uuid) == 0)
            dprintf(tmp_cli->fd, "%d %s : %s : %s\r\n", EVENT_MP_RECEIVED, \
new_message->from_name, new_message->from_uuid, new_message->content);
    }
    return (EXIT_SUCCESS);
}

int cmd_send(client_t *cli, header_t *header, global_t *glob)
{
    send_t *send = (send_t *)header;
    client_t *to = frm_uuid(glob->clients, send->uuid);
    message_t *new_message = create_message(cli, to, send->message);

    if (!to) {
        dprintf(cli->fd, "%d %s\r\n", EVENT_ERROR_UNKNOWN_USER, send->uuid);
        return (EXIT_FAILURE);
    }
    server_event_private_message_sended(cli->base.uuid, send->uuid, \
send->message);
    dprintf(cli->fd, "%d Message successfuly sent\r\n", NO_EVENT);
    if (!glob->messages)
        glob->messages = bvector_create(new_message, MESSAGE);
    else
        bvector_push_back(glob->messages, new_message, MESSAGE);
    return (send_helper(new_message, glob));
}