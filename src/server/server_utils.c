/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** server_creation
*/

#include "server.h"

int connect_to_socket(socket_t *my_socket)
{
    if (!my_socket)
        return (-1);
    if (connect(my_socket->fd, (struct sockaddr *)&my_socket->socket, \
sizeof(my_socket->socket)) != 0) {
        puts("Connection to the peer failed.");
        return (-1);
    }
    return (my_socket->fd);
}

int start_listening_socket(socket_t *my_socket)
{
    if (!my_socket)
        return (84);
    if (listen(my_socket->fd, CLIENT_NUMBER) != 0) {
        return (84);
    } else {
        puts("Server listening...");
    }
    return (0);
}

int accept_from_socket(socket_t *my_socket)
{
    int distant_fd;
    int len = sizeof(my_socket->socket);

    if (!my_socket)
        return (-1);
    if ((distant_fd = accept(my_socket->fd, \
(struct sockaddr *)&my_socket->socket, (socklen_t *)&len)) < 0) {
        puts("Local accept failed.");
        return (-1);
    }
    return (distant_fd);
}

static socket_t *configure_socket(socket_t *my_socket)
{
    socklen_t len = sizeof(my_socket->socket);

    if (bind(my_socket->fd, (struct sockaddr *)&my_socket->socket, \
sizeof(my_socket->socket)) != 0) {
        puts("Bind failed.");
        return (NULL);
    } else puts("Socket succesfully binded");
    if (getsockname(my_socket->fd, (struct sockaddr *)&my_socket->socket, \
&len) == -1) {
        perror("getsockname");
        return (NULL);
    }
    return (my_socket);
}

socket_t *create_socket(uint16_t port, bool wanna_bind)
{
    socket_t *my_socket = malloc(sizeof(socket_t));
    int opt = 1;

    if ((my_socket->fd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        puts("Error creating the TCP socket.");
        return (NULL);
    } else
        puts("Socket succesfully created");
    bzero(&my_socket->socket, sizeof(my_socket->socket));
    if (setsockopt(my_socket->fd, SOL_SOCKET, SO_REUSEADDR, \
(char *)&opt, sizeof(opt)) < 0)
        return (NULL);
    my_socket->socket.sin_family = AF_INET;
    my_socket->socket.sin_addr.s_addr = htonl(INADDR_ANY);
    my_socket->socket.sin_port = htons(port);
    if (!wanna_bind)
        return (my_socket);
    return (configure_socket(my_socket));
}