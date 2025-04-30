/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** main
*/
#include "op.h"
#include "corewar.h"
#include <stdio.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

int error_file(const char *filepath)
{
    struct stat file;

    if (stat(filepath, &file) == 0) {
        if (errno == ENOENT)
            mini_printf(2, "Error : [%s] not found.\n", filepath);
        if (errno == EACCES) {
            mini_printf(2, "You dont have permission ");
            mini_printf(2, "for reading [%s].\n", filepath);
        }
    }
    return 84;
}

static int open_args(FILE **fd, char **av, int i)
{
    (*fd) = fopen(av[i], "rb");
    if (av[i]) {
        if (my_strlen(av[i]) < 4
            || my_strcmp(av[i] + my_strlen(av[i] + 4), ".cor")) {
            mini_printf(2, "%s must be finish with[.cor], ", av[i]);
            mini_printf(2, "example : %s.cor\n", av[i]);
            return 84;
        }
    }
    if (!(*fd))
        return error_file(av[1]);
    return 0;
}

prog_t *parsing_args(char **av)
{
    FILE *fd = NULL;
    prog_t *prog = malloc(sizeof(prog_t));
    int load_adress = -1;

    if (!prog)
        return NULL;
    prog->nb_robot = 0;
    prog->champions = NULL;
    for (int i = 1; av[i]; i++) {
        load_adress = -1;
        if (flags_a(&load_adress, av, &i) == 84)
            return NULL;
        if (open_args(&fd, av, i))
            return NULL;
        if (add_champ(fd, prog, load_adress) == 84)
            return NULL;
        fclose(fd);
    }
    return prog;
}

static int check_ac(int ac)
{
    if (ac < 3) {
        mini_printf(2, "For load the simulation, ");
        mini_printf(2, "you must ensure at minimun two robots.\n");
        mini_printf(2, "Example : ./corewar test_1.cor test_2.cor\n");
        return 84;
    }
    return 0;
}

static int check_nb_robots(prog_t *prog)
{
    if (prog->nb_robot < 2) {
        mini_printf(2, "Please ensure at minimums two robots.\n");
        mini_printf(2, "Example : ./corewar test_1.cor test_2.cor\n");
        return 84;
    }
    return 0;
}

int main(int ac, char **av)
{
    prog_t *prog = parsing_args(av);
    unsigned char buffer[MEM_SIZE + 1] = {0};

    if (!prog)
        return 84;
    if (check_ac(ac) == 84)
        return 84;
    buffer[MEM_SIZE] = '\0';
    init_champ(prog, buffer);
    if (check_nb_robots(prog) == 84)
        return 84;
    return game_loop(prog, buffer);
}
