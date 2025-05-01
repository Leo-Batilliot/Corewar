/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** free
*/


#include "corewar.h"

int free_champion(champ_t *champ)
{
    if (!champ)
        return 0;
    if (champ->code)
        my_free(champ->code);
    my_free(champ);
    return 0;
}

static int free_champions_list(champ_t *head)
{
    champ_t *next;

    for (; head; head = next) {
        next = head->next;
        free_champion(head);
    }
    return 0;
}

int free_corewar(corewar_t *corewar)
{
    if (!corewar)
        return 0;
    if (corewar->champions)
        free_champions_list(corewar->champions);
    my_free(corewar);
    return 0;
}
