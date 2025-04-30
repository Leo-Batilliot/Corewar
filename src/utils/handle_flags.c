/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** handle_flags
*/

#include "corewar.h"
#include "op.h"

static int get_load(int *load_adress, char **av, int *i)
{
    if (av[(*i) + 1]) {
        (*load_adress) = my_atoi(av[(*i) + 1]) % MEM_SIZE;
        if ((*load_adress) < 0 || (*load_adress) == -2) {
            mini_printf(2, "The load adresse must be superior ");
            mini_printf(2, "at 0 or must be contain only number.\n");
            return 84;
        }
        if (!av[(*i) + 2]) {
            mini_printf(2, "Please put an other flags or robots.\n");
            mini_printf(2, "Example : ./corewar -a 100 test.cor tyron.cor\n");
            return 84;
        }
        (*i) = (*i) + 2;
    }
    return 0;
}

int flags_a(int *load_adress, char **av, int *i)
{
    if (!my_strcmp(av[(*i)], "-a")) {
        if (get_load(load_adress, av, i) == 84)
            return 84;
        if ((*load_adress) == -1) {
            mini_printf(2, "Please, for -a, you must load an adresse, ");
            mini_printf(2, "example : ./corewar -a 100 test.cor.\n");
            return 84;
        }
    }
    return 0;
}
