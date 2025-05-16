/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** free
*/


#include "corewar.h"

// name :   free_champion
// args :   champ
// use :    free champ with my free
int free_champion(champ_t *champ)
{
    if (!champ)
        return 0;
    if (champ->code)
        my_free(champ->code);
    my_free(champ);
    return 0;
}

// name :   free_champions_list
// args :   head
// use :    free list champ
static int free_champions_list(champ_t *head)
{
    champ_t *next;

    for (; head; head = next) {
        next = head->next;
        free_champion(head);
    }
    return 0;
}

// name :   free_corewar
// args :   corewar
// use :    free memory with my free
int free_corewar(corewar_t *corewar)
{
    if (!corewar)
        return 0;
    if (corewar->champions)
        free_champions_list(corewar->champions);
    my_free(corewar->index);
    if (corewar->sprite)
        sfSprite_destroy(corewar->sprite);
    if (corewar->textures) {
        for (int i = 0; corewar->textures[i]; i++)
            sfTexture_destroy(corewar->textures[i]);
        my_free(corewar->textures);
    }
    if (corewar->clock)
        sfClock_destroy(corewar->clock);
    my_free(corewar);
    return 0;
}
