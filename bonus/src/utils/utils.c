/*
** EPITECH PROJECT, 2025
** bonus
** File description:
** utils
*/

#include <stddef.h>
#include "corewar.h"
#include <stdlib.h>

void get_strings(cycle_data_t *cycle, unsigned char *buffer)
{
    const char *hex_digits = "0123456789ABCDEF";

    for (int i = 0; i < MEM_SIZE; i++) {
        cycle->buffer[i][0] = hex_digits[(buffer[i] >> 4) & 0x0F];
        cycle->buffer[i][1] = hex_digits[buffer[i] & 0x0F];
        cycle->buffer[i][2] = '\0';
    }
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

void add_cycle_to_end(corewar_t *corewar, cycle_data_t *cycle)
{
    cycle_data_t *head = corewar->sim->list;

    if (!head) {
        corewar->sim->list = cycle;
        return;
    }
    for (; head && head->next; head = head->next);
    head->next = cycle;
    cycle->prev = head;
}

champ_info_t *champ_infos(champ_t *champ)
{
    champ_info_t *infos = malloc(sizeof(champ_info_t));

    if (!infos)
        return NULL;
    infos->name = my_strdup(champ->prog_name);
    infos->color_id = champ->color_index;
    infos->id = champ->id;
    infos->wait = champ->wait_cycle;
    return infos;
}

// name :   new_cycle
// args :   buffer, buffer indexes
// use :    copy the buffer and index into the cycle list    
int new_cycle(unsigned char *buffer, corewar_t *corewar)
{
    cycle_data_t *cycle = corewar->current;
    int count = 0;

    for (champ_t *head = corewar->champions; head; head = head->next) {
        if (head->child != 1) {
            cycle->champs[count] = champ_infos(head);
            count++;
        }
    }
    cycle->champs[count] = NULL;
    get_strings(cycle, buffer);
    cycle->buffer_id = my_intndup(corewar->index, MEM_SIZE);
    if (!cycle->buffer_id) {
        return my_free(cycle);
    }
    add_cycle_to_end(corewar, cycle);
    return 0;
}
