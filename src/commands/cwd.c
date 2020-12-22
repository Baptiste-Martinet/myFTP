/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** cwd
*/

#include "myftp.h"

int cmd_cwd(int client_fd, global_t *glob, char **command)
{
    client_t *client = list_get_client(glob->clients, client_fd);
    char *new_path;

    if (!check_client(client_fd, client, false))
        return (84);
    if (array_len(command) < 2) {
        dprintf(client_fd, "550 Filepath needed after cwd command\r\n");
        return (84);
    }
    new_path = my_strcat(client->working_dir, my_strcat(command[1], "/"));
    if (!new_path || !is_directory(new_path)) {
        dprintf(client_fd, "550 No such file or directory\r\n");
        return (84);
    }
    client->working_dir = new_path;
    dprintf(client_fd, "250 Requested file action okay, completed.\r\n");
    return 0;
}