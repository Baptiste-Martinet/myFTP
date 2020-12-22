/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** main
*/

#include "myftp.h"
#include <sys/wait.h>

void test(int fd, char *code)
{
    if (!code)
        exit(EXIT_FAILURE);
    char *buffer = malloc(MAXMSG);

    bzero(buffer, MAXMSG);
    if (read(fd, buffer, MAXMSG) < 0)
        exit(EXIT_FAILURE);
    if (strncmp(buffer, code, strlen(code)) != 0) {
        fprintf(stderr, "Expected: [%s], but received: %s", code, buffer);
        exit(EXIT_FAILURE);
    }
    free(buffer);
}

void run_clients(int port, int max_clients)
{
    struct sockaddr_in distantSock;
    int distantFd;
    char commands[5][16] = {"NOOP", "PASV", "PWD", "CDUP", "HELP"};
    char command_received_codes[5][4] = {"200", "227", "257", "552", "214"};
    int status;
    int r;

    printf("Running %d client(s) on port %d...\n", max_clients, port);
    for(int i = 0; i < max_clients; i++) {
        if(fork() == 0) {
            srand(time(NULL) ^ (getpid()<<16));
            distantFd = socket(AF_INET, SOCK_STREAM, 0);
            if (distantFd < 0) {
                fprintf(stderr, "Error creating the TCP socket, exiting.\n");
                exit(EXIT_FAILURE);
            }
            bzero(&distantSock, sizeof(distantSock));
            distantSock.sin_family = AF_INET;
            if (inet_aton(IP, (struct in_addr *)&distantSock.sin_addr.s_addr) == 0) {
                fprintf(stderr, "Invalid IP, exiting.\n");
                exit(EXIT_FAILURE);
            }
            distantSock.sin_port = htons(port);
            sleep(1);
            if (connect(distantFd, (struct sockaddr *)&distantSock, sizeof(distantSock)) != 0) {
                fprintf(stderr,"Connection to the peer failed, exiting.");
                exit(EXIT_FAILURE);
            }
            sleep(1);
            test(distantFd, "220");
            dprintf(distantFd, "USER Anonymous\r\n");
            test(distantFd, "331");
            sleep(1);
            dprintf(distantFd, "PASS \r\n");
            test(distantFd, "230");
            sleep(1);
            r = rand() % 5;
            dprintf(distantFd, "%s\r\n", commands[r]);
            test(distantFd, command_received_codes[r]);
            sleep(1);
            dprintf(distantFd, "QUIT\r\n");
            test(distantFd, "221");
            close(distantFd);
            exit(EXIT_SUCCESS); 
        } 
    }
    wait(&status);
    if (WIFEXITED(status)){
        if (WEXITSTATUS(status) == EXIT_FAILURE) {
            printf("\x1B[31mTEST FAILED\n");
            exit(84);
        } else {
            printf("\x1B[32mTEST PASSED\n");
            exit(0);
        }
    }
}

int main(int ac, char **av)
{
    if (ac != 3) {
        fprintf(stderr, "USAGE: ./program PORT NB_CLIENTS\n");
        return (84);
    }
    run_clients(atoi(av[1]), atoi(av[2]));
    return (0);
}