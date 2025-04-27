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

prog_t *parsing_args(char **av)
{
    FILE *fd = NULL;
    prog_t *prog = malloc(sizeof(prog_t));

    if (!prog)
        return NULL;
    prog->nb_robot = 0;
    prog->champions = NULL;
    for (int i = 1; av[i]; i++) {
        fd = fopen(av[i], "rb");
        if (!fd)
            return NULL;
        if (add_champ(fd, prog, i) == 84)
            return NULL;
        fclose(fd);
    }
    return prog;
}

int main(int ac, char **av)
{
    prog_t *prog = parsing_args(av);
    unsigned char buffer[MEM_SIZE + 1] = {0};

    (void)ac;
    if (!prog)
        return 84;
    buffer[MEM_SIZE] = '\0';
    init_champ(prog, buffer);
    return game_loop(prog, buffer);
}
