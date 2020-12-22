/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** thread_saver
*/

#include "database.h"

static int create_db_thread(int file, gthread_t *thread)
{
    db_thread_t db_thread = {
        .header = {DB_THREAD, sizeof(db_thread_t)}, .name = {0}, .uuid = {0},
        .message = {0}, .timestamp = {0}, .uuid_creator = {0},
    };

    memset(db_thread.name, 0, MAX_NAME_LENGTH);
    strcpy(db_thread.name, thread->base.name);
    memset(db_thread.uuid, 0, UUID_LENGHT);
    strcpy(db_thread.uuid, thread->base.uuid);
    memset(db_thread.message, 0, MAX_BODY_LENGTH);
    strcpy(db_thread.message, thread->message);
    memset(db_thread.timestamp, 0, TIMESTAMP_LENGHT);
    strcpy(db_thread.timestamp, thread->timestamp);
    memset(db_thread.uuid_creator, 0, UUID_LENGHT);
    strcpy(db_thread.uuid_creator, thread->uuid_creator);
    write(file, &db_thread, sizeof(db_thread_t));
    printf("%s%s --Saving thread: %s%s\n", "\033[0;32m", "<Saver>:", \
thread->base.name, "\033[0m");
    return (EXIT_SUCCESS);
}

int save_threads(int file, bvector_t *threads)
{
    gthread_t *tmp_thread = NULL;
    bvector_t *vec = threads;

    for (; vec; vec = vec->next) {
        tmp_thread = (gthread_t *)vec->data;
        create_db_thread(file, tmp_thread);
        save_replies(file, tmp_thread->replies);
    }
    return (EXIT_SUCCESS);
}