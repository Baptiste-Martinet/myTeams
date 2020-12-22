/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** saver
*/

#include "database.h"

int save_server(global_t *glob)
{
    int file = open("database", O_CREAT | O_RDWR, 0644);

    if (file < 0) {
        puts("Error while creating/opening database.txt !");
        return (EXIT_FAILURE);
    }
    puts("\033[0;32mSaving server datas...\033[0m");
    save_teams(file, glob);
    save_messages(file, glob);
    save_clients(file, glob);
    puts("\033[0;32m<Saver>: Server successfully saved!\033[0m");
    close(file);
    return (EXIT_SUCCESS);
}