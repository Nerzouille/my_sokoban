/*
** EPITECH PROJECT, 2023
** sokoban
** File description:
** sokoban ends
*/

#include <ncurses.h>
#include "../include/my.h"
#include "soko.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

static int map_analys_s(struct soko *soko, int i)
{
    for (int j = 0; j < soko->col; j++) {
        if (soko->map[i][j] != ' ' && soko->map[i][j] != '#'
            && soko->map[i][j] != 'P' && soko->map[i][j] != 'O'
            && soko->map[i][j] != 'X')
            return 0;
    }
}

static int map_analys(struct soko *soko)
{
    for (int i = 0; soko->map_r[i] != '\n' && i < soko->lines; i++) {
        if (map_analys_s(soko, i) == 0)
            return 0;
    }
    return 1;
}

int err_hand(int argc, char *argv[], struct soko *soko)
{
    int temp = map_opener(argv, soko, argc);
    int getch = 0;

    if (argc == 1) {
        my_printf("[sokoban] To few arguments");
        return 84;
    }
    if (temp != 0)
        return temp;
    def_map(soko);
    if (soko->col == 0 || soko->lines == 0 || map_analys(soko) == 0)
        return 84;
    find_player(soko);
    initscr();
    keypad(soko->screen, TRUE);
    curs_set(false);
    tab_print(soko, argc, argv, getch);
    return 0;
}

static int win_ver(struct soko *soko, int i)
{
    for (int j = 0; j < soko->col; j++) {
        if (soko->map[i][j] == 'O')
            return 0;
    }
}

int win(struct soko *soko, int i_cp, int j_cp)
{
    for (int i = 0; i < soko->lines; i++) {
        if (win_ver(soko, i) == 0) {
            return 0;
        }
    }
    soko->map[i_cp][j_cp] = 'P';
    soko->map[soko->i][soko->j] = ' ';
    return 1;
}

static void death_ver_search(struct soko *soko, int i, int j, int *count)
{
    if (soko->map[i][j] == 'X') {
        if ((soko->map[i + 1][j] == '#' && soko->map[i][j + 1] == '#')
        || (soko->map[i + 1][j] == '#' && soko->map[i][j - 1] == '#')
        || (soko->map[i - 1][j] == '#' && soko->map[i][j + 1] == '#')
        || (soko->map[i - 1][j] == '#' && soko->map[i][j - 1] == '#'))
            (*count)++;
    }
}

static int death_ver(struct soko *soko, int i, int j)
{
    int count = 0;

    for (int i = 0; i < soko->lines; i++) {
        for (int j = 0; j < soko->col; j++) {
            death_ver_search(soko, i, j, &count);
        }
    }
    if (count == soko->box_nbr)
        return 4;
    return 0;
}

static int death_verb(struct soko *soko, int i)
{
    for (int j = 0; j < soko->col; j++) {
        if (death_ver(soko, i, j) == 4)
            return 1;
    }
    return 0;
}

int death(struct soko *soko, int i_cp, int j_cp)
{
    for (int i = 0; i < soko->lines; i++) {
        if (death_verb(soko, i) != 1) {
            return 0;
        }
    }
    soko->map[i_cp][j_cp] = 'P';
    soko->map[soko->i][soko->j] = ' ';
    soko->end = 43;
    return 1;
}
