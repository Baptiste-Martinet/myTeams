/*
** EPITECH PROJECT, 2020
** send_struct1.c
** File description:
** send_struct1
*/

#include "client.h"

void send_messages(char ** param, int fd)
{
    send_uuidx1(param, MESSAGES, fd);
}

void send_subscribe(char ** param, int fd)
{
    send_uuidx1(param, SUBSCRIBE, fd);
}

void send_subscribed(char ** param, int fd)
{
    uuidx1_t login = {
        .header = {
            .code = SUBSCRIBED,
            .size = sizeof(uuidx1_t)
        },
        .uuid = {0}
    };

    if (ptr_number((void **)param) >= 2)
        write_on_struct(login.uuid, param[1], UUID_LENGHT);
    write(fd, &login, sizeof(uuidx1_t));
}

void send_unsubscribe(char ** param, int fd)
{
    send_uuidx1(param, UNSUBSCRIBE, fd);
}

void send_use(char ** param, int fd)
{
    use_t login = {
        .header = {
            .code = USE,
            .size = sizeof(use_t)
        },
        .nb_uuid_defined = ptr_number((void **)param) - 1,
        .uuids = {{0}, {0}, {0}}
    };

    (ptr_number((void **)param) >= 2) ? \
write_on_struct(login.uuids[0], param[1], UUID_LENGHT) : 0;
    (ptr_number((void **)param) >= 3) ? \
write_on_struct(login.uuids[1], param[2], UUID_LENGHT) : 0;
    if (ptr_number((void **)param) >= 4)
        write_on_struct(login.uuids[2], param[3], UUID_LENGHT);
    write(fd, &login, sizeof(use_t));
}