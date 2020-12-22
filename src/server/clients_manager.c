/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** clients_management
*/

#include "server.h"

static int add_new_client(int server_fd, fd_set *active_fd_set, \
global_t *glob)
{
    struct sockaddr_in client_sock;
    size_t size = sizeof(client_sock);
    int new_cli_fd;

    if ((new_cli_fd = accept(server_fd, \
(struct sockaddr *)&client_sock, (socklen_t *)&size)) < 0) {
        puts("accept a cassé");
        return (EXIT_FAILURE);
    }
    if (!glob->clients)
        glob->clients = bvector_create(create_client(new_cli_fd), CLIENT);
    else
        bvector_push_back(glob->clients, create_client(new_cli_fd), CLIENT);
    puts("<Server>: New connection !");
    return (EXIT_SUCCESS);
}

static void clients_queue(int server_fd, fd_set *fd_set, global_t *glob)
{
    bvector_t *vec = glob->clients;
    client_t *tmp_cli = NULL;

    if (FD_ISSET(server_fd, fd_set))
        add_new_client(server_fd, fd_set, glob);
    for (; vec; vec = vec->next) {
        tmp_cli = (client_t *)vec->data;
        if (tmp_cli->fd == -1)
            continue;
        if (FD_ISSET(tmp_cli->fd, fd_set)) {
            if (read_from_client(tmp_cli, glob) < 0) {
                disconnect_client(tmp_cli, glob);
            }
        }
    }
}

static int create_fd_set_form_clients(global_t *glob, fd_set *fd_set)
{
    bvector_t *vec = glob->clients;
    int fd_max = glob->server_socket->fd;
    client_t *tmp_cli = NULL;

    FD_ZERO(fd_set);
    FD_SET(glob->server_socket->fd, fd_set);
    for (; vec; vec = vec->next) {
        tmp_cli = (client_t *)vec->data;
        if (tmp_cli->fd == -1)
            continue;
        FD_SET(tmp_cli->fd, fd_set);
        if (tmp_cli->fd > fd_max)
            fd_max = tmp_cli->fd;
    }
    return (fd_max);
}

static int clients_manager_loop(global_t *glob)
{
    fd_set fd_set;
    int fd_max = 0;

    while (!stop_the_program(false)) {
        fd_max = create_fd_set_form_clients(glob, &fd_set);
        //bvector_display(glob->clients);
        if (select(fd_max + 1, &fd_set, NULL, NULL, NULL) < 0)
            break;
        clients_queue(glob->server_socket->fd, &fd_set, glob);
    }
    return (EXIT_SUCCESS);
}

int start_server(int port)
{
    global_t glob = {
        .server_socket = create_socket(port, true),
        .clients = NULL,
        .teams = NULL,
        .messages = NULL,
    };

    if (!glob.server_socket)
        return (EXIT_FAILURE);
    save_loader(&glob);
    start_listening_socket(glob.server_socket);
    clients_manager_loop(&glob);
    save_server(&glob);
    close(glob.server_socket->fd);
    return (EXIT_SUCCESS);
}