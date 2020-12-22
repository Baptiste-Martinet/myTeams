/*
** EPITECH PROJECT, 2020
** rfc_filtering.c
** File description:
** rfc
*/

#include "client.h"

char * time_now_to_string(void)
{
    time_t timee = time(NULL);
    char * buff = malloc(sizeof(char) * 20);

    memset(buff, 0, 20);
    strftime(buff, 20, "%Y/%m/%d %H:%M:%S", localtime(&timee));
    return buff;
}

char * time_to_string(time_t timee)
{
    char * buff = malloc(sizeof(char) * 20);

    memset(buff, 0, 20);
    strftime(buff, 20, "%Y/%m/%d %H:%M:%S", localtime(&timee));
    return buff;
}

time_t string_to_time_t(const char * str)
{
    time_t timee = {0};
    struct tm tmm = {0};

    strptime(str, "%Y/%m/%d %H:%M:%S", &tmm);
    tmm.tm_isdst = -1;
    timee = mktime(&tmm);
    return timee;
}