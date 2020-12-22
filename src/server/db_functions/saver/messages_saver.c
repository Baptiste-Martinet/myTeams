/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** message_saver
*/

#include "database.h"

static int create_db_message(int file, message_t *message)
{
    db_message_t db_message = { .header = {DB_MESSAGE, sizeof(db_message_t)}, \
.timestamp = {0}, .from_name = {0}, .from_uuid = {0}, \
.to_name = {0}, .to_uuid = {0}, .content = {0}};

    memset(db_message.timestamp, 0, TIMESTAMP_LENGHT);
    strcpy(db_message.timestamp, message->timestamp);
    memset(db_message.from_name, 0, MAX_NAME_LENGTH);
    strcpy(db_message.from_name, message->from_name);
    memset(db_message.from_uuid, 0, UUID_LENGHT);
    strcpy(db_message.from_uuid, message->from_uuid);
    memset(db_message.to_name, 0, MAX_NAME_LENGTH);
    strcpy(db_message.to_name, message->to_name);
    memset(db_message.to_uuid, 0, UUID_LENGHT);
    strcpy(db_message.to_uuid, message->to_uuid);
    memset(db_message.content, 0, MAX_BODY_LENGTH);
    strcpy(db_message.content, message->content);
    write(file, &db_message, sizeof(db_message_t));
    printf("%s%s Saving message: %s%s\n", "\033[0;32m", "<Saver>:",
    message->content, "\033[0m");
    return (EXIT_SUCCESS);
}

int save_messages(int file, global_t *glob)
{
    message_t *tmp_message = NULL;
    bvector_t *vec = glob->messages;

    for (; vec; vec = vec->next) {
        tmp_message = (message_t *)vec->data;
        create_db_message(file, tmp_message);
    }
    return (EXIT_SUCCESS);
}