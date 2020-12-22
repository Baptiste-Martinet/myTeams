/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** string_utils
*/

#include "client.h"

int verify_arguments(char * line)
{
    bool good_count = true;
    bool minimum_quote = false;

    for (int i = 0; line[i] != 0; ++i) {
        if (line[i] == '\"') {
            good_count = !good_count;
            minimum_quote = true;
        }
    }
    if (!good_count || !minimum_quote)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}