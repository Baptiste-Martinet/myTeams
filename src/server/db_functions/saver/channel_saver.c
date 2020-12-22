/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** channel_saver
*/

#include "database.h"

static int create_db_channel(int file, channel_t *channel)
{
    db_channel_t db_channel = {
        .header = {.type = DB_CHANNEL, .size = sizeof(db_channel_t)},
        .name = {0},
        .uuid = {0},
        .description = {0},
    };

    memset(db_channel.name, 0, MAX_NAME_LENGTH);
    strcpy(db_channel.name, channel->base.name);
    memset(db_channel.uuid, 0, UUID_LENGHT);
    strcpy(db_channel.uuid, channel->base.uuid);
    memset(db_channel.description, 0, MAX_DESCRIPTION_LENGTH);
    strcpy(db_channel.description, channel->description);
    write(file, &db_channel, sizeof(db_channel_t));
    printf("%s%s -Saving channel: %s%s\n", "\033[0;32m", "<Saver>:", \
channel->base.name, "\033[0m");
    return (EXIT_SUCCESS);
}

int save_channels(int file, bvector_t *channels)
{
    channel_t *tmp_channel = NULL;
    bvector_t *vec = channels;

    for (; vec; vec = vec->next) {
        tmp_channel = (channel_t *)vec->data;
        create_db_channel(file, tmp_channel);
        save_threads(file, tmp_channel->threads);
    }
    return (EXIT_SUCCESS);
}