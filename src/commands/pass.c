/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** pass
*/

#include "myftp.h"

static int pass_helper(int client_fd, client_t *client, char **command)
{
    if (strcmp(str_to_upper(client->id), "ANONYMOUS") == 0) {
        client->pass = strdup("");
        dprintf(client_fd, "230 Login successful.\r\n");
        return (0);
    }
    if (array_len(command) < 2) {
        dprintf(client_fd, "501 Password needed after user command\r\n");
        return (84);
    }
    client->id = NULL;
    dprintf(client_fd, "530 Wrong id or password\r\n");
    return (0);
}

int cmd_pass(int client_fd, global_t *glob, char **command)
{
    client_t *client = list_get_client(glob->clients, client_fd);

    (void)command;
    if (!client) {
        dprintf(client_fd, "530 Permission denied.\r\n");
        return (84);
    }
    if (!client->id) {
        dprintf(client_fd, "332 Need account for login.\r\n");
        return (84);
    }
    if (client->pass) {
        dprintf(client_fd, "553 Already logged in, please log out\r\n");
        return (84);
    }
    return (pass_helper(client_fd, client, command));
}