/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** event
*/

#include "server.h"

int send_event_to_clients(char *event, global_t *glob, team_t *subbed)
{
    bvector_t *vec = glob->clients;
    client_t *tmp_cli = NULL;

    for (; vec; vec = vec->next) {
        tmp_cli = (client_t *)vec->data;
        if (!tmp_cli->is_connected || tmp_cli->fd == -1)
            continue;
        if (subbed && !is_client_sub_to_team(tmp_cli, subbed))
            continue;
        dprintf(tmp_cli->fd, "%s\r\n", event);
    }
    free(event);
    return (EXIT_SUCCESS);
}

int send_event_to_clients_but_cli(char *event, global_t *glob, \
team_t *subbed, client_t *cli)
{
    bvector_t *vec = glob->clients;
    client_t *tmp_cli = NULL;

    for (; vec; vec = vec->next) {
        tmp_cli = (client_t *)vec->data;
        if (!tmp_cli->is_connected || tmp_cli->fd == -1
            || (cli && tmp_cli == cli))
            continue;
        if (subbed && !is_client_sub_to_team(tmp_cli, subbed))
            continue;
        dprintf(tmp_cli->fd, "%s\r\n", event);
    }
    free(event);
    return (EXIT_SUCCESS);
}