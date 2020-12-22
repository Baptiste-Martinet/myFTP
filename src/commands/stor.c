/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** stor
*/

#include "myftp.h"

static void store_helper(int client_fd, int target, int distant_fd,
                                                    client_t *client)
{
    void *buff;
    int last_read_val;

    if (!(buff = malloc(MAXMSG)))
        exit(EXIT_FAILURE);
    bzero(buff, MAXMSG);
    while ((last_read_val = read(distant_fd, buff, MAXMSG)) > 0)
        write(target, buff, last_read_val);
    free(buff);
    close(target);
    close(distant_fd);
    close(client->transfer_socket->fd);
    if (last_read_val == -1)
        dprintf(client_fd, "550 Couldn't complete storing\r\n");
    else
        dprintf(client_fd, "226 Closing data connection.\r\n");
    exit(0);
}

static void fork_store(int client_fd, client_t *client, char *filepath)
{
    int pid = fork();
    int target;
    int distant_fd;

    if (manage_fork_parent(pid, client) != 0)
        return;
    setsid();
    if ((target = open(filepath, O_CREAT | O_TRUNC | O_RDWR, 0666)) == -1) {
        dprintf(client_fd, "550 Failed to open file.\r\n");
        exit(EXIT_FAILURE);
    }
    if ((distant_fd = manage_transfer_mode(client)) == -1) {
        dprintf(client_fd, "425 problem with connection.\r\n");
        exit(EXIT_FAILURE);
    }
    dprintf(client_fd, "150 File status okay; Opening data connection.\r\n");
    store_helper(client_fd, target, distant_fd, client);
}

int cmd_stor(int client_fd, global_t *glob, char **command)
{
    client_t *client = list_get_client(glob->clients, client_fd);

    if (!check_client(client_fd, client, true))
        return (84);
    if (array_len(command) < 2) {
        dprintf(client_fd, "501 You must select a file to upload\r\n");
        return (84);
    }
    fork_store(client_fd, client, my_strcat(client->working_dir, command[1]));
    return (0);
}