/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** pasv
*/

#include "myftp.h"

static char *dots_by_coms(char *str)
{
    if (!str)
        return (NULL);
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '.')
            str[i] = ',';
    }
    return (str);
}

int cmd_pasv(int client_fd, global_t *glob, char **command)
{
    client_t *client = list_get_client(glob->clients, client_fd);
    uint16_t port;

    (void)command;
    if (!check_client(client_fd, client, false))
        return (84);
    if (client->transfer_socket)
        close(client->transfer_socket->fd);
    if (!(client->transfer_socket = create_socket(0, IP, true)))
        return (84);
    if (start_listening_socket(client->transfer_socket) == 84)
        return (84);
    client->transfer_mode = 1;
    port = ntohs(client->transfer_socket->socket.sin_port);
    fprintf(stderr, "pasv port: %d\n", port);
    dprintf(client_fd, "227 Entering Passive Mode (%s,%d,%d).\r\n",
        dots_by_coms(inet_ntoa(client->transfer_socket->socket.sin_addr)),
        port / 256, port % 256);
    return (0);
}