/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** server_creation
*/

#include "myftp.h"

static socket_t *configure_socket(socket_t *my_socket)
{
    socklen_t len = sizeof(my_socket->socket);

    if (bind(my_socket->fd, (struct sockaddr *)&my_socket->socket,
                                    sizeof(my_socket->socket)) != 0) {
        fprintf(stderr, "Bind failed.\n");
        return (NULL);
    } else fprintf(stderr, "Socket succesfully binded\n");
    if (getsockname(my_socket->fd, (struct sockaddr *)&my_socket->socket,
                                                            &len) == -1) {
        perror("getsockname");
        return (NULL);
    }
    return (my_socket);
}

socket_t *create_socket(uint16_t port, char *ip, bool is_passiv)
{
    socket_t *my_socket = malloc(sizeof(socket_t));
    int opt = 1;

    if ((my_socket->fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        fprintf(stderr, "Error creating the TCP socket.\n");
        return (NULL);
    } else
        fprintf(stderr, "Socket succesfully created\n");
    bzero(&my_socket->socket, sizeof(my_socket->socket));
    if(setsockopt(my_socket->fd, SOL_SOCKET, SO_REUSEADDR,
                                (char *)&opt, sizeof(opt)) < 0)
        return (NULL);
    my_socket->socket.sin_family = AF_INET;
    my_socket->socket.sin_addr.s_addr = INADDR_ANY;
    if (inet_aton(ip,
        (struct in_addr *)&my_socket->socket.sin_addr.s_addr) == 0)
        return (NULL);
    my_socket->socket.sin_port = htons(port);
    if (!is_passiv)
        return (my_socket);
    return (configure_socket(my_socket));
}