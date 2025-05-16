/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** live
*/

#include "corewar.h"
#include "op.h"
#include <stddef.h>

// name :   live
// args :   prog, cur, buffer
// use :    command live
int live(corewar_t *prog, champ_t *cur, unsigned char *buffer)
{
    void **args = get_args(cur, buffer);
    champ_t *champ = NULL;

    if (!args)
        return 84;
    champ = find_node(prog, *((int *)args[0]), 1);
    if (!champ)
        return free_array(args);
    else {
        champ->nbr_live++;
        prog->last_alive = champ->id;
    }
    return free_array(args);
}
