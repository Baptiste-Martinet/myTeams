/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** string_utils
*/

#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <zconf.h>
#include <signal.h>
#include <errno.h>
#include <sys/stat.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <stdbool.h>
#include <netdb.h>
#include <limits.h>
#include <fcntl.h>
#include <uuid/uuid.h>

#define CRLF "\r\n\0"
#define IP "127.0.0.1"
#define CLIENT_NUMBER 1024
#define BUFFER_SIZE 1024

#undef EXIT_FAILURE
#define EXIT_FAILURE 84

#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512
#define UUID_LENGHT 37
#define TIMESTAMP_LENGHT 20

#include "rfc.h"

char * load_file_in_mem(const char * filepath);
int help(int ac, char ** av, const char * help_msg_path, int supposed_arg);

int contains(const char * str, const char * str1);
bool starts_with(const char *pre, const char *str);
bool ends_with(char * base, char * str);
int is_numeric(const char * s);
char ** split(char * line, const char * delimiter);
void free_2darray(void ** array);
char * multi_tok(char * input, const char * delimiter);
char * multi_tok_no_delim(char * input, const char * delimiter);
char ** split_no_delim(char * line, const char * delimiter);
size_t ptr_number(void ** split);

/* str_to_word_array.c */
char **str_to_word_array(char *str, char *delims);
int array_len(char **array);

/* string_utils */
char *my_strcat(char *s1, char *s2);
char *str_to_upper(char *str);

typedef enum header_types_t
{
    COMMAND
} header_types_t;

typedef enum OP_CODES_S {
    LOGIN,
    LOGOUT,
    USERS,
    USER,
    SEND,
    MESSAGES,
    SUBSCRIBE,
    SUBSCRIBED,
    UNSUBSCRIBE,
    USE,
    CREATE,
    LIST,
    INFO
} OP_CODES;

typedef struct __attribute__((packed)) header_s {
    OP_CODES code;
    int size;
} header_t;

typedef struct __attribute__((packed)) login_s {
    header_t header;
    char user_name[MAX_NAME_LENGTH];
} login_t;

typedef struct __attribute__((packed)) use_s {
    header_t header;
    size_t nb_uuid_defined;
    char uuids[3][UUID_LENGHT];
} use_t;

typedef struct __attribute__((packed)) send_s {
    header_t header;
    char uuid[UUID_LENGHT];
    char message[MAX_BODY_LENGTH];
} send_t;

typedef struct __attribute__((packed)) empty_s {
    header_t header;
} empty_t;

typedef struct __attribute__((packed)) uuidx1_s {
    header_t header;
    char uuid[UUID_LENGHT];
} uuidx1_t;

typedef struct __attribute__((packed)) create_s {
    header_t header;
    char name[MAX_NAME_LENGTH];
    char body[MAX_BODY_LENGTH];
} create_t;

char * time_to_string(time_t timee);
char * time_now_to_string(void);
time_t string_to_time_t(const char * str);

int my_getline(char ** line, int fd, char ** old_buffer);

bool stop_the_program(bool set);

int more_pipe(int mode);

#endif