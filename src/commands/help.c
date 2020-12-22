/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** help
*/

#include "myftp.h"

int cmd_help(int client_fd, global_t *glob, char **command)
{
    client_t *client = list_get_client(glob->clients, client_fd);

    (void)command;
    if (!check_client(client_fd, client, false))
        return (84);
    dprintf(client_fd, "214-The following commands are recognized.\n" \
    "\tUSER PASS CWD CDUP QUIT PORT PASV STOR RETR LIST DELE PWD NOOP HELP\n"\
    "214 Help OK.\r\n");
    return (0);
}