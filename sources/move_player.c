/*
** EPITECH PROJECT, 2023
** sokoban
** File description:
** move player sokoban
*/

#include <ncurses.h>
#include "../include/my.h"
#include "soko.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

int mv_b(struct soko *soko, int i, int j, int getch)
{
    int i_cp = i;
    int j_cp = j;

    if (getch == 65)
        i--;
    if (getch == 66)
        i++;
    if (getch == 67)
        j++;
    if (getch == 68)
        j--;
    if (soko->map[i][j] != '#' && soko->map[i][j] != 'X') {
        soko->map[i][j] = 'X';
        if (win(soko, i_cp, j_cp) == 1)
            return 42;
        if (death(soko, i_cp, j_cp) == 1)
            return 43;
        return 0;
    }
    return 1;
}

static int prep_mv_b(struct soko *soko, int i, int j, int getch)
{
    if (soko->map[i][j] == 'X') {
        soko->end = mv_b(soko, i, j, getch);
        if (soko->end != 0)
            return soko->end;
    }
    return 0;
}

int mv_p(struct soko *soko, int i, int j, int getch)
{
    int temp;

    if (soko->map[i][j] != '#') {
        temp = prep_mv_b(soko, i, j, getch);
        if (temp != 0)
            return temp;
        soko->map[i][j] = 'P';
        soko->map[soko->i][soko->j] = soko->map_o[soko->i][soko->j];
        soko->i = i;
        soko->j = j;
    }
}

static int prep_mv_p(struct soko *soko, int i, int j, int getch)
{
    int temp;

    if (getch == 65) {
        temp = mv_p(soko, i - 1, j, getch);
    }
    if (getch == 66) {
        temp = mv_p(soko, i + 1, j, getch);
    }
    if (getch == 67) {
        temp = mv_p(soko, i, j + 1, getch);
    }
    if (getch == 68) {
        temp = mv_p(soko, i, j - 1, getch);
    }
    return temp;
}

int mv_tab(struct soko *soko, int getch)
{
    int i = soko->i;
    int j = soko->j;
    int temp = prep_mv_p(soko, i, j, getch);

    if (getch == 410) {
        if (COLS < soko->col || LINES < soko->lines)
            soko->c_s_size = 0;
        else
            soko->c_s_size = 1;
    }
    if (temp == 42)
        return temp;
}
