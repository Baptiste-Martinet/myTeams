/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** database
*/

#pragma once

#include "server.h"

enum DB_TYPES {
    DB_TEAM,
    DB_CHANNEL,
    DB_THREAD,
    DB_REPLY,
    DB_MESSAGE,
    DB_CLIENT,
    DB_SUB
};

typedef struct __attribute__((packed)) db_header_s {
    enum DB_TYPES type;
    int size;
} db_header_t;

typedef struct __attribute__((packed)) db_team_s {
    db_header_t header;
    char uuid[UUID_LENGHT];
    char uuid_creator[UUID_LENGHT];
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
} db_team_t;

typedef struct __attribute__((packed)) db_channel_s {
    db_header_t header;
    char name[MAX_NAME_LENGTH];
    char uuid[UUID_LENGHT];
    char description[MAX_DESCRIPTION_LENGTH];
} db_channel_t;

typedef struct __attribute__((packed)) db_thread_s {
    db_header_t header;
    char name[MAX_NAME_LENGTH];
    char uuid[UUID_LENGHT];
    char message[MAX_BODY_LENGTH];
    char timestamp[TIMESTAMP_LENGHT];
    char uuid_creator[UUID_LENGHT];
} db_thread_t;

typedef struct __attribute__((packed)) db_reply_s {
    db_header_t header;
    char name[MAX_NAME_LENGTH];
    char uuid[UUID_LENGHT];
    char uuid_creator[UUID_LENGHT];
    char message[MAX_BODY_LENGTH];
    char timestamp[TIMESTAMP_LENGHT];
} db_reply_t;

typedef struct __attribute__((packed)) db_message_s {
    db_header_t header;
    char timestamp[TIMESTAMP_LENGHT];
    char from_name[MAX_NAME_LENGTH];
    char from_uuid[UUID_LENGHT];
    char to_name[MAX_NAME_LENGTH];
    char to_uuid[UUID_LENGHT];
    char content[MAX_BODY_LENGTH];
} db_message_t;

typedef struct __attribute__((packed)) db_client_s {
    db_header_t header;
    char name[MAX_NAME_LENGTH];
    char uuid[UUID_LENGHT];
} db_client_t;

typedef struct __attribute__((packed)) db_sub_s {
    db_header_t header;
    char uuid[UUID_LENGHT];
} db_sub_t;

/* loader.c */

typedef struct db_loader_s {
    team_t *team;
    channel_t *channel;
    gthread_t *thread;
    client_t *client;
} db_loader_t;

typedef struct resource_type_s {
    enum DB_TYPES type;
    int (*func)(global_t *glob, db_header_t *header, db_loader_t *loader);
} resource_type_t;

/* SAVER */

int save_teams(int file, global_t *glob);
int save_channels(int file, bvector_t *channels);
int save_threads(int file, bvector_t *threads);
int save_replies(int file, bvector_t *replies);
int save_clients(int file, global_t *glob);
int save_messages(int file, global_t *glob);

/* LOADER */

int load_team(global_t *glob, db_header_t *header, db_loader_t *loader);
int load_channel(global_t *glob, db_header_t *header, db_loader_t *loader);
int load_thread(global_t *glob, db_header_t *header, db_loader_t *loader);
int load_reply(global_t *glob, db_header_t *header, db_loader_t *loader);
int load_message(global_t *glob, db_header_t *header, db_loader_t *loader);
int load_client(global_t *glob, db_header_t *header, db_loader_t *loader);
int load_client_sub(global_t *glob, db_header_t *header, db_loader_t *loader);