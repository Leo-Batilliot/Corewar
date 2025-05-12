/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** init
*/

#include "corewar.h"
#include <stddef.h>
#include <stdlib.h>

champ_t *init_champion(int id, flags_t *flags)
{
    champ_t *champion = malloc(sizeof(champ_t));

    if (!champion)
        return NULL;
    champion->wait_cycle = 0;
    champion->pc = 0;
    champion->status = 0;
    champion->rem = 0;
    champion->carry = 0;
    champion->nbr_live = 0;
    champion->pos = flags->address;
    champion->id = flags->id != -1 ? flags->id : id;
    champion->code = NULL;
    champion->next = NULL;
    return champion;
}

corewar_t *init_main_struct(void)
{
    corewar_t *main_struct = malloc(sizeof(corewar_t));

    if (!main_struct)
        return NULL;
    main_struct->champions = NULL;
    main_struct->cycle_alive = 0;
    main_struct->last_alive = 0;
    main_struct->nb_robot = 0;
    main_struct->dump = -1;
    return main_struct;
}

flags_t *init_flags(char **array)
{
    flags_t *flags = malloc(sizeof(flags_t));

    if (!flags)
        return NULL;
    flags->address = -1;
    flags->dump = -1;
    flags->id = -1;
    flags->array = array;
    flags->index = 1;
    return flags;
}
