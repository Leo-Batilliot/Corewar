/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** linked_list
*/

#include <stdlib.h>
#include "corewar.h"
#include "op.h"

champ_t *find_node(corewar_t *prog, int id_to_find)
{
    for (champ_t *tmp = prog->champions; tmp; tmp = tmp->next) {
        if (tmp->id == id_to_find)
            return tmp;
    }
    return NULL;
}

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
