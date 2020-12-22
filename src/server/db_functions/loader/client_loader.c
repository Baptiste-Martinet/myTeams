/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** client_loader
*/

#include "database.h"

int load_client(global_t *glob, db_header_t *header, db_loader_t *loader)
{
    db_client_t *db_client = (db_client_t *)header;
    client_t *new_cli = create_client(-1);

    strcpy(new_cli->base.name, db_client->name);
    strcpy(new_cli->base.uuid, db_client->uuid);
    if (!glob->clients)
        glob->clients = bvector_create(new_cli, CLIENT);
    else
        bvector_push_back(glob->clients, new_cli, CLIENT);
    loader->client = new_cli;
    printf("%s%s Loading client: %s%s\n", "\033[0;32m", "<Loader>:", \
new_cli->base.name, "\033[0m");
    server_event_user_loaded(new_cli->base.uuid, new_cli->base.name);
    return (EXIT_SUCCESS);
}

int load_client_sub(global_t *glob, db_header_t *header, db_loader_t *loader)
{
    db_sub_t *db_sub = (db_sub_t *)header;
    team_t *sub = frm_uuid(glob->teams, db_sub->uuid);

    if (!sub) {
        puts("\033[0;31m<Loader>: Sub Error: team doesn't exist]\033[0m");
        return (EXIT_FAILURE);
    }
    if (!loader->client) {
        puts("\033[0;31m<Loader>: Sub Error: client not defined]\033[0m");
        return (EXIT_FAILURE);
    }
    if (!loader->client->subs)
        loader->client->subs = bvector_create(sub, TEAM);
    else
        bvector_push_back(loader->client->subs, sub, TEAM);
    printf("%s%s -Loading client sub: %s%s\n", "\033[0;32m", "<Loader>:", \
sub->base.name, "\033[0m");
    return (EXIT_SUCCESS);
}