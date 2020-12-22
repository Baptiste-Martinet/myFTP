/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** str_to_word_array
*/

#include "myftp.h"

static bool is_delim(char c, char *delims)
{
    if (!delims)
        return (false);
    for (int i = 0; delims[i] != '\0'; i++)
        if (delims[i] == c)
            return (true);
    return (false);
}

static int get_nb_words(char *str, char *delims)
{
    int nb_words = 0;
    bool last_was_delim = true;

    for (int i = 0; str[i] != '\0'; i++) {
        if (!is_delim(str[i], delims)) {
            if (last_was_delim) {
                nb_words++;
                last_was_delim = false;
            }
        } else {
            last_was_delim = true;
        }
    }
    return (nb_words);
}

static int get_word_length(char *str, int pos, char *delims)
{
    int size = pos;

    for (; str[size] != '\0' &&
                    !is_delim(str[size], delims); size++);
    return (size - pos);
}

char **str_to_word_array(char *str, char *delims)
{
    int nb_words = get_nb_words(str, delims);
    char **array = malloc(sizeof(char *) * (nb_words + 1));
    int idx = 0;
    int word_len;

    if (!str || !delims)
        return (NULL);
    array[nb_words] = NULL;
    for (int i = 0; str[i] != '\0'; i++) {
        if (is_delim(str[i], delims))
            continue;
        word_len = get_word_length(str, i, delims);
        array[idx] = malloc(sizeof(char) * (word_len + 1));
        for (int j = 0; j < word_len; j++)
            array[idx][j] = str[i + j];
        array[idx][word_len] = '\0';
        idx++;
        i += word_len;
    }
    return (array);
}

int array_len(char **array)
{
    int size = 0;

    if (!array)
        return (-1);
    for (; array[size] != NULL; size++);
    return (size);
}