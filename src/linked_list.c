/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** linked_list
*/

#include "myftp.h"

void list_add_client(client_t **clients, int fd, char *working_dir)
{
    client_t *new_elem = malloc(sizeof(client_t));
    client_t *temp = *clients;

    (void)working_dir;
    if (!new_elem)
        return;
    new_elem->id = NULL;
    new_elem->pass = NULL;
    new_elem->fd = fd;
    new_elem->working_dir = strdup("./");
    new_elem->cmd_buffer = NULL;
    new_elem->transfer_socket = NULL;
    new_elem->transfer_mode = 0;
    new_elem->next = NULL;
    if (!temp) {
        (*clients) = new_elem;
        return;
    }
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = new_elem;
}

client_t *list_get_client(client_t *clients, int fd)
{
    while (clients) {
        if (clients->fd == fd)
            return (clients);
        clients = clients->next;
    }
    return (NULL);
}

bool delete_client(client_t *client)
{
    if (!client)
        return (false);
    close(client->fd);
    if (client->transfer_socket)
        close(client->transfer_socket->fd);
    if (client->id)
        free(client->id);
    if (client->pass)
        free(client->pass);
    if (client->cmd_buffer)
        free(client->cmd_buffer);
    if (client->working_dir)
        free(client->working_dir);
    free(client);
    return (true);
}

void list_del_client(client_t **clients, int fd)
{
    client_t *temp = *clients;
    client_t *to_free;

    if (!temp)
        return;
    if (temp->fd == fd) {
        *clients = (*clients)->next;
        delete_client(temp);
        return;
    }
    while (temp->next) {
        if (temp->next->fd == fd) {
            to_free = temp->next;
            temp->next = temp->next->next;
            delete_client(to_free);
            break;
        }
        temp = temp->next;
    }
}

void list_dump(client_t *clients)
{
    printf("Dumping list:\n");
    while (clients) {
        printf("elem: %d\n", clients->fd);
        clients = clients->next;
    }
    printf("\n");
}