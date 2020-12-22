/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** reply_list
*/

#include "server.h"

reply_t * create_reply(char user_name[MAX_NAME_LENGTH], \
char message[MAX_BODY_LENGTH], char uuid_creator[UUID_LENGHT])
{
    reply_t * reply = malloc(sizeof(reply_t));
    uuid_t binuuid;
    char *timee = time_now_to_string();

    uuid_generate_random(binuuid);
    uuid_unparse(binuuid, reply->base.uuid);
    memset(reply->base.name, 0, MAX_NAME_LENGTH);
    strcpy(reply->base.name, user_name);
    memset(reply->message, 0, MAX_BODY_LENGTH);
    strcpy(reply->message, message);
    memset(reply->timestamp, 0, TIMESTAMP_LENGHT);
    strcpy(reply->timestamp, timee);
    free(timee);
    strcpy(reply->uuid_creator, uuid_creator);
    return (reply);
}

void destroy_reply(reply_t * reply)
{
    if (!reply)
        return;
    free(reply);
}