/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** pwd
*/

#include "myftp.h"

int cmd_pwd(int client_fd, global_t *glob, char **command)
{
    client_t *client = list_get_client(glob->clients, client_fd);

    (void)command;
    if (!check_client(client_fd, client, false))
        return (84);
    dprintf(client_fd, "257 \"%s\"\r\n", client->working_dir + 1);
    return (0);
}