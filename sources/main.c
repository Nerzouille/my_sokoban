/*
** EPITECH PROJECT, 2023
** sokoban
** File description:
** sokoban main
*/

#include <ncurses.h>
#include "../include/my.h"
#include "soko.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

int player_finder(struct soko *soko, int i)
{
    for (int j = 0; j < soko->col; j++) {
        if (soko->map[i][j] == 'P') {
            soko->i = i;
            soko->j = j;
            return 0;
        }
    }
}

int find_player(struct soko *soko)
{
    for (int i = 0; i < soko->lines; i++) {
        player_finder(soko, i);
    }
    return 1;
}

static int free_a(struct soko *soko)
{
    free(soko->screen);
    for (int i = soko->lines; i > 0; i--)
        free(soko->map[i]);
    free(soko->map);
}

int main(int argc, char *argv[])
{
    struct soko soko = {.col = 0, .lines = 0, .iso = 0,
        .c_s_size = 1, .box_nbr = 0};
    int getch = err_hand(argc, argv, &soko);

    if (getch != 0)
        return getch;
    while (1) {
        getch = getch();
        mv_tab(&soko, getch);
        clear();
        tab_print(&soko, argc, argv, getch);
        if (soko.end == 42 || soko.end == 43 || soko.end == 4)
            break;
        refresh();
    }
    endwin();
    if (soko.end == 43)
        return 1;
    free_a(&soko);
    return 0;
}
