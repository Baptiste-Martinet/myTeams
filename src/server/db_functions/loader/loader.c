/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** loader
*/

#include "database.h"

static resource_type_t db_types_array[] = {
    {DB_TEAM, &load_team},
    {DB_CHANNEL, &load_channel},
    {DB_THREAD, &load_thread},
    {DB_REPLY, &load_reply},
    {DB_MESSAGE, &load_message},
    {DB_CLIENT, &load_client},
    {DB_SUB, &load_client_sub},
    {DB_TEAM, NULL}
};

static int load_resource(global_t *glob, void *buffer, db_loader_t *loader)
{
    db_header_t *header = (db_header_t *)buffer;

    for (size_t i = 0; db_types_array[i].func; ++i) {
        if (header->type == db_types_array[i].type) {
            return (db_types_array[i].func(glob, header, loader));
        }
    }
    return (EXIT_FAILURE);
}

static int binary_parse_file(int file, global_t *glob, db_loader_t *loader)
{
    void *buffer = malloc(1023);
    int red = 0;
    int nbytes;

    while (true) {
        nbytes = read(file, buffer + red, (red < sizeof(db_header_t) ? \
sizeof(db_header_t) : ((db_header_t *)buffer)->size) - red);
        if (nbytes <= 0)
            break;
        red += nbytes;
        if (red < sizeof(db_header_t))
            continue;
        if (red < ((db_header_t *)buffer)->size)
            continue;
        red = 0;
        load_resource(glob, buffer, loader);
    }
    puts("\033[0;32m<Loader>: Loading completed successfully\033[0m");
    free(buffer);
    return (EXIT_SUCCESS);
}

int save_loader(global_t *glob)
{
    int file = open("database", O_RDWR, 0644);
    db_loader_t loader = {
        .team = NULL, .channel = NULL, .thread = NULL, .client = NULL,
    };

    if (file < 0) {
        puts("\033[0;32m<Loader>: Can't find any database to load\033[0m");
        return (EXIT_FAILURE);
    }
    puts("\033[0;32m<Loader>: Loading database...\033[0m");
    return (binary_parse_file(file, glob, &loader));
}