/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** ld
*/

#include "corewar.h"
#include "op.h"
#include <stdio.h>

// name :   get_addr
// args :   args, buffer, cur
// use :    get new adresse for read mem
static int get_addr(void **args, unsigned char *buffer, champ_t *cur)
{
    int value = 0;
    int addr = 0;

    addr = *((short *)args[0]);
    addr = (cur->pc + addr) % MEM_SIZE;
    value = read_mem(buffer, addr, 4);
    return value;
}

// name :   lld
// args :   prog, cur, buffer
// use :    lld command
int lld(corewar_t *prog, champ_t *cur, unsigned char *buffer)
{
    void **args = get_args(cur, buffer);
    int dst = 0;
    int value = 0;

    (void)prog;
    if (!args)
        return 84;
    dst = *((char *)args[1]);
    if (cur->type[0] == T_DIR && check_reg(dst))
        value = *((int *)args[0]);
    else if (cur->type[0] == 3 && check_reg(dst))
        value = get_addr(args, buffer, cur);
    cur->registre[dst - 1] = value;
    cur->carry = (cur->registre[dst - 1] == 0) ? 1 : 0;
    return free_array(args);
}
