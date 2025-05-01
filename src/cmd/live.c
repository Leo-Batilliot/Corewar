/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** live
*/

#include "corewar.h"
#include "op.h"
#include <stddef.h>

champ_t *find_node(corewar_t *prog, int id_to_find)
{
    for (champ_t *tmp = prog->champions; tmp; tmp = tmp->next) {
        if (tmp->id == id_to_find)
            return tmp;
    }
    return NULL;
}

int live(corewar_t *prog, champ_t *cur, unsigned char *buffer)
{
    void **args = get_args(cur, buffer);
    champ_t *champ = NULL;

    if (!args)
        return 84;
    champ = find_node(prog, *((int *)args[0]));
    if (!champ)
        return free_array(args);
    else {
        mini_printf(1, "The player %i(%s)is alive.\n",
            champ->id, champ->prog_name);
        champ->nbr_live++;
        prog->last_alive = champ->id;
    }
    return free_array(args);
}
