/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** server_utils
*/

#include "myftp.h"

int start_listening_socket(socket_t *my_socket)
{
    if (!my_socket)
        return (84);
    if (listen(my_socket->fd, MAX_CLIENTS) != 0) {
        return (84);
    } else {
        printf("Server listening...\n");
    }
    return (0);
}

int accept_from_socket(socket_t *my_socket)
{
    int distantFd;
    int len = sizeof(my_socket->socket);

    if (!my_socket)
        return (-1);
    if ((distantFd = accept(my_socket->fd,
            (struct sockaddr *)&my_socket->socket, (socklen_t *)&len)) < 0) {
        fprintf(stderr, "Local accept failed.");
        return (-1);
    }
    return (distantFd);
}

int connect_to_socket(socket_t *my_socket)
{
    if (!my_socket)
        return (-1);
    if (connect(my_socket->fd, (struct sockaddr *)&my_socket->socket,
                                        sizeof(my_socket->socket)) != 0) {
        fprintf(stderr, "Connection to the peer failed.");
        return (-1);
    }
    return (my_socket->fd);
}