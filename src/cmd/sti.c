/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** sti
*/

#include "corewar.h"
#include "op.h"

void write_bytes(unsigned char *buffer, int addr, int val, int size)
{
    for (int i = 0; i < size; i++) {
        buffer[(addr + i)] = (val >> (8 * (size - 1 - i))) & 0xFF;
    }
}

int sti(corewar_t *prog, champ_t *cur, unsigned char *buffer)
{
    void **args = get_args(cur, buffer);
    int dst = 0;
    int val_1 = 0;
    int val_2 = 0;
    int addr = 0;

    (void)prog;
    if (!args)
        return 84;
    dst = *((char *)args[0]);
    val_1 = get_value(cur->type[1], args[1], cur, buffer);
    val_2 = get_value(cur->type[2], args[2], cur, buffer);
    addr = (cur->pc + (val_1 + val_2) % IDX_MOD) % MEM_SIZE;
    write_bytes(buffer, addr, cur->registre[dst - 1], 4);
    return free_array(args);
}
