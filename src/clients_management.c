/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** clients_management
*/

#include "myftp.h"

static bool add_new_client(int server_fd, fd_set *active_fd_set,
    global_t *glob)
{
    struct sockaddr_in client_sock;
    size_t size;
    int new_client_fd;

    size = sizeof(client_sock);
    new_client_fd = accept(server_fd,
        (struct sockaddr *)&client_sock, (socklen_t *)&size);
    if (new_client_fd < 0) {
        fprintf(stderr, "accept a cassé\n");
        return (false);
    }
    fprintf(stderr, "New connection\n");
    list_add_client(&glob->clients, new_client_fd, glob->server_path);
    FD_SET(new_client_fd, active_fd_set);
    dprintf(new_client_fd, "220 Service ready for new user.\r\n");
    return (true);
}

static void clients_queue(int server_fd, fd_set *read_fd_set,
                            fd_set *active_fd_set, global_t *glob)
{
    for (int client_fd = 0; client_fd < FD_SETSIZE; ++client_fd) {
        if (!FD_ISSET(client_fd, read_fd_set))
            continue;
        if (client_fd == server_fd) {
            add_new_client(server_fd, active_fd_set, glob);
        } else {
            if (read_from_client(client_fd, glob) < 0) {
                dprintf(client_fd, "221 Goodbye.\r\n");
                FD_CLR(client_fd, active_fd_set);
                list_del_client(&glob->clients, client_fd);
            }
        }
    }
}

int clients_manager_loop(int port, char *server_path)
{
    socket_t *server_socket = create_socket(port, IP, true);
    fd_set active_fd_set;
    fd_set read_fd_set;
    global_t glob = {strdup(server_path), NULL};

    if (!server_socket)
        return (84);
    start_listening_socket(server_socket);
    FD_ZERO(&active_fd_set);
    FD_SET(server_socket->fd, &active_fd_set);
    while (1) {
        read_fd_set = active_fd_set;
        if (select(FD_SETSIZE, &read_fd_set, NULL, NULL, NULL) < 0)
            exit(84);
        clients_queue(server_socket->fd, &read_fd_set, &active_fd_set, &glob);
    }
    close(server_socket->fd);
    return (0);
}