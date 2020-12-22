/*
** EPITECH PROJECT, 2020
** client.h
** File description:
** client
*/

#ifndef CLIENT_H
#define CLIENT_H

#ifndef __USE_XOPEN
#define __USE_XOPEN
#endif

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include "logging_client.h"
#undef __USE_XOPEN
#undef _GNU_SOURCE
#include "common.h"

#define STDIN_FD 0
#define UNKNOWN_COMMAND 42

typedef struct client_socket_t
{
    struct sockaddr_in distant_sock;
    int distant_fd;
    const char * ip;
    uint16_t port;
    bool error;
} client_socket_t;

client_socket_t create_socket(const char * ip, uint16_t port);
void close_socket(client_socket_t * w);
void client_loop(int distant_fd);

typedef struct account_t
{
    char * username;
    uuid_t used_uuid;
    int distant_fd;
    int last_fd_read;
    char * old_buffer;
} account_t;

int read_server(int distandFd, account_t * account);

typedef struct command_id_t
{
    const char * title;
    int (* func)(char *, account_t * account);
} command_id_t;

typedef struct command_parse_t
{
    const char * title;
    void (*ptr)(char **, int);
} command_parse_t;

void send_login(char ** param, int fd);
void send_logout(char ** param, int fd);
void send_users(char ** param, int fd);
void send_user(char ** param, int fd);
void send_send(char ** param, int fd);
void send_messages(char ** param, int fd);
void send_subscribe(char ** param, int fd);
void send_subscribed(char ** param, int fd);
void send_unsubscribe(char ** param, int fd);
void send_use(char ** param, int fd);
void send_create(char ** param, int fd);
void send_list(char ** param, int fd);
void send_info(char ** param, int fd);

void send_empty(char **param, OP_CODES code, int fd);
void send_uuidx1(char **param, OP_CODES coded, int fd);

void write_on_struct(char * dest, char * src, size_t size);

int check_command(char *line, account_t *account);

int help_command(char * param, account_t * account);
int send_command(char * param, account_t * account);

int verify_arguments(char * line);
char ** treat_arguments(char * split);

typedef struct error_msg_s
{
    int code;
    const char *msg;
} error_msg_t;

typedef struct treat_code_s
{
    int code;
    char * (*ptr)(char *, account_t *, char **);
} treat_code_t;

char * event_loggedin(char * line, account_t * account, char ** tab);
char * event_loggedout(char * line, account_t * account, char ** tab);
char * event_mp_received(char * line, account_t * account, char ** tab);
char * event_thread_msg_received(char * line, account_t * account, char ** tab);
char * event_print_users(char * line, account_t * account, char ** tab);
char * event_print_teams(char * line, account_t * account, char ** tab);
char * event_team_print_channels(char * line, account_t * account, char ** tab);
char * event_channel_print_thread(char * line, account_t * account, char ** ta);
char * event_thread_print_replies(char * line, account_t * account, char ** tb);
char * event_mp_print_msg(char * line, account_t * account, char ** tab);
char * event_unknown_team(char * line, account_t * account, char ** tab);
char * event_unknown_channel(char * line, account_t * account, char ** tab);
char * event_unknown_thread(char * line, account_t * account, char ** tab);
char * event_unknown_user(char * line, account_t * account, char ** tab);
char * event_unauthorized(char * line, account_t * account, char ** tab);
char * event_no_event(char * line, account_t * account, char ** tab);
char * event_already_exist(char * line, account_t * account, char ** tab);
char * event_print_user(char * line, account_t * account, char ** tab);
char * event_print_team(char * line, account_t * account, char ** tab);
char * event_print_channel(char * line, account_t * account, char ** tab);
char * event_print_thread(char * line, account_t * account, char ** tab);
char * event_print_team_created(char * line, account_t * account, char ** tab);
char * event_print_channel_created(char * li, account_t * account, char ** tab);
char * event_print_thread_created(char * lie, account_t * account, char ** tab);
char * event_print_replies_created(char * line, account_t * acco, char ** tab);
char * event_subscribed(char * line, account_t * account, char ** tab);
char * event_unsubscribed(char * line, account_t * account, char ** tab);
char * event_team_created(char * line, account_t * account, char ** tab);
char * event_channel_created(char * line, account_t * account, char ** tab);
char * event_thread_created(char * line, account_t * account, char ** tab);

void treat_code(int code, account_t * account, char * line);
int rfc_filtering(char * line, account_t * account);
int rfc_loop(char * line, account_t * account);

int create_fd_set_form_clients(int distant_fd, fd_set * fd_set, bool first);
int read_server_and_client(int distant_fd, account_t * account, bool first);

char * get_last_reponse(char * line);

int more_pipe(int mode);

void stock_rest(char ** tab, int index, account_t * account);

#endif