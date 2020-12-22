/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** port
*/

#include "myftp.h"

static int port_helper(int client_fd, client_t *client, char **host_port)
{
    int port;
    char *ip;

    port = (atoi(host_port[4]) * 256) + atoi(host_port[5]);
    if (!(ip = malloc(sizeof(char) * 50)))
        return (84);
    bzero(ip, 50);
    snprintf(ip, 50, "%s.%s.%s.%s", host_port[0], host_port[1],
                                    host_port[2], host_port[3]);
    if (client->transfer_socket) {
        close (client->transfer_socket->fd);
        client->transfer_socket = NULL;
    }
    if (!(client->transfer_socket = create_socket(port, ip, false))) {
        dprintf(client_fd, "550 random error code port create\r\n");
        return (84);
    }
    client->transfer_mode = 2;
    free(ip);
    dprintf(client_fd, "200 PORT okay.\r\n");
    return (0);
}

int cmd_port(int client_fd, global_t *glob, char **command)
{
    client_t *client = list_get_client(glob->clients, client_fd);
    char **host_port;

    if (!check_client(client_fd, client, false))
        return (84);
    if (array_len(command) < 2) {
        dprintf(client_fd, "550 Port needed after PORT command\r\n");
        return (84);
    }
    if (!(host_port = str_to_word_array(command[1], " \t\r\n.,)(")) ||
        array_len(host_port) < 6) {
        dprintf(client_fd, "550 random port error code\r\n");
        return (84);
    }
    for (int i = 0; host_port[i] && i < 6; i++)
        if (!is_num(host_port[i]))
            return (84);
    return (port_helper(client_fd, client, host_port));
}