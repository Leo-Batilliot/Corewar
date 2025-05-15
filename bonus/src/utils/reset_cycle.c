/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** reset_cycle
*/

#include "corewar.h"
#include "op.h"

// name :   get_state
// args :   corewar, down, reset
// use :    check if cycle must down or reset
static int get_state(corewar_t *corewar, int *down, int *reset)
{
    for (champ_t *cur = corewar->champions; cur; cur = cur->next) {
        if (cur->state == 0)
            (*reset) = 0;
        if (cur->state == 2)
            (*down) = 1;
    }
    return 0;
}

// name :   update_cycle_live
// args :   corewar, down
// use :    update cycle alive
static int update_cycle_live(corewar_t *corewar, int down)
{
    for (champ_t *cur = corewar->champions; cur; cur = cur->next)
        cur->state = 0;
    corewar->cycle_alive = CYCLE_TO_DIE + 1;
    if (down == 1)
        corewar->cycle_alive -= CYCLE_DELTA;
    return 0;
}

// name :   reset_cycle
// args :   corewar
// use :    reset cycle alive if all champ is at end
int reset_cycle(corewar_t *corewar)
{
    int down = 0;
    int reset = 1;

    if (corewar->cycle_alive <= 0) {
        get_state(corewar, &down, &reset);
        if (reset == 1 || corewar->cycle_alive <= 0)
            update_cycle_live(corewar, down);
    }
    return 0;
}
