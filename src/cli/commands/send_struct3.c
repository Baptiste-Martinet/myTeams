/*
** EPITECH PROJECT, 2020
** send_struct1.c
** File description:
** send_struct1
*/

#include "client.h"

void send_create(char ** param, int fd)
{
    create_t login = {
        .header = {
            .code = CREATE,
            .size = sizeof(create_t)
        },
        .name = {0},
        .body = {0}
    };

    if (ptr_number((void **)param) < 2) {
        printf("Missing parameter(s).\n");
        return;
    }
    if (ptr_number((void **)param) >= 3) {
        write_on_struct(login.name, param[1], MAX_NAME_LENGTH);
        write_on_struct(login.body, param[2], MAX_BODY_LENGTH);
    } else
        write_on_struct(login.body, param[1], MAX_BODY_LENGTH);
    write(fd, &login, sizeof(create_t));
}

void send_list(char ** param, int fd)
{
    send_empty(param, LIST, fd);
}

void send_info(char ** param, int fd)
{
    send_empty(param, INFO, fd);
}

void send_empty(char **param, OP_CODES coded, int fd)
{
    empty_t empty = {
        .header = {
            .code = coded,
            .size = sizeof(empty_t)
        }
    };

    write(fd, &empty, sizeof(empty_t));
}

void send_uuidx1(char **param, OP_CODES coded, int fd)
{
    uuidx1_t login = {
        .header = {
            .code = coded,
            .size = sizeof(uuidx1_t)
        }
    };

    if (ptr_number((void **)param) < 2) {
        printf("Missing parameters.\n");
        return;
    }
    write_on_struct(login.uuid, param[1], UUID_LENGHT);
    write(fd, &login, sizeof(uuidx1_t));
}