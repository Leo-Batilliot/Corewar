/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** or
*/

#include "corewar.h"
#include "op.h"
#include <stdlib.h>

// name :   or_cmd
// args :   prog, cur, buffer
// use :    command or
int or_cmd(corewar_t *prog, champ_t *cur, unsigned char *buffer)
{
    void **args = get_args(cur, buffer);
    int dst = 0;
    int val_1 = 0;
    int val_2 = 0;

    (void)prog;
    if (!args)
        return 84;
    dst = *((char *)args[2]);
    val_1 = get_value(cur->type[0], args[0], cur, buffer);
    val_2 = get_value(cur->type[1], args[1], cur, buffer);
    cur->registre[dst - 1] = (val_1 | val_2) % MEM_SIZE;
    cur->carry = (cur->registre[dst - 1] == 0) ? 1 : 0;
    return free_array(args);
}
