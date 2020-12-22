/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** string_utils
*/

#include "server.h"

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