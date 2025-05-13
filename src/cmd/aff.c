/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** aff
*/

#include "corewar.h"
#include "op.h"
#include <unistd.h>

int aff(corewar_t *prog, champ_t *cur, unsigned char *buffer)
{
    void **args = get_args(cur, buffer);
    int r = 0;
    char c = '\0';

    (void)prog;
    if (!args)
        return 84;
    r = *((char *)args[0]);
    c = cur->registre[r - 1] % 256;
    write(1, &c, 1);
    return free_array(args);
}
