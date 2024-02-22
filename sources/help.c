/*
** EPITECH PROJECT, 2023
** sokoban
** File description:
** sokoban help
*/

#include <ncurses.h>
#include "../include/my.h"
#include "soko.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>


int help(int argc, char *argv[])
{
    char *help_txt = "USAGE\n     ./my_sokoban map\nDESCRIPTION\n"
    "     map  file representing the warehouse map, containing '#'"
    " for walls,\n          'P' for the player, 'X' for boxes and"
    " '0' for storage locations.";

    if (argc == 2 && my_strcmp(argv[1], "-h") == 0) {
        my_printf("%s", help_txt);
        return 1;
    }
    return 0;
}
