/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** cdup
*/

#include "myftp.h"

int cmd_cdup(int client_fd, global_t *glob, char **command)
{
    client_t *client = list_get_client(glob->clients, client_fd);
    char *parent_path;

    (void)command;
    if (!check_client(client_fd, client, false))
        return (84);
    if (strlen(client->working_dir) < 2 ||
                    !(parent_path = get_parent_dir(client->working_dir))) {
        dprintf(client_fd, "552 Can't access lower than root folder\r\n");
        return (84);
    }
    client->working_dir = parent_path;
    dprintf(client_fd, "200 CDUP okay.\r\n");
    return (0);
}