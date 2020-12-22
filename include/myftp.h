/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** myftp
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <zconf.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/sysmacros.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#include <time.h>

#define IP "127.0.0.1"
#define MAXMSG  1023
#define MAX_CLIENTS 1024

typedef struct socket_s {
    struct sockaddr_in socket;
    int fd;
} socket_t;

typedef struct client_s {
    char *id;
    char *pass;
    char *working_dir;
    char *cmd_buffer;
    socket_t *transfer_socket;
    int transfer_mode;
    int fd;
    struct client_s *next;
} client_t;

typedef struct global_s {
    char *server_path;
    client_t *clients;
} global_t;

typedef struct flags_s {
    char *command;
    int (*func)(int client_fd, global_t *glob, char **command);
} flags_t;

typedef struct message_s {
    int code;
    char *format;
} message_t;

/* command functions */

int cmd_user(int client_fd, global_t *glob, char **command);
int cmd_pass(int client_fd, global_t *glob, char **command);
int cmd_cwd(int client_fd, global_t *glob, char **command);
int cmd_cdup(int client_fd, global_t *glob, char **command);
int cmd_quit(int client_fd, global_t *glob, char **command);
int cmd_dele(int client_fd, global_t *glob, char **command);
int cmd_pwd(int client_fd, global_t *glob, char **command);
int cmd_pasv(int client_fd, global_t *glob, char **command);
int cmd_port(int client_fd, global_t *glob, char **command);
int cmd_help(int client_fd, global_t *glob, char **command);
int cmd_noop(int client_fd, global_t *glob, char **command);
int cmd_retr(int client_fd, global_t *glob, char **command);
int cmd_stor(int client_fd, global_t *glob, char **command);
int cmd_list(int client_fd, global_t *glob, char **command);

/* main.c */

/* server_creation.c */

socket_t *create_socket(uint16_t port, char *ip, bool is_passiv);

/*server utils */

int start_listening_socket(socket_t *my_socket);
int accept_from_socket(socket_t *my_socket);
int connect_to_socket(socket_t *my_socket);

/* fork_utils */

int manage_fork_parent(int pid, client_t *client);
bool check_client(int client_fd, client_t *client,
    bool check_transfer_mod);
int manage_transfer_mode(client_t *client);

/* clients_management */

int clients_manager_loop(int port, char *server_path);


/* client_reader.c */

int read_from_client(int client_fd, global_t *glob);
char **get_cleaned_cmd(char *buffer, char *delims);


/* linked list */

void list_add_client(client_t **clients, int fd, char *working_dir);
client_t *list_get_client(client_t *clients, int fd);
void list_del_client(client_t **clients, int fd);
void list_dump(client_t *clients);

/* str_to_word_array.c */

char **str_to_word_array(char *str, char *delims);
int array_len(char **array);

/* string_utils.c */

char *my_strcat(char *s1, char *s2);
bool is_num(char *str);
char *str_to_upper(char *str);
bool my_ls2(int fd, char *filepath);
bool my_free_array(char **arr);

/* file_utils.c */

bool is_file_exist(char *filepath);
char *get_absolute_path(char *working_dir);
bool is_directory(char *filepath);
char *get_parent_dir(char *child_dir);

/* my_ls */
bool my_ls(int fd, char *filepath);