/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** zjump
*/

#include "corewar.h"
#include "op.h"

// name :   zjump
// args :   prog, cur, buffer
// use :    jump at an address in memory
int zjump(corewar_t *prog, champ_t *cur, unsigned char *buffer)
{
    void **args = get_args(cur, buffer);
    int index = 0;

    (void)prog;
    if (!args)
        return 84;
    index = get_value(cur->type[0], args[0], cur, buffer);
    if (cur->carry == 1) {
        cur->pc = (cur->pc + index % IDX_MOD) % MEM_SIZE;
        cur->advance_pc = 0;
        cur->status = 0;
    } else
        cur->advance_pc = 1;
    return free_array(args);
}
