/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** dele
*/

#include "myftp.h"

int cmd_dele(int client_fd, global_t *glob, char **command)
{
    client_t *client = list_get_client(glob->clients, client_fd);
    struct stat sb;

    if (!check_client(client_fd, client, false))
        return (84);
    if (array_len(command) < 2) {
        dprintf(client_fd, "550 Filepath needed after cwd command\r\n");
        return (84);
    }
    if (stat(my_strcat(client->working_dir, command[1]), &sb) == -1 ||
                                                    !S_ISREG(sb.st_mode)) {
        dprintf(client_fd, "550 Can't delete this file\r\n");
        return (84);
    }
    if (remove(my_strcat(client->working_dir, command[1])) != 0) {
        dprintf(client_fd, "550 Can't delete file\r\n");
        return (84);
    }
    dprintf(client_fd, "250 Requested file action okay, completed.\r\n");
    return (0);
}