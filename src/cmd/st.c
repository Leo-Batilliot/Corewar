/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** st
*/

#include "corewar.h"
#include <stdio.h>
#include "op.h"

static int equal_reg(void **args, champ_t *cur)
{
    int src = 0;
    int dst = 0;

    if (cur->type[1] == T_REG) {
        src = *((char *)args[0]);
        dst = *((char *)args[1]);
        cur->registre[src] = cur->registre[dst];
    }
    return 0;
}

static int add_register(champ_t *cur, void **args, unsigned char *buffer)
{
    int src = 0;
    int dst = 0;
    int pos = 0;
    int byte = 0;

    if (cur->type[1] == 3) {
        src = *((char *)args[0]);
        dst = *((short *)args[1]);
        pos = (cur->pc + (dst % IDX_MOD));
        for (int i = 0; i < 4; i++) {
            byte = (cur->registre[src] >> (8 * (3 - i))) & 0xFF;
            buffer[(pos + i) % MEM_SIZE] = byte;
        }
    }
    return 0;
}

int store(corewar_t *prog, champ_t *cur, unsigned char *buffer)
{
    void **args = get_args(cur, buffer);

    (void)prog;
    if (!args)
        return 84;
    equal_reg(args, cur);
    add_register(cur, args, buffer);
    free_array(args);
    return 0;
}
