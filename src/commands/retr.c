/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** retr
*/

#include "myftp.h"

static void retr_helper(int client_fd, int target, int distant_fd,
                                                    client_t *client)
{
    void *buff;
    int last_read_value;

    if (!(buff = malloc(MAXMSG)))
        exit(EXIT_FAILURE);
    bzero(buff, MAXMSG);
    dprintf(client_fd, "150 File status okay; Opening data connection.\r\n");
    while ((last_read_value = read(target, buff, MAXMSG)) > 0)
        write(distant_fd, buff, last_read_value);
    free(buff);
    close(target);
    close(distant_fd);
    close(client->transfer_socket->fd);
    dprintf(client_fd, "226 Closing data connection.\r\n");
    exit(0);
}

static void fork_retr(int client_fd, client_t *client, char *filepath)
{
    int pid = fork();
    int target;
    int distant_fd;

    if (manage_fork_parent(pid, client) != 0)
        return;
    setsid();
    if ((target = open(filepath, O_RDONLY)) == -1) {
        dprintf(client_fd, "550 Failed to open file.\r\n");
        exit(EXIT_FAILURE);
    }
    if ((distant_fd = manage_transfer_mode(client)) == -1) {
        dprintf(client_fd, "425 problem with connection.\r\n");
        exit(EXIT_FAILURE);
    }
    retr_helper(client_fd, target, distant_fd, client);
}

int cmd_retr(int client_fd, global_t *glob, char **command)
{
    client_t *client = list_get_client(glob->clients, client_fd);

    if (!check_client(client_fd, client, true))
        return (84);
    if (array_len(command) < 2) {
        dprintf(client_fd, "501 You must select a file to download\r\n");
        return (84);
    }
    fork_retr(client_fd, client, my_strcat(client->working_dir, command[1]));
    return (0);
}