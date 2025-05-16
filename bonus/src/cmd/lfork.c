/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** lfork
*/

#include "op.h"
#include "corewar.h"
#include <stdlib.h>

// name :   lfork_cmd
// args :   prog, cur, buffer
// use :    cmd lfork
int lfork_cmd(corewar_t *prog, champ_t *cur, unsigned char *buffer)
{
    void **args = get_args(cur, buffer);
    champ_t *new = NULL;
    int val = 0;
    int addr = 0;

    if (!args)
        return 84;
    val = get_value(cur->type[0], args[0], cur, buffer);
    addr = (cur->pc + val) % MEM_SIZE;
    new = new_champ(prog, cur, addr);
    add_to_end(prog, new);
    return free_array(args);
}
