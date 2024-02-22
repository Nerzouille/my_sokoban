/*
** EPITECH PROJECT, 2023
** sokoban
** File description:
** sokoban definition of the map
*/

#include <ncurses.h>
#include "../include/my.h"
#include "soko.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

char *assign_str(char *buffer, char *temp, int pi, struct soko *soko)
{
    for (int i = 0; buffer[i] != '\0'; i++) {
        temp[i] = buffer[i + pi];
    }
}

int map_opener(char **argv,
    struct soko *soko, int argc)
{
    int var = open(argv[1], O_RDONLY);
    int len_v;
    struct stat len_s;

    if (help(argc, argv) == 1)
        return 1;
    stat(argv[1], &len_s);
    len_v = len_s.st_size;
    soko->map_r = malloc(sizeof(char *) * len_v);
    read(var, soko->map_r, len_v);
    soko->map_r[len_v] = '\0';
    close(var);
    return 0;
}

static int search_col(char *buffer, struct soko *soko)
{
    int i = 0;
    int count = 0;
    int max = 0;
    int last;

    for (i; buffer[i] != '\0'; i++) {
        if (buffer[i] == '\n') {
            count = 0;
            i++;
        } else {
            count++;
        }
        last = count;
        if (count > max)
            max = count;
    }
    if (last == 0)
        soko->lines--;
    return max;
}

static int search_lines(char *buffer)
{
    int i = 0;
    int count = 0;
    char *cache = malloc(sizeof(char *) * my_strlen(buffer));

    my_strcat(cache, buffer);
    for (i; buffer[i] != '\0'; i++) {
        if (buffer[i] == '\n') {
            count++;
        }
    }
    count++;
    return count;
}

static void def_map_cpy_ed(struct soko *soko, int i, int j)
{
    if (soko->map_o[i][j] == 'X')
            soko->box_nbr++;
    if (soko->map_o[i][j] == 'P' || soko->map_o[i][j] == 'X')
        soko->map_o[i][j] = ' ';
}

void def_map_cpy(struct soko *soko)
{
    for (int i = 0; soko->map_r[i] != '\n' && i < soko->lines; i++) {
        for (int j = 0; j < soko->col; j++) {
            def_map_cpy_ed(soko, i, j);
        }
    }
}

int def_map(struct soko *soko)
{
    soko->lines = search_lines(soko->map_r);
    soko->col = search_col(soko->map_r, soko);
    soko->map = malloc(sizeof(char *) * soko->lines);
    for (int i = 0; i < soko->col; i++)
        soko->map[i] = malloc(sizeof(char) * soko->col);
    for (int i = 0; soko->map_r[i] != '\n' && i < soko->lines; i++) {
        for (int j = 0; j < soko->col; j++) {
            soko->map[i][j] = soko->map_r[i * soko->col + i + j];
        }
    }
    soko->map_o = malloc(sizeof(char *) * soko->lines);
    for (int i = 0; i < soko->col; i++)
        soko->map_o[i] = malloc(sizeof(char) * soko->col);
    for (int i = 0; soko->map_r[i] != '\n' && i < soko->lines; i++) {
        for (int j = 0; j < soko->col; j++) {
            soko->map_o[i][j] = soko->map_r[i * soko->col + i + j];
        }
    }
    def_map_cpy(soko);
}

int tab_print(struct soko *soko, int argc, char *argv[], int getch)
{
    char *txt = "Please resize the window";
    int strlen = my_strlen(txt);

    if (soko->c_s_size == 1) {
        for (int i = 0; i < soko->lines; i++) {
            mvprintw((LINES - soko->lines) / 2 + i, (COLS - soko->col) / 2,
                "%s\n", soko->map[i]);
        }
    } else {
        mvprintw((LINES) / 2, (COLS - strlen) / 2, "%s", txt);
    }
    if (getch == ' ') {
        soko->end = 0;
        def_map(soko);
        err_hand(argc, argv, soko);
    }
    return 0;
}
