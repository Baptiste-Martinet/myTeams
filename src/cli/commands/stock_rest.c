/*
** EPITECH PROJECT, 2020
** send_struct1.c
** File description:
** send_struct1
*/

#include "client.h"

void stock_rest(char ** tab, int index, account_t * account)
{
    int length = 1;

    for (int i = index; tab[i] != NULL; ++i)
        length += strlen(tab[i]);
    account->old_buffer = malloc(sizeof(char) * length);
    memset(account->old_buffer, 0, length);
    for (; tab[index] != NULL; ++index)
        strcat(account->old_buffer, tab[index]);
}