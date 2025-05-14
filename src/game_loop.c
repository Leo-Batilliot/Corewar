/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** game_loop
*/

#include "corewar.h"
#include "op.h"
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// name :   update_cycle
// args :   champion
// use :    check update cycle
static int update_cycle(champ_t *champion)
{
    if (champion->wait_cycle > 0 && champion->status == 1) {
        champion->wait_cycle--;
        return 1;
    }
    return 0;
}

// name :   watch_health
// args :   champion, corewar
// use :    check if champ must be dead, or no
int watch_health(champ_t *champion, corewar_t *corewar)
{
    if (corewar->cycle_alive <= 0 && champion->nbr_live <= 0) {
        remove_champion(&corewar->champions, champion->id, corewar);
        return 0;
    }
    if (champion->nbr_live >= NBR_LIVE && corewar->cycle_alive > 0) {
        champion->state = 2;
        champion->nbr_live = 0;
        return 0;
    }
    if (corewar->cycle_alive <= 0 && champion->nbr_live > 0) {
        champion->state = 1;
        champion->nbr_live = 0;
        return 0;
    }
    return 0;
}

// name :   loop_type
// args :   champion, buffer
// use :    loop to get type
static int loop_type(champ_t *champion, unsigned char *buffer)
{
    for (int i = 0; op_tab[i].mnemonique; i++) {
        if (get_type(&i, champion, buffer))
            return 1;
    }
    return 0;
}

// name :   execute_each_champ
// args :   champion, buffer, corewar
// use :    execute each champ
int execute_each_champ(champ_t *champion, unsigned char *buffer,
    corewar_t *corewar)
{
    if (update_cycle(champion))
        return 2;
    if (champion->status == 0) {
        if (loop_type(champion, buffer))
            return 1;
    }
    exec_cmd(champion, corewar, buffer);
    watch_health(champion, corewar);
    return 0;
}

// name :   check_end
// args :   corewar, game_run
// use :    check the condition if is the enf of the game
static int check_end(corewar_t *corewar, bool *game_run)
{
    champ_t *winner = NULL;
    int count = 0;

    for (champ_t *cur = corewar->champions; cur; cur = cur->next) {
        if (cur->child == 0)
            count++;
    }
    if (count <= 1) {
        winner = find_node(corewar, corewar->last_alive, 0);
        if (winner) {
            mini_printf(1, "The player %i", winner->registre[0]);
            mini_printf(1, "(%s)has won.\n", winner->prog_name);
        }
        *game_run = false;
    }
    return 0;
}

// name :   update_next
// args :   save_next, champ
// use :    update next for list
static int update_next(champ_t **save_next, champ_t *champ)
{
    (*save_next) = champ->next;
    if (champ->state != 0) {
        champ = (*save_next);
        return 1;
    }
    return 0;
}

// name :   loop_champ
// args :   corewar, buffer, game_run
// use :    loop each champ
int loop_champ(corewar_t *corewar, unsigned char *buffer, bool *game_run)
{
    int res = 0;
    champ_t *champ = corewar->champions;
    champ_t *save_next = NULL;

    while (champ != NULL && *game_run == true) {
        if (update_next(&save_next, champ))
            continue;
        res = execute_each_champ(champ, buffer, corewar);
        if (res == 2) {
            champ = save_next;
            continue;
        }
        if (res == 1)
            break;
        check_end(corewar, game_run);
        champ = save_next;
    }
    return 0;
}

// name :   print_hex_byte
// args :   byte
// use :    print byte in hex
void print_hex_byte(unsigned char byte)
{
    char hex_digits[] = "0123456789abcdef";
    char out[2] = {0, 0};

    out[0] = hex_digits[(byte >> 4) & 0x0F];
    out[1] = hex_digits[byte & 0x0F];
    write(1, out, 2);
}

// name :   dump
// args :   buffer
// use :    print dump memory
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

// name :   game_loop
// args :   corewar, buffer
// use :    game loop, start of the vm
int game_loop(corewar_t *corewar, unsigned char *buffer)
{
    bool game_run = true;

    corewar->cycle_alive = CYCLE_TO_DIE;
    for (int cycle = 0; game_run; cycle++) {
        loop_champ(corewar, buffer, &game_run);
        reset_cycle(corewar);
        corewar->cycle_alive--;
        if (cycle == corewar->dump)
            dump(buffer);
    }
    return 0;
}
