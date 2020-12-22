/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** fork_utils
*/

#include "myftp.h"

int manage_fork_parent(int pid, client_t *client)
{
    if (pid == -1) {
        fprintf(stderr, "Error: Can't fork");
        return (-1);
    } else if (pid > 0) {
        close(client->transfer_socket->fd);
        client->transfer_socket = NULL;
        client->transfer_mode = 0;
        return (pid);
    }
    return (0);
}

bool check_client(int client_fd, client_t *client, bool check_transfer_mod)
{
    if (!client) {
        dprintf(client_fd, "530 Permission denied.\r\n");
        return (false);
    }
    if (!client->pass) {
        dprintf(client_fd, "530 Please login with USER and PASS.\r\n");
        return (false);
    }
    if (check_transfer_mod && (!client->transfer_socket ||
                                    client->transfer_mode == 0)) {
        dprintf(client_fd, "425 Use PORT or PASV first.\r\n");
        return (false);
    }
    return (true);
}

int manage_transfer_mode(client_t *client)
{
    if (!client->transfer_socket)
        return (-1);
    if (client->transfer_mode == 1) {
        return (accept_from_socket(client->transfer_socket));
    } else if (client->transfer_mode == 2) {
        return (connect_to_socket(client->transfer_socket));
    }
    return (-1);
}