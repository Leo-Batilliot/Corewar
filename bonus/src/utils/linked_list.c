/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** linked_list
*/

#include <stdlib.h>
#include "corewar.h"
#include "op.h"

// name :   find_node
// args :   prog, id_to_find, opt
// use :    finc champ with option
champ_t *find_node(corewar_t *prog, int id_to_find, int opt)
{
    for (champ_t *tmp = prog->champions; tmp; tmp = tmp->next) {
        if (opt == 1 && tmp->child == 0 && tmp->id == id_to_find)
            return tmp;
        if (opt == 0 && tmp->id == id_to_find)
            return tmp;
    }
    return NULL;
}

// name :   update_removed
// args :   prev, head, tmp, corewar
// use :    update champ removed to next
static void update_removed(champ_t **prev, champ_t **head,
    champ_t **tmp, corewar_t *corewar)
{
    if (!(*prev))
        *head = (*tmp)->next;
    else
        (*prev)->next = (*tmp)->next;
    if ((*tmp)->code)
        free((*tmp)->code);
    free((*tmp));
    corewar->nb_robot--;
    return;
}

// name :   remove_champion
// args :   head, id, corewar
// use :    remove champion if dead
void remove_champion(champ_t **head, int id, corewar_t *corewar)
{
    champ_t *tmp = *head;
    champ_t *prev = NULL;

    while (tmp) {
        if (tmp->id == id) {
            update_removed(&prev, head, &tmp, corewar);
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }
}
