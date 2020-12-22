/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** message_loader
*/

#include "database.h"

int init_messsage(message_t *new_message, db_message_t *db_message)
{
    memset(new_message->base.name, 0, MAX_NAME_LENGTH);
    memset(new_message->base.uuid, 0, UUID_LENGHT);
    memset(new_message->content, 0, MAX_BODY_LENGTH);
    strcpy(new_message->content, db_message->content);
    memset(new_message->from_name, 0, MAX_NAME_LENGTH);
    strcpy(new_message->from_name, db_message->from_name);
    memset(new_message->to_name, 0, MAX_NAME_LENGTH);
    strcpy(new_message->to_name, db_message->to_name);
    memset(new_message->from_uuid, 0, UUID_LENGHT);
    strcpy(new_message->from_uuid, db_message->from_uuid);
    memset(new_message->to_uuid, 0, UUID_LENGHT);
    strcpy(new_message->to_uuid, db_message->to_uuid);
    memset(new_message->timestamp, 0, TIMESTAMP_LENGHT);
    strcpy(new_message->timestamp, db_message->timestamp);
    return (EXIT_SUCCESS);
}

int load_message(global_t *glob, db_header_t *header, db_loader_t *loader)
{
    db_message_t *db_message = (db_message_t *)header;
    message_t *new_message = malloc(sizeof(message_t));

    init_messsage(new_message, db_message);
    if (!glob->messages)
        glob->messages = bvector_create(new_message, MESSAGE);
    else
        bvector_push_back(glob->messages, new_message, MESSAGE);
    printf("%s%s Loading message: %s%s\n", "\033[0;32m", "<Loader>:", \
new_message->content, "\033[0m");
    return (EXIT_SUCCESS);
}