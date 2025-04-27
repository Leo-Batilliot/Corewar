/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** game_loop
*/

#include "corewar.h"
#include "op.h"
#include <stdbool.h>

static int update_cycle(champ_t *cur)
{
    if (cur->wait_cycle > 0 && cur->status == 1) {
        cur->wait_cycle--;
        return 1;
    }
    return 0;
}

int watch_health(champ_t *cur, bool *game_run, prog_t *prog)
{
    if (prog->cycle_alive == 0 && cur->nbr_live < NBR_LIVE) {
        (*game_run) = false;
    }
    if (cur->nbr_live >= NBR_LIVE && prog->cycle_alive > 0) {
        prog->cycle_alive -= CYCLE_DELTA;
        cur->nbr_live = 0;
    }
    return 0;
}

static int loop_type(champ_t *cur, unsigned char *buffer)
{
    for (int i = 0; op_tab[i].mnemonique != NULL; i++) {
        if (get_type(&i, cur, buffer))
            return 1;
    }
    return 0;
}

int execute_each_champ(champ_t *cur, unsigned char *buffer,
    prog_t *prog, bool *game_run)
{
    if (update_cycle(cur))
        return 2;
    if (cur->status == 0) {
        if (loop_type(cur, buffer))
            return 1;
    }
    exec_cmd(cur, prog, buffer);
    watch_health(cur, game_run, prog);
    return 0;
}

int loop_champ(prog_t *prog, unsigned char *buffer, bool *game_run)
{
    int res = 0;

    for (champ_t *cur = prog->champions; cur; cur = cur->next) {
        res = execute_each_champ(cur, buffer, prog, game_run);
        if (res == 2)
            continue;
        if (res == 1)
            break;
    }
    return 0;
}

int game_loop(prog_t *prog, unsigned char *buffer)
{
    bool game_run = true;

    prog->cycle_alive = CYCLE_TO_DIE;
    while (game_run) {
        loop_champ(prog, buffer, &game_run);
        prog->cycle_alive--;
    }
    mini_printf(1, "The player %i () has won.\n", prog->last_alive);
    return 0;
}
