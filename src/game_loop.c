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
        return 1;
    }
    if (champion->nbr_live >= NBR_LIVE && corewar->cycle_alive > 0) {
        champion->state = 2;
        champion->nbr_live = 0;
        return 1;
    }
    if (corewar->cycle_alive <= 0 && champion->nbr_live > 0) {
        champion->state = 1;
        champion->nbr_live = 0;
        return 1;
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
int execute_each_champ(champ_t **champion, unsigned char *buffer,
    corewar_t *corewar)
{
    champ_t *next = NULL;

    if (update_cycle(*champion)) {
        next = (*champion)->next;
        if (watch_health(*champion, corewar)) {
            *champion = next;
            return 0;
        }
        return 1;
    }
    if ((*champion)->status == 0) {
        if (loop_type((*champion), buffer))
            return 1;
    }
    exec_cmd(*champion, corewar, buffer);
    next = (*champion)->next;
    watch_health(*champion, corewar);
    *champion = next;
    return 0;
}

// name :   check_end
// args :   corewar, game_run
// use :    check the condition if is the enf of the game
static int end(corewar_t *corewar)
{
    int count = 0;
    champ_t *winner = NULL;

    for (champ_t *head = corewar->champions; head; head = head->next) {
        if (head->child == 0)
            count++;
    }
    if (!(corewar->champions) || count == 0) {
        mini_printf(1, "No player has won. It's a draw.\n");
        return 1;
    }
    if (count > 1)
        return 0;
    winner = find_parent(corewar);
    mini_printf(1, "The player %i", winner->id);
    mini_printf(1, "(%s)has won.\n", winner->prog_name);
    return 1;
}

// name :   loop_champ
// args :   corewar, buffer, game_run
// use :    loop each champ
int loop_champ(corewar_t *corewar, unsigned char *buffer)
{
    for (champ_t *champ = corewar->champions; champ;) {
        if (champ->state != 0) {
            champ = champ->next;
            continue;
        }
        if (execute_each_champ(&champ, buffer, corewar) == 1)
            champ = champ->next;
    }
    return 0;
}

// name :   print_hex_byte
// args :   byte
// use :    print byte in hex
void print_hex_byte(unsigned char byte)
{
    char hex_digits[] = "0123456789ABCDEF";
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
    for (int i = 0; i < MEM_SIZE; i++) {
        if (i > 0 && i % 32 == 0)
            mini_printf(1, "\n");
        print_hex_byte(buffer[i]);
        if (i % 32 != 31)
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
    corewar->cycle_alive = CYCLE_TO_DIE;
    for (int cycle = 0; cycle >= 0; cycle++) {
        loop_champ(corewar, buffer);
        if (end(corewar))
            return 0;
        reset_cycle(corewar);
        corewar->cycle_alive--;
        if (cycle == corewar->dump)
            dump(buffer);
    }
    return 0;
}
