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
int execute_each_champ(champ_t **champion, unsigned char *buffer,
    corewar_t *corewar)
{
    champ_t *next = NULL;

    if (update_cycle(*champion))
        return 0;
    if ((*champion)->status == 0) {
        if (loop_type((*champion), buffer))
            return 0;
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
    int id = 0;

    if (!(corewar->champions)) {
        mini_printf(1, "No player has won. It's a draw.\n");
        return 1;
    }
    id = corewar->champions->id;
    for (champ_t *head = corewar->champions; head; head = head->next)
        if (head->id != id)
            return 0;
    mini_printf(1, "The player %i", corewar->champions->registre[0]);
    mini_printf(1, "(%s)has won.\n", corewar->champions->prog_name);
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
        execute_each_champ(&champ, buffer, corewar);
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

unsigned char *my_unsigned_strndup(unsigned char *buffer, int len)
{
    unsigned char *str = malloc(sizeof(char) *(len + 1));

    if (!str)
        return NULL;
    for (int i = 0; i < len; i++)
        str[i] = buffer[i];
    str[len] = '\0';
    return str;
}

int *my_intndup(int *tab, int len)
{
    int *dup = malloc(sizeof(int) * (len + 1));

    if (!dup)
        return NULL;
    for (int i = 0; i < len; i++)
        dup[i] = tab[i];
    dup[len] = -1;
    return dup;
}



// name :   new_cycle
// args :   buffer, buffer indexes
// use :    copy the buffer and index into the cycle list    
int new_cycle(unsigned char *buffer, corewar_t *corewar)
{
    cycle_data_t *cycle = malloc(sizeof(cycle_data_t));
    cycle_data_t *head = corewar->sim->list;

    if (!cycle)
        return 0;
    cycle->next = NULL;
    cycle->buffer = my_unsigned_strndup(buffer, MEM_SIZE);
    if (!cycle->buffer)
        return my_free(cycle);
    cycle->buffer_id = my_intndup(corewar->index, MEM_SIZE);
    if (!cycle->buffer_id) {
        my_free(cycle->buffer);
        return my_free(cycle);
    }
    for (; head && head->next; head = head->next);
    if (!corewar->sim->list)
        corewar->sim->list = cycle;
    else
        head->next = cycle;
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
        new_cycle(buffer, corewar);
        if (end(corewar))
            return 0;
        reset_cycle(corewar);
        corewar->cycle_alive--;
        if (cycle == corewar->dump)
            dump(buffer);
    }
    return 0;
}
