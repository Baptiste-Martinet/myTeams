/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** message_list
*/

#include "server.h"

message_t * create_message(client_t *from, client_t *to, \
char content[MAX_BODY_LENGTH])
{
    message_t * message = malloc(sizeof(message_t));
    uuid_t binuuid;
    char *timee = time_now_to_string();

    uuid_generate_random(binuuid);
    uuid_unparse(binuuid, message->base.uuid);
    memset(message->timestamp, 0, TIMESTAMP_LENGHT);
    strcpy(message->timestamp, timee);
    free(timee);
    memset(message->from_name, 0, MAX_NAME_LENGTH);
    strcpy(message->from_name, from->base.name);
    memset(message->to_name, 0, MAX_NAME_LENGTH);
    strcpy(message->to_name, to->base.name);
    memset(message->from_uuid, 0, UUID_LENGHT);
    strcpy(message->from_uuid, from->base.uuid);
    memset(message->to_uuid, 0, UUID_LENGHT);
    strcpy(message->to_uuid, to->base.uuid);
    memset(message->content, 0, MAX_BODY_LENGTH);
    strcpy(message->content, content);
    return (message);
}

void destroy_message(message_t * message)
{
    if (!message)
        return;
    free(message);
}