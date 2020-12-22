/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** string_utils
*/

#include "common.h"

char * multi_tok(char * input, const char * delimiter)
{
    static char *string;
    char * temp = NULL;
    char * end = NULL;

    if (input != NULL)
        string = input;
    if (string == NULL)
        return string;
    end = strstr(string, delimiter);
    if (end == NULL) {
        temp = (string != NULL && string[0] != 0) ? strdup(string) : NULL;
        string = NULL;
        return temp;
    }
    temp = strdup(string);
    end += strlen(delimiter);
    temp[end - string] = 0;
    string = end;
    return temp;
}

char * multi_tok_no_delim(char * input, const char * delimiter)
{
    static char *string;
    char * temp = NULL;
    char * end = NULL;

    if (input != NULL)
        string = input;
    if (string == NULL)
        return string;
    end = strstr(string, delimiter);
    if (end == NULL) {
        temp = (string != NULL && string[0] != 0) ? strdup(string) : NULL;
        string = NULL;
        return temp;
    }
    temp = strdup(string);
    end += strlen(delimiter);
    temp[end - string - strlen(delimiter)] = 0;
    string = end;
    return temp;
}

char ** split_no_delim(char * line, const char * delimiter)
{
    char * token = multi_tok_no_delim(line, delimiter);
    char ** res = NULL;

    if (line == NULL || token == NULL)
        return NULL;
    res = malloc(sizeof(char *));
    for (int tabsize = 1; token != NULL;) {
        res = realloc(res, sizeof(char *) * (tabsize + 1));
        res[tabsize - 1] = strdup(token);
        res[tabsize++] = NULL;
        free(token);
        token = multi_tok_no_delim(NULL, delimiter);
    }
    return res;
}

size_t ptr_number(void ** split)
{
    size_t nb = 0;

    for (; split[nb] != NULL; ++nb);
    return nb;
}

int contains(const char * str, const char * str1)
{
    int x = 0;
    int count = 0;

    if (str == NULL || str1 == NULL)
        return 0;
    for (size_t i = 0; str[i] != 0; ++i) {
        x = ((str[i] == str1[x]) ? x + 1 : 0);
        if (str1[x] == 0) {
            ++count;
            x = 0;
        }
    }
    return count;
}