/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** thread_list
*/

#include "server.h"

gthread_t * create_thread(char title[MAX_NAME_LENGTH], \
char message[MAX_BODY_LENGTH], char uuid_creator[UUID_LENGHT])
{
    gthread_t * thread = malloc(sizeof(gthread_t));
    uuid_t binuuid;
    char *timee = time_now_to_string();

    uuid_generate_random(binuuid);
    uuid_unparse(binuuid, thread->base.uuid);
    memset(thread->base.name, 0, MAX_NAME_LENGTH);
    strcpy(thread->base.name, title);
    memset(thread->message, 0, MAX_BODY_LENGTH);
    strcpy(thread->message, message);
    memset(thread->timestamp, 0, TIMESTAMP_LENGHT);
    strcpy(thread->timestamp, timee);
    free(timee);
    memset(thread->uuid_creator, 0, UUID_LENGHT);
    strcpy(thread->uuid_creator, uuid_creator);
    thread->replies = NULL;
    return (thread);
}

void destroy_thread(gthread_t * thread)
{
    if (!thread)
        return;
    free(thread);
}