/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** lldi
*/

#include "corewar.h"
#include "op.h"

// name :   lldi
// args :   prog, cur, buffer
// use :    lldi commands
int lldi(corewar_t *prog, champ_t *cur, unsigned char *buffer)
{
    void **args = get_args(cur, buffer);
    int rem = 0;

    (void)prog;
    if (!args)
        return 84;
    rem = read_mem(buffer,
        cur->pc + (get_value(cur->type[0], args[0], cur, buffer)
        + get_value(cur->type[1], args[1], cur, buffer)) % MEM_SIZE,
        REG_SIZE);
    cur->registre[*((char *)args[2]) - 1] = rem;
    cur->carry = (cur->registre[*((char *)args[2]) - 1] == 0) ? 1 : 0;
    return free_array(args);
}
