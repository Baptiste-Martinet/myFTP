/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** noop
*/

#include "myftp.h"

int cmd_noop(int client_fd, global_t *glob, char **command)
{
    client_t *client = list_get_client(glob->clients, client_fd);

    (void)command;
    if (!check_client(client_fd, client, false))
        return (84);
    dprintf(client_fd, "200 NOOP ok.\r\n");
    return (0);
}