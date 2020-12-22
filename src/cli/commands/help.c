/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** string_utils
*/

#include "client.h"

int help_command(char * parameters, account_t * account)
{
    char * msg = load_file_in_mem("./src/cli/commands/help_msg");

    printf("%s\n", msg);
    free(msg);
    return UNKNOWN_COMMAND;
}