/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** team_list
*/

#include "server.h"

team_t * create_team(char name[MAX_NAME_LENGTH], \
char description[MAX_DESCRIPTION_LENGTH], \
char uuid_creator[UUID_LENGHT], bool initial_sub)
{
    team_t * team = malloc(sizeof(team_t));
    uuid_t binuuid;

    uuid_generate_random(binuuid);
    uuid_unparse(binuuid, team->base.uuid);
    memset(team->base.name, 0, MAX_NAME_LENGTH);
    strcpy(team->base.name, name);
    memset(team->description, 0, MAX_DESCRIPTION_LENGTH);
    strcpy(team->description, description);
    memset(team->uuid_creator, 0, UUID_LENGHT);
    strcpy(team->uuid_creator, uuid_creator);
    team->initial_sub = initial_sub;
    team->channels = NULL;
    return (team);
}

void destroy_team(team_t * team)
{
    if (!team)
        return;
}