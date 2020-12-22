/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** client_reader
*/

#include "server.h"

static const cmd_t cmd_array[] = {
    {LOGIN, &cmd_login},
    {LOGOUT, &cmd_logout},
    {USERS, &cmd_users},
    {USER, &cmd_user},
    {SEND, &cmd_send},
    {MESSAGES, &cmd_messages},
    {SUBSCRIBE, &cmd_subscribe},
    {SUBSCRIBED, &cmd_subscribed},
    {UNSUBSCRIBE, &cmd_unsubscribe},
    {USE, &cmd_use},
    {CREATE, &cmd_create},
    {LIST, &cmd_list},
    {INFO, &cmd_info},
    {LOGIN, NULL}
};

static int manage_client_input(client_t *cli, global_t *glob)
{
    header_t *header = (header_t *)cli->buffer;

    for (size_t i = 0; cmd_array[i].func; ++i) {
        if (header->code == cmd_array[i].code) {
            if (i > 1 && cli->base.name[0] == 0) {
                dprintf(cli->fd, "%d %d\r\n", \
EVENT_ERROR_UNAUTHORIZED, header->code);
                return (EXIT_FAILURE);
            }
            return (cmd_array[i].func(cli, header, glob));
        }
    }
    dprintf(cli->fd, "%d Command Unknown\r\n", NO_EVENT);
    return (EXIT_FAILURE);
}

int read_from_client(client_t *cli, global_t *glob)
{
    int red;

    if (!cli)
        return EXIT_FAILURE;
    red = read(cli->fd, cli->buffer + cli->buffer_size, \
(cli->buffer_size < sizeof(header_t) ? sizeof(header_t) \
: ((header_t *)cli->buffer)->size) - cli->buffer_size);
    if (red <= 0)
        return (-1);
    cli->buffer_size += red;
    if (cli->buffer_size < sizeof(header_t))
        return (EXIT_FAILURE);
    if (cli->buffer_size < ((header_t *)cli->buffer)->size)
        return (EXIT_FAILURE);
    cli->buffer_size = 0;
    return (manage_client_input(cli, glob));
}