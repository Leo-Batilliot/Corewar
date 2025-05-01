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

static int not_enough_arguments(char **args, int ac)
{
    int count = 0;
    int len = array_len((const void **) args);

    for (int i = 1; ac > 2 && i < len; i++) {
        if (!my_strcmp(args[i], "-a") || !my_strcmp(args[i], "-n")
            || !my_strcmp(args[i], "-dump")) {
            i++;
            continue;
        }
        count++;
    }
    if (count < 2) {
        mini_printf(2, "At least 2 robots are needed to run the simulation\n");
        return 84;
    }
    return 0;
}

int main(int ac, char **av)
{
    corewar_t *corewar = NULL;
    unsigned char buffer[MEM_SIZE + 1] = {0};
    int res = 0;

    if (not_enough_arguments(av, ac) == 84)
        return 84;
    corewar = parsing_main(av);
    if (!corewar)
        return 84;
    buffer[MEM_SIZE] = '\0';
    set_champions_positions(corewar, buffer);
    res = game_loop(corewar, buffer);
    free_corewar(corewar);
    return res;
}
