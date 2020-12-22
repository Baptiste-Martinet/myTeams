/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** string_utils
*/

#include "common.h"

bool stop_the_program(bool set)
{
    static bool stop = false;

    if (set) {
        stop = true;
    }
    return stop;
}

int more_pipe(int mode)
{
    static char * my_fifo = "./fifo";
    static bool done = false;
    static int fd = 0;
    static bool closed = false;

    (mode == 5) ? fd = -42 : 0;
    if (fd == -42)
        return fd;
    if (closed || !done) {
        mkfifo(my_fifo, 0777);
        fd = open(my_fifo, O_RDWR);
        done = true;
        closed = false;
    }
    if (mode == 3) {
        close(fd);
        closed = true;
        remove(my_fifo);
    }
    return fd;
}