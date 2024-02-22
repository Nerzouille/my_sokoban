/*
** EPITECH PROJECT, 2023
** sokoban
** File description:
** sokoban.h
*/

#include <ncurses.h>
#include "../include/my.h"
#include <stdlib.h>

#ifndef STRUC_H_
    #define STRUC_H_

struct soko {
    int c_s_size;
    int size_m;
    char *map_r;
    char **map;
    char **map_o;
    int iso;
    char temp;
    char current_place;
    char current_place_b;
    int i;
    int j;
    int lines;
    int col;
    int end;
    int box_nbr;
    WINDOW *screen;
};

int temp_def(struct soko *soko);
int help(int argc, char *argv[]);
int death(struct soko *soko, int i_cp, int j_cp);
int win(struct soko *soko, int i_cp, int j_cp);
int mv_b(struct soko *soko, int i, int j, int getch);
int def_map(struct soko *soko);
int err_hand(int argc, char *argv[], struct soko *soko);
int zero_case(struct soko *soko, int i, int j);
int mv_tab(struct soko *soko, int getch);
int tab_print(struct soko *soko, int argc, char *argv[], int getch);
int find_player(struct soko *soko);
int map_opener(char **argv,
    struct soko *soko, int argc);
#endif /* !STRUC_H_ */
