/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** client_reader
*/

#include "myftp.h"

static flags_t cmd_array[] = {
    {"USER", &cmd_user},
    {"PASS", &cmd_pass},
    {"CWD", &cmd_cwd},
    {"CDUP", &cmd_cdup},
    {"QUIT", &cmd_quit},
    {"DELE", &cmd_dele},
    {"PWD", &cmd_pwd},
    {"PASV", &cmd_pasv},
    {"PORT", &cmd_port},
    {"HELP", &cmd_help},
    {"NOOP", &cmd_noop},
    {"RETR", &cmd_retr},
    {"STOR", &cmd_stor},
    {"LIST", &cmd_list},
    {NULL, NULL}
};

bool manage_client_buffer(int client_fd, char *buffer, client_t *client)
{
    int buffer_len;

    if (!client) {
        dprintf(client_fd, "530 Permission denied.\r\n");
        return (false);
    }
    if (!buffer)
        return (false);
    buffer_len = strlen(buffer);
    client->cmd_buffer = my_strcat(client->cmd_buffer, buffer);
    if (buffer_len < 2)
        return (false);
    if (buffer[buffer_len - 2] == '\r' && buffer[buffer_len - 1] == '\n') {
        return (true);
    }
    return (false);
}

static int manage_client_input(int client_fd, char *buffer, global_t *glob)
{
    client_t *client = list_get_client(glob->clients, client_fd);
    char **command;

    if (!manage_client_buffer(client_fd, buffer, client))
        return (0);
    if (strlen(client->cmd_buffer) > 0 && client->cmd_buffer[0] == ' ') {
        dprintf(client_fd, "500 Unknown command.\r\n");
        client->cmd_buffer = NULL;
        return (0);
    }
    command = str_to_word_array(client->cmd_buffer, " \t\r\n");
    client->cmd_buffer = NULL;
    free(buffer);
    if (!command || array_len(command) < 1)
        return (84);
    for (int i = 0; cmd_array[i].command; i++) {
        if (strcmp(cmd_array[i].command, str_to_upper(command[0])) == 0)
            return (cmd_array[i].func(client_fd, glob, command));
    }
    dprintf(client_fd, "500 Unknown command.\r\n");
    return (0);
}

int read_from_client(int client_fd, global_t *glob)
{
    char *buffer = malloc(MAXMSG);
    int nbytes;

    bzero(buffer, MAXMSG);
    nbytes = read(client_fd, buffer, MAXMSG);
    if (nbytes <= 0) {
        return (-1);
    } else {
        fprintf(stderr, "Server: got message: %s", buffer);
        return (manage_client_input(client_fd, buffer, glob));
    }
}