/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** live
*/

#include "corewar.h"
#include "op.h"

champ_t *find_node(prog_t *prog, int id_to_find)
{
    for (champ_t *tmp = prog->champions; tmp; tmp = tmp->next) {
        if (tmp->id == id_to_find)
            return tmp;
    }
    return NULL;
}

int live(prog_t *prog, champ_t *cur, unsigned char *buffer)
{
    void **args = get_args(cur, buffer);
    champ_t *find = NULL;

    if (!args)
        return 84;
    find = find_node(prog, *((int *)args[0]));
    if (!find)
        return 0;
    else {
        mini_printf(1, "The player %i(%s)is alive.\n",
            find->id, find->prog_name);
        find->nbr_live++;
        prog->last_alive = find->id;
    }
    return 0;
}
