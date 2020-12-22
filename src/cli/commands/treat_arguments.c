/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** string_utils
*/

#include "client.h"

static void remove_arg(char ** new_tab, size_t i, size_t nb)
{
    free(new_tab[i]);
    new_tab[i] = NULL;
    for (; i < nb; ++i) {
        new_tab[i] = new_tab[i+1];
    }
}

static void check_empty_arguments(char ** new_tab, size_t nb)
{
    for (size_t i = 0; i < nb; ++i) {
        while (i < nb && (new_tab[i] == NULL || new_tab[i][0] == 0))
            remove_arg(new_tab, i, nb--);
    }
}

static void write_arguments(char ** new_tab, char * line, size_t nb)
{
    bool quote_mode = false;
    size_t x = 0;
    size_t j = 0;

    for (size_t i = 0; line[i] != 0; ++i) {
        (line[i] == '\"') ? quote_mode = !quote_mode : 0;
        if (!quote_mode && (line[i] == ' ' || line[i] == '\t')) {
            ++x;
            j = 0;
        } else {
            (line[i] != '\"') ? new_tab[x][j++] = line[i] : 0;
        }
    }
    check_empty_arguments(new_tab, nb);
}

static char ** malloc_arguments(char * line)
{
    char ** new_tab = NULL;
    size_t nb = (strlen(line) > 0) ? 1 : 0;
    bool quote_mode = false;

    for (size_t i = 0; line[i] != 0; ++i) {
        if (line[i] != '\"' && quote_mode)
            continue;
        (line[i] == '\"') ? quote_mode = !quote_mode : 0;
        if (line[i] == ' ' || line[i] == '\t')
            ++nb;
    }
    new_tab = malloc(sizeof(char *) * (nb + 1));
    for (size_t i = 0; i < nb; ++i) {
        new_tab[i] = malloc(sizeof(char) * (strlen(line) + 1));
        memset(new_tab[i], 0, strlen(line) + 1);
    }
    new_tab[nb] = NULL;
    write_arguments(new_tab, line, nb);
    return new_tab;
}

char ** treat_arguments(char * line)
{
    char ** new_tab = malloc_arguments(line);

    return new_tab;
}