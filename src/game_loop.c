/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** game_loop
*/

#include "corewar.h"
#include "op.h"
#include <stdbool.h>
#include <unistd.h>

static int update_cycle(champ_t *champion)
{
    if (champion->wait_cycle > 0 && champion->status == 1) {
        champion->wait_cycle--;
        return 1;
    }
    return 0;
}

int watch_health(champ_t *champion, bool *game_run, corewar_t *corewar)
{
    if (corewar->cycle_alive == 0 && champion->nbr_live < NBR_LIVE) {
        (*game_run) = false;
    }
    if (champion->nbr_live >= NBR_LIVE && corewar->cycle_alive > 0) {
        corewar->cycle_alive -= CYCLE_DELTA;
        champion->nbr_live = 0;
    }
    return 0;
}

static int loop_type(champ_t *champion, unsigned char *buffer)
{
    for (int i = 0; op_tab[i].mnemonique; i++) {
        if (get_type(&i, champion, buffer))
            return 1;
    }
    return 0;
}

int execute_each_champ(champ_t *champion, unsigned char *buffer,
    corewar_t *corewar, bool *game_run)
{
    if (update_cycle(champion))
        return 2;
    if (champion->status == 0) {
        if (loop_type(champion, buffer))
            return 1;
    }
    exec_cmd(champion, corewar, buffer);
    watch_health(champion, game_run, corewar);
    return 0;
}

int loop_champ(corewar_t *corewar, unsigned char *buffer, bool *game_run)
{
    int res = 0;

    for (champ_t *champ = corewar->champions; champ; champ = champ->next) {
        res = execute_each_champ(champ, buffer, corewar, game_run);
        if (res == 2)
            continue;
        if (res == 1)
            break;
    }
    return 0;
}

void print_hex_byte(unsigned char byte)
{
    char hex_digits[] = "0123456789abcdef";
    char out[2] = {0, 0};

    out[0] = hex_digits[(byte >> 4) & 0x0F];
    out[1] = hex_digits[byte & 0x0F];
    write(1, out, 2);
}

static int dump(unsigned char *buffer)
{
    mini_printf(1, "Memory dump:\n");
    for (int i = 0; i < MEM_SIZE; i++) {
        if (i % 64 == 0)
            mini_printf(1, "\n");
        print_hex_byte(buffer[i]);
        mini_printf(1, " ");
    }
    mini_printf(1, "\n");
    return 0;
}

int game_loop(corewar_t *corewar, unsigned char *buffer)
{
    bool game_run = true;

    corewar->cycle_alive = CYCLE_TO_DIE;
    for (int cycle = 0; game_run; cycle++) {
        loop_champ(corewar, buffer, &game_run);
        corewar->cycle_alive--;
        if (cycle == corewar->dump)
            dump(buffer);
    }
    mini_printf(1, "The player %i () has won.\n", corewar->last_alive);
    return 0;
}
