/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** string_utils
*/

#include "myftp.h"

char *my_strcat(char *s1, char *s2)
{
    char *new_str;
    int i;
    int j;

    if (!s1 && s2)
        return (s2);
    if (s1 && !s2)
        return (s1);
    if (!s1 && !s2)
        return (NULL);
    if (!(new_str = malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1))))
        return (NULL);
    for (i = 0; s1[i] != '\0'; i++)
        new_str[i] = s1[i];
    for (j = 0; s2[j] != '\0'; j++)
        new_str[i + j] = s2[j];
    new_str[i + j] = '\0';
    return (new_str);
}

bool my_ls2(int fd, char *filepath)
{
    char buff[1024];
    FILE *file;

    if (!(file = popen(my_strcat(my_strcat("ls -l ", filepath),
                                        " | grep -v ^total"), "r")))
        return (false);
    while (fread(buff, 1, 1, file) > 0)
        write(fd, buff, 1);
    pclose(file);
    return (true);
}

bool is_num(char *str)
{
    if (!str)
        return (false);
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || '9' < str[i])
            return (false);
    }
    return (true);
}

char *str_to_upper(char *str)
{
    if (!str)
        return (str);
    for (int i = 0; str[i] != '\0'; i++) {
        if ('a' <= str[i] && str[i] <= 'z')
            str[i] -= 'a' - 'A';
    }
    return (str);
}

bool my_free_array(char **arr)
{
    if (!arr)
        return (false);
    for (int i = 0; arr[i]; i++)
        free(arr);
    free(arr);
    return (true);
}