/*
** EPITECH PROJECT, 2020
** send_struct_base.c
** File description:
** copy
*/

#include "client.h"

void write_on_struct(char * dest, char * src, size_t size)
{
    memset(dest, 0, size);
    if (src == NULL || src[0] == 0)
        return;
    memcpy(dest, src, strlen(src));
}