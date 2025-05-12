/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** get_value
*/

#include "corewar.h"
#include "op.h"

int get_value(int type, void *arg, champ_t *cur, unsigned char *buffer)
{
    int r = 0;

    if (type == T_REG) {
        r = *((char *)arg);
        return cur->registre[r];
    }
    if (type == T_DIR)
        return *((int *)arg);
    if (type == 2) {
        r = *((short *)arg);
        r = (cur->pc + r % IDX_MOD);
        return read_mem(buffer, r, 4);
    }
    return 0;
}
