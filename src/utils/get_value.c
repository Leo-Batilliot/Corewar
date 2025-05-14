/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** get_value
*/

#include "corewar.h"
#include "op.h"
#include <stdio.h>

// name :   get_value
// args :   type, arg, cur, buffer
// use :    common function to get value at int to return
int get_value(int type, void *arg, champ_t *cur, unsigned char *buffer)
{
    int r = 0;

    if (type == T_REG) {
        r = *((char *)arg);
        return cur->registre[r - 1];
    }
    if (type == T_DIR) {
        if (check_array(cur))
            return *((short *)arg);
        return *((int *)arg);
    }
    if (type == 3) {
        r = *((short *)arg);
        r = (cur->pc + r % IDX_MOD) % MEM_SIZE;
        return read_mem(buffer, r, 4);
    }
    return 0;
}
