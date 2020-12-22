/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** user
*/

#include "myftp.h"

int cmd_user(int client_fd, global_t *glob, char **command)
{
    client_t *client = list_get_client(glob->clients, client_fd);

    if (!client) {
        dprintf(client_fd, "530 Permission denied.\r\n");
        return (84);
    }
    if (array_len(command) < 2) {
        dprintf(client_fd, "501 Username needed after user command\r\n");
        return (84);
    }
    if (client->id) {
        dprintf(client_fd, "553 Already logged in, please log out\r\n");
        return (84);
    }
    client->id = strdup(command[1]);
    dprintf(client_fd, "331 Please specify the password.\r\n");
    return (0);
}