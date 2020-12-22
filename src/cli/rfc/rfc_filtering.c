/*
** EPITECH PROJECT, 2020
** rfc_filtering.c
** File description:
** rfc
*/

#include "client.h"

static int extract_code(char ** line)
{
    int code = EXIT_FAILURE;
    char c[3] = {0, 0, 0};

    if (!isdigit((*line)[0]))
        return EXIT_FAILURE;
    get_last_reponse(*line);
    for (int i = 0; i < 3 && isdigit((*line)[0]); ++i) {
        c[i] = (*line)[0];
        ++(*line);
    }
    if (!isspace((*line)[0]))
        return EXIT_FAILURE;
    ++(*line);
    code = atoi(c);
    return code;
}

int rfc_filtering(char * line, account_t * account)
{
    int code = extract_code(&line);

    if (code == EXIT_FAILURE)
        return EXIT_FAILURE;
    treat_code(code, account, line);
    return EXIT_SUCCESS;
}

int rfc_loop(char * line, account_t * account)
{
    char ** tab = split_no_delim(line, CRLF);
    int ret = EXIT_SUCCESS;

    if (tab == NULL)
        return EXIT_FAILURE;
    for (int i = 0; tab[i] != NULL && ret == EXIT_SUCCESS; ++i) {
        ret = rfc_filtering(tab[i], account);
    }
    free_2darray((void **)tab);
    return ret;
}