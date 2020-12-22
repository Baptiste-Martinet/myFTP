/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** list
*/

#include "myftp.h"

static bool my_shitty_ls(int fd, char *filepath)
{
    int tmp;

    tmp = dup(1);
    dup2(fd, 1);
    system(my_strcat(my_strcat("ls -l ", filepath), " | grep -v ^total"));
    dup2(tmp, 1);
    close(tmp);
    return (true);
}

static void fork_list(int client_fd, client_t *client, char *filepath)
{
    int pid = fork();
    int distant_fd;

    if (manage_fork_parent(pid, client) != 0)
        return;
    setsid();
    if (!is_directory(filepath)) {
        dprintf(client_fd, "552 No such file or directory\r\n");
        exit(EXIT_FAILURE);
    }
    if ((distant_fd = manage_transfer_mode(client)) == -1)
        exit(EXIT_FAILURE);
    dprintf(client_fd, "150 File status okay; Opening data connection.\r\n");
    my_shitty_ls(distant_fd, filepath);
    close(client->transfer_socket->fd);
    close(distant_fd);
    dprintf(client_fd, "226 Closing data connection.\r\n");
    exit(0);
}

int cmd_list(int client_fd, global_t *glob, char **command)
{
    client_t *client = list_get_client(glob->clients, client_fd);

    if (!check_client(client_fd, client, true))
        return (84);
    fork_list(client_fd, client, (array_len(command) >= 2 ?
        my_strcat(client->working_dir, command[1]) : client->working_dir));
    return (0);
}