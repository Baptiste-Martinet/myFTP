/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** my_ls
*/

#include "myftp.h"

static bool print_info_file(int fd, struct stat sb, char *file_name)
{
    struct group *grp;
    time_t curtime;
    char *tim;

    curtime = sb.st_mtime;
    if (!(tim = ctime(&curtime)))
        return (false);
    dprintf(fd, "%c%c%c%c%c%c%c%c%c%c. %ld %s %s %ld\t%c%c %c%c%c." \
        " %c%c%c%c%c %s\n", ((sb.st_mode & S_IFMT) == S_IFDIR ? 'd' : '-'),
        (sb.st_mode & S_IRUSR ? 'r' : '-'), (sb.st_mode & S_IWUSR ? 'w' : '-')
        , (sb.st_mode & S_IXUSR ? 'x' : '-'),
        (sb.st_mode & S_IRGRP ? 'r' : '-'), (sb.st_mode & S_IWGRP ? 'w' : '-')
        , (sb.st_mode & S_IXGRP ? 'x' : '-'),
        (sb.st_mode & S_IROTH ? 'r' : '-'), (sb.st_mode & S_IWOTH ? 'w' : '-')
        , (sb.st_mode & S_IXOTH ? 'x' : '-'), sb.st_nlink, pws->pw_name,
        ((grp = getgrgid(sb.st_gid)) ? grp->gr_name : pws->pw_name),
        sb.st_size, tim[8], tim[9], tim[4], tim[5], tim[6], tim[11], tim[12],
        tim[13], tim[14], tim[15], file_name);
    return (true);
}

static bool manage_info_file(int fd, char *filepath, char *file_name)
{
    struct stat sb;
    struct passwd *pws;

    if (stat(my_strcat(my_strcat(filepath, "/"), file_name), &sb) == -1)
            return (false);
    if (!(pws = getpwuid(sb.st_uid)))
        return (false);
    return (print_info_file(fd, sb, file_name));
}

bool my_ls(int fd, char *filepath)
{
    struct dirent *lect;
    DIR *rep;

    if (!(rep = opendir(filepath)))
        return (false);
    while ((lect = readdir(rep))) {
        if (lect->d_name[0] == '.')
            continue;
        if (!manage_info_file(fd, filepath, lect->d_name))
            return (false);
    }
    closedir(rep);
    return (true);
}