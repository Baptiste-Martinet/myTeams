/*
** EPITECH PROJECT, 2020
** send_struct1.c
** File description:
** send_struct1
*/

#include "client.h"

void send_login(char ** param, int fd)
{
    login_t login = {
        .header = {
            .code = LOGIN,
            .size = sizeof(login_t)
        },
        .user_name = {0}
    };

    if (ptr_number((void **)param) < 2) {
        printf("Missing name parameter.\n");
        return;
    }
    if (ptr_number((void **)param) >= 2)
        write_on_struct(login.user_name, param[1], MAX_NAME_LENGTH);
    write(fd, &login, sizeof(login_t));
}

void send_logout(char ** param, int fd)
{
    send_empty(param, LOGOUT, fd);
}

void send_users(char ** param, int fd)
{
    send_empty(param, USERS, fd);
}

void send_user(char ** param, int fd)
{
    send_uuidx1(param, USER, fd);
}

void send_send(char ** param, int fd)
{
    send_t login = {
        .header = {
            .code = SEND,
            .size = sizeof(send_t)
        },
        .uuid = {0},
        .message = {0}
    };

    if (ptr_number((void **)param) < 3) {
        printf("Missing parameters.\n");
        return;
    }
    if (ptr_number((void **)param) >= 2)
        write_on_struct(login.uuid, param[1], UUID_LENGHT);
    if (ptr_number((void **)param) >= 3)
        write_on_struct(login.message, param[2], MAX_BODY_LENGTH);
    write(fd, &login, sizeof(send_t));
}