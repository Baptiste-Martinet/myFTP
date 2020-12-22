/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** file_utils
*/

#include "myftp.h"

bool is_file_exist(char *filepath)
{
    if (access(filepath, F_OK) != -1)
        return (true);
    return (false);
}

bool is_directory(char *filepath)
{
    struct stat sb;

    if (stat(filepath, &sb) == -1)
        return (false);
    if ((sb.st_mode & S_IFMT) == S_IFDIR)
        return (true);
    return (false);
}

char *get_absolute_path(char *working_dir)
{
    char buf[PATH_MAX];
    char *absolute_path;

    bzero(buf, PATH_MAX);
    if (!is_directory(working_dir))
        realpath(".", buf);
    else
        realpath(working_dir, buf);
    absolute_path = strdup(buf);
    return (absolute_path);
}

char *get_parent_dir(char *child_dir)
{
    char *parent_dir;
    size_t size;

    if (!child_dir)
        return (NULL);
    if (strcmp(child_dir, "./") == 0)
        return (NULL);
    size = strlen(child_dir);
    for (size_t i = 0; child_dir[i] != '\0'; i++) {
        if (child_dir[i] == '/' && i != (strlen(child_dir) - 1))
            size = i + 1;
    }
    parent_dir = malloc(sizeof(char) * (size + 1));
    if (!parent_dir)
        return (NULL);
    for (size_t j = 0; j < size; j++)
        parent_dir[j] = child_dir[j];
    parent_dir[size] = '\0';
    return (parent_dir);
}