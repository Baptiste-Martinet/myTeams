/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** client_list
*/

#include "server.h"

client_t * create_client(int fd)
{
    client_t * client = malloc(sizeof(client_t));
    uuid_t binuuid;

    uuid_generate_random(binuuid);
    client->is_connected = false;
    client->fd = fd;
    memset(client->base.name, 0, MAX_NAME_LENGTH);
    uuid_unparse(binuuid, client->base.uuid);
    client->buffer = malloc(BUFFER_SIZE);
    memset(client->buffer, 0, BUFFER_SIZE);
    client->buffer_size = 0;
    client->is_copy = false;
    client->team = NULL;
    client->channel = NULL;
    client->thread = NULL;
    client->subs = bvector_create(create_team("", "", "", true), TEAM);
    return (client);
}

void destroy_client(client_t * cli)
{
    if (!cli)
        return;
    if (cli->fd != -1)
        close(cli->fd);
    if (cli->buffer)
        free(cli->buffer);
    free(cli);
}

void bvector_erase_at_fd(bvector_t **vector, int fd)
{
    bvector_t *tmp = *vector;
    bvector_t *to_be_free = NULL;

    if (!vector)
        return;
    if ((*vector)->type != CLIENT)
        return;
    if (((client_t *)((*vector)->data))->fd == fd) {
        *vector = (*vector)->next;
        bvector_destroy(tmp);
        return;
    }
    for (; tmp->next; tmp = tmp->next) {
        if (((client_t *)tmp->next->data)->fd == fd) {
            to_be_free = tmp->next;
            tmp->next = tmp->next->next;
            bvector_destroy(to_be_free);
            break;
        }
    }
}

bool is_client_sub_to_team(client_t *cli, team_t *team)
{
    bvector_t *vec = cli->subs;

    for (; vec; vec = vec->next) {
        if ((team_t *)vec->data == team) {
            return (true);
        }
    }
    return (false);
}

void client_display(client_t *cli)
{
    printf("{uuid: %s name: %s, is_connected: %d}, ", cli->base.uuid, \
cli->base.name, cli->is_connected);
}