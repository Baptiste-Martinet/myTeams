/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** replies_saver
*/

#include "database.h"

static int create_db_reply(int file, reply_t *reply)
{
    db_reply_t db_reply = {
        .header = {DB_REPLY, sizeof(db_reply_t)}, .name = {0}, .uuid = {0},
        .uuid_creator = {0}, .message = {0}, .timestamp = {0},
    };

    memset(db_reply.name, 0, MAX_NAME_LENGTH);
    strcpy(db_reply.name, reply->base.name);
    memset(db_reply.uuid, 0, UUID_LENGHT);
    strcpy(db_reply.uuid, reply->base.uuid);
    memset(db_reply.uuid_creator, 0, UUID_LENGHT);
    strcpy(db_reply.uuid_creator, reply->uuid_creator);
    memset(db_reply.message, 0, MAX_BODY_LENGTH);
    strcpy(db_reply.message, reply->message);
    memset(db_reply.timestamp, 0, TIMESTAMP_LENGHT);
    strcpy(db_reply.timestamp, reply->timestamp);
    write(file, &db_reply, sizeof(db_reply_t));
    printf("%s%s ---Saving reply: %s%s\n", "\033[0;32m", "<Saver>:", \
reply->message, "\033[0m");
    return (EXIT_SUCCESS);
}

int save_replies(int file, bvector_t *replies)
{
    reply_t *tmp_reply = NULL;
    bvector_t *vec = replies;

    for (; vec; vec = vec->next) {
        tmp_reply = (reply_t *)vec->data;
        create_db_reply(file, tmp_reply);
    }
    return (EXIT_SUCCESS);
}