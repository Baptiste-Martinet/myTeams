/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** string_utils
*/

#include "client.h"
#include <sys/ioctl.h>

void client_loop(int distant_fd)
{
    account_t account = {NULL, {0}, distant_fd, -1, NULL};

    while (!stop_the_program(false)) {
        printf("[CLIENT] > ");
        fflush(stdout);
        if (read_server_and_client(distant_fd, &account, true) == EXIT_FAILURE)
            break;
    }
    (account.username != NULL) ? free(account.username) : 0;
}

client_socket_t create_socket(const char * ip, uint16_t port)
{
    client_socket_t w;
    w.distant_fd = 0;
    w.error = true;

    w.distant_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (w.distant_fd < 0)
        return w;
    bzero(&(w.distant_sock), sizeof(w.distant_sock));
    w.distant_sock.sin_family = AF_INET;
    if (inet_aton(ip, (struct in_addr *)&(w.distant_sock.sin_addr.s_addr)) == 0)
        return w;
    w.distant_sock.sin_port = htons(port);
    if (connect(w.distant_fd, (struct sockaddr *)&(w.distant_sock), \
sizeof(w.distant_sock)) != 0)
        return w;
    w.error = false;
    return w;
}

void close_socket(client_socket_t * w)
{
    close(w->distant_fd);
    more_pipe(3);
}