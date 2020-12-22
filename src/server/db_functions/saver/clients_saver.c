/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** save_clients
*/

#include "database.h"

static int create_db_sub(int file, team_t *sub)
{
    db_sub_t db_sub = {
        .header = {DB_SUB, sizeof(db_sub_t)},
        .uuid = {0},
    };
    memset(db_sub.uuid, 0, UUID_LENGHT);
    strcpy(db_sub.uuid, sub->base.uuid);
    write(file, &db_sub, sizeof(db_sub_t));
    printf("%s%s -Saving client sub: %s%s\n", "\033[0;32m", "<Saver>:", \
sub->base.name, "\033[0m");
    return (EXIT_SUCCESS);
}

static int create_db_client(int file, client_t *cli)
{
    db_client_t db_client = {
        .header = {DB_CLIENT, sizeof(db_client_t)},
        .name = {0},
        .uuid = {0},
    };
    memset(db_client.name, 0, MAX_NAME_LENGTH);
    strcpy(db_client.name, cli->base.name);
    memset(db_client.uuid, 0, UUID_LENGHT);
    strcpy(db_client.uuid, cli->base.uuid);
    write(file, &db_client, sizeof(db_client_t));
    printf("%s%s Saving client: %s%s\n", "\033[0;32m", "<Saver>:", \
cli->base.name, "\033[0m");
    return (EXIT_SUCCESS);
}

static int save_client_subs(int file, bvector_t *subs)
{
    team_t *tmp_sub = NULL;
    bvector_t *vec = subs;

    for (; vec; vec = vec->next) {
        tmp_sub = (team_t *)vec->data;
        if (tmp_sub->initial_sub)
            continue;
        create_db_sub(file, tmp_sub);
    }
    return (EXIT_SUCCESS);
}

int save_clients(int file, global_t *glob)
{
    client_t *tmp_cli = NULL;
    bvector_t *vec = glob->clients;

    for (; vec; vec = vec->next) {
        tmp_cli = (client_t *)vec->data;
        if (tmp_cli->is_copy)
            continue;
        create_db_client(file, tmp_cli);
        save_client_subs(file, tmp_cli->subs);
    }
    return (EXIT_SUCCESS);
}