/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** team_loader
*/

#include "database.h"

int load_reply(global_t *glob, db_header_t *header, db_loader_t *loader)
{
    db_reply_t *db_reply = (db_reply_t *)header;
    reply_t *new_reply = create_reply(db_reply->name, db_reply->message, \
db_reply->uuid_creator);

    memset(new_reply->base.uuid, 0, UUID_LENGHT);
    strcpy(new_reply->base.uuid, db_reply->uuid);
    memset(new_reply->timestamp, 0, TIMESTAMP_LENGHT);
    strcpy(new_reply->timestamp, db_reply->timestamp);
    if (!loader->thread)
        return (EXIT_FAILURE);
    if (!loader->thread->replies)
        loader->thread->replies = bvector_create(new_reply, REPLY);
    else
        bvector_push_back(loader->thread->replies, new_reply, REPLY);
    printf("%s%s ---Loading reply: %s%s\n", "\033[0;32m", "<Loader>:", \
new_reply->base.name, "\033[0m");
    return (EXIT_SUCCESS);
}

int load_thread(global_t *glob, db_header_t *header, db_loader_t *loader)
{
    db_thread_t *db_thread = (db_thread_t *)header;
    gthread_t *new_thread = create_thread(db_thread->name, \
db_thread->message, db_thread->uuid_creator);

    memset(new_thread->base.uuid, 0, UUID_LENGHT);
    strcpy(new_thread->base.uuid, db_thread->uuid);
    memset(new_thread->timestamp, 0, TIMESTAMP_LENGHT);
    strcpy(new_thread->timestamp, db_thread->timestamp);
    if (!loader->channel)
        return (EXIT_FAILURE);
    if (!loader->channel->threads)
        loader->channel->threads = bvector_create(new_thread, THREAD);
    else
        bvector_push_back(loader->channel->threads, new_thread, THREAD);
    loader->thread = new_thread;
    printf("%s%s --Loading thread: %s%s\n", "\033[0;32m", "<Loader>:", \
new_thread->base.name, "\033[0m");
    return (EXIT_SUCCESS);
}

int load_channel(global_t *glob, db_header_t *header, db_loader_t *loader)
{
    db_channel_t *db_channel = (db_channel_t *)header;
    channel_t *new_channel = create_channel(db_channel->name, \
db_channel->description);

    memset(new_channel->base.uuid, 0, UUID_LENGHT);
    strcpy(new_channel->base.uuid, db_channel->uuid);
    if (!loader->team)
        return (EXIT_FAILURE);
    if (!loader->team->channels)
        loader->team->channels = bvector_create(new_channel, CHANNEL);
    else
        bvector_push_back(loader->team->channels, new_channel, CHANNEL);
    loader->channel = new_channel;
    printf("%s%s -Loading channel: %s%s\n", "\033[0;32m", "<Loader>:", \
new_channel->base.name, "\033[0m");
    return (EXIT_SUCCESS);
}

int load_team(global_t *glob, db_header_t *header, db_loader_t *loader)
{
    db_team_t *db_team = (db_team_t *)header;
    team_t *new_team = create_team(db_team->name, db_team->description, \
db_team->uuid_creator, false);

    memset(new_team->base.uuid, 0, UUID_LENGHT);
    strcpy(new_team->base.uuid, db_team->uuid);
    if (!glob->teams)
        glob->teams = bvector_create(new_team, TEAM);
    else
        bvector_push_back(glob->teams, new_team, TEAM);
    loader->team = new_team;
    printf("%s%s Loading team: %s%s\n", "\033[0;32m", "<Loader>:", \
new_team->base.name, "\033[0m");
    return (EXIT_SUCCESS);
}