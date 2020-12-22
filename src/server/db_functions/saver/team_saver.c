/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** team_saver
*/

#include "database.h"

static int create_db_team(int file, team_t *team)
{
    db_team_t db_team = {
        .header = {.type = DB_TEAM, .size = sizeof(db_team_t)},
        .name = {0},
        .uuid = {0},
        .uuid_creator = {0},
        .description = {0},
    };

    memset(db_team.name, 0, MAX_NAME_LENGTH);
    strcpy(db_team.name, team->base.name);
    memset(db_team.uuid, 0, UUID_LENGHT);
    strcpy(db_team.uuid, team->base.uuid);
    memset(db_team.uuid_creator, 0, UUID_LENGHT);
    strcpy(db_team.uuid_creator, team->uuid_creator);
    memset(db_team.description, 0, MAX_DESCRIPTION_LENGTH);
    strcpy(db_team.description, team->description);
    write(file, &db_team, sizeof(db_team_t));
    printf("%s%s Saving team: %s%s\n", "\033[0;32m", "<Saver>:", \
team->base.name, "\033[0m");
    return (EXIT_SUCCESS);
}

int save_teams(int file, global_t *glob)
{
    team_t *tmp_team = NULL;
    bvector_t *vec = glob->teams;

    for (; vec; vec = vec->next) {
        tmp_team = (team_t *)vec->data;
        create_db_team(file, tmp_team);
        save_channels(file, tmp_team->channels);
    }
    return (EXIT_SUCCESS);
}