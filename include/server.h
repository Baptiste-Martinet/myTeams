/*
** EPITECH PROJECT, 2020
** server.h
** File description:
** server
*/

#ifndef SERVER_H
#define SERVER_H

#define __USE_XOPEN
#define _GNU_SOURCE
#include "logging_server.h"
#undef __USE_XOPEN
#undef _GNU_SOURCE
#include "bvector.h"

typedef struct socket_s {
    struct sockaddr_in socket;
    int fd;
} socket_t;

typedef struct reply_s {
    bvector_base_t base;
    char uuid_creator[UUID_LENGHT];
    char message[MAX_BODY_LENGTH];
    char timestamp[TIMESTAMP_LENGHT];
} reply_t;

typedef struct gthread_s {
    bvector_base_t base;
    char uuid_creator[UUID_LENGHT];
    char message[MAX_BODY_LENGTH];
    char timestamp[TIMESTAMP_LENGHT];
    bvector_t *replies;
} gthread_t;

typedef struct channel_s {
    bvector_base_t base;
    char description[MAX_DESCRIPTION_LENGTH];
    bvector_t *threads;
} channel_t;

typedef struct team_s {
    bvector_base_t base;
    char uuid_creator[UUID_LENGHT];
    char description[MAX_DESCRIPTION_LENGTH];
    bvector_t *channels;
    bool initial_sub;
} team_t;

typedef struct client_s {
    bvector_base_t base;
    bool is_connected;
    int fd;
    void *buffer;
    int buffer_size;
    bool is_copy;
    team_t *team;
    channel_t *channel;
    gthread_t *thread;
    bvector_t *subs;
} client_t;

typedef struct message_s {
    bvector_base_t base;
    char timestamp[TIMESTAMP_LENGHT];
    char from_name[MAX_NAME_LENGTH];
    char from_uuid[UUID_LENGHT];
    char to_name[MAX_NAME_LENGTH];
    char to_uuid[UUID_LENGHT];
    char content[MAX_BODY_LENGTH];
} message_t;

typedef struct global_s {
    socket_t *server_socket;
    bvector_t *clients;
    bvector_t *teams;
    bvector_t *messages;
} global_t;

typedef struct cmd_s {
    OP_CODES code;
    int (*func)(client_t *cli, header_t *header, global_t *glob);
} cmd_t;

/* client_manager.c */

int start_server(int port);

/* client_reader.c */

int read_from_client(client_t *cli, global_t *glob);

/* server_utils.c */

socket_t *create_socket(uint16_t port, bool wanna_bind);
int accept_from_socket(socket_t *my_socket);
int start_listening_socket(socket_t *my_socket);
int connect_to_socket(socket_t *my_socket);

/* disconnect_client.c */

int disconnect_client(client_t *cli, global_t *glob);

/* event.c */

int send_event_to_clients(char *event, global_t *glob, team_t *subbed);
int send_event_to_clients_but_cli(char *event, global_t *glob, \
team_t *subbed, client_t *cli);


/* COMMANDS */

int cmd_login(client_t *cli, header_t *header, global_t *glob);
int cmd_logout(client_t *cli, header_t *header, global_t *glob);
int cmd_users(client_t *cli, header_t *header, global_t *glob);
int cmd_user(client_t *cli, header_t *header, global_t *glob);
int cmd_send(client_t *cli, header_t *header, global_t *glob);
int cmd_messages(client_t *cli, header_t *header, global_t *glob);
int cmd_subscribe(client_t *cli, header_t *header, global_t *glob);
int cmd_subscribed(client_t *cli, header_t *header, global_t *glob);
int cmd_unsubscribe(client_t *cli, header_t *header, global_t *glob);
int cmd_use(client_t *cli, header_t *header, global_t *glob);
int cmd_create(client_t *cli, header_t *header, global_t *glob);
int cmd_list(client_t *cli, header_t *header, global_t *glob);
int cmd_info(client_t *cli, header_t *header, global_t *glob);

/* LINKED LISTS */

/* client_list.c */

client_t * create_client(int fd);
void destroy_client(client_t * cli);
void bvector_erase_at_fd(bvector_t **vector, int fd);
void client_display(client_t *cli);
bool is_client_sub_to_team(client_t *cli, team_t *team);

/* team_list.c */

team_t * create_team(char name[MAX_NAME_LENGTH], \
char description[MAX_DESCRIPTION_LENGTH], \
char uuid_creator[UUID_LENGHT], bool initial_sub);
void destroy_team(team_t * team);

/* channel_list.c */

channel_t * create_channel(char name[MAX_NAME_LENGTH], \
char description[MAX_DESCRIPTION_LENGTH]);
void destroy_channel(channel_t * channel);

/* thread_list.c */

gthread_t * create_thread(char title[MAX_NAME_LENGTH], \
char message[MAX_BODY_LENGTH], \
char uuid_creator[UUID_LENGHT]);
void destroy_thread(gthread_t * thread);

/* reply_list.c */

reply_t * create_reply(char user_name[MAX_NAME_LENGTH], \
char message[MAX_BODY_LENGTH], \
char uuid_creator[UUID_LENGHT]);
void destroy_reply(reply_t * reply);

/* message_list.c */

message_t * create_message(client_t *from, client_t *to, \
char content[MAX_BODY_LENGTH]);
void destroy_message(message_t * message);
message_t *bvector_get_from_user_names(bvector_t *vector, \
char user_name1[MAX_NAME_LENGTH], char user_name2[MAX_NAME_LENGTH]);

/* cmd_helper.c */

int add_team_helper(team_t *new_team, client_t *cli, global_t *glob);
int add_channel_helper(channel_t *new_channel, client_t *cli, global_t *glob);
int add_thread_helper(gthread_t *new_thread, client_t *cli, global_t *glob);
int add_reply_helper(client_t *cli, gthread_t *thread, reply_t *new_reply, \
global_t *glob);

/* saver.c */

int save_server(global_t *glob);

/* loader.c */

int save_loader(global_t *glob);

#endif