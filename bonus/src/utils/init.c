/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** init
*/

#include "corewar.h"
#include <stddef.h>
#include <stdlib.h>

// name :   available
// args :   an id, corewar main struct
// use :    return 1 if the id is available 0 if not
static int available(int id, corewar_t *corewar)
{
    if (!corewar->champions)
        return 1;
    for (champ_t *head = corewar->champions; head; head = head->next)
        if (head->id == id)
            return 0;
    return 1;
}

// name :   first_available
// args :   corewar main struct
// use :    return the first available id
static int first_available(corewar_t *corewar)
{
    for (int res = 1; res < 1000; res++) {
        if (available(res, corewar))
            return res;
    }
    return 1;
}

// name :   get_id
// args :   corewar main struct, id if -n is used
// use :    get the corresponding id (or the first available if its taken)
static int get_id(corewar_t *corewar, int flag_id)
{
    if (!corewar->champions)
        return flag_id == -1 ? 1 : flag_id;
    if (flag_id != -1) {
        if (available(flag_id, corewar))
            return flag_id;
        return first_available(corewar);
    }
    if (available(corewar->nb_robot + 1, corewar))
        return corewar->nb_robot + 1;
    return first_available(corewar);
}

// name :   init_champion
// args :   id, flags, corewar
// use :    int champion in new list
champ_t *init_champion(flags_t *flags, corewar_t *corewar)
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
    champion->child = 0;
    champion->pos = flags->address;
    champion->id = get_id(corewar, flags->id);
    corewar->cur_id++;
    for (int i = 0; i < MAX_ARGS_NUMBER; i++)
        champion->type[i] = 0;
    champion->code = NULL;
    champion->next = NULL;
    return champion;
}

static int init_cycles(corewar_t *main_struct)
{
    main_struct->index = malloc(sizeof(int) * (MEM_SIZE + 1));
    if (!main_struct->index)
        return 1;
    for (int i = 0; i < MEM_SIZE; i++)
        main_struct->index[i] = 0;
    main_struct->index[MEM_SIZE] = -1;
    main_struct->sim = malloc(sizeof(simulation_t));
    if (!main_struct->sim) {
        my_free(main_struct->index);
        return 1;
    }
    main_struct->sim->list = NULL;
    return 0;
}

// name :   init_main_struct
// args :   void
// use :    int structure value at 0 or NULL
corewar_t *init_main_struct(void)
{
    corewar_t *main_struct = malloc(sizeof(corewar_t));

    if (!main_struct)
        return NULL;
    main_struct->champions = NULL;
    main_struct->cycle_alive = 0;
    main_struct->last_alive = 0;
    main_struct->nb_robot = 0;
    main_struct->cur_id = 0;
    main_struct->dump = -1;
    if (init_cycles(main_struct)) {
        my_free(main_struct);
        return NULL;
    }
    return main_struct;
}

// name :   init_flags
// args :   array
// use :    function to init flags
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
