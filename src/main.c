/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** main
*/

#include "myftp.h"

int main(int ac, char **av)
{
    if (ac != 3) {
        fprintf(stderr, "Usage: ./my_ftp PORT PATH\n");
        return (84);
    }
    if (!is_num(av[1]))
        return (84);
    if (chdir(av[2]) != 0)
        return (84);
    return (clients_manager_loop(atoi(av[1]), av[2]));
}