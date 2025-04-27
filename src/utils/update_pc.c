/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** update_pc
*/

#include "corewar.h"
#include "op.h"

static int check_array(champ_t *cur)
{
    char *array[] = {"zjump", "ldi", "sti", "fork", "lldi", "lfork"};

    for (int i = 0; i < 6; i++)
        if (!my_strcmp(array[i], op_tab[cur->rem].mnemonique))
            return 1;
    return 0;
}

static int update_dir(champ_t *cur)
{
    if (check_array(cur))
        return 2;
    else
        return 4;
}

int update_pc(champ_t *cur)
{
    cur->pc += 1;
    if (op_tab[cur->rem].nbr_args > 1)
        cur->pc += 1;
    for (int k = 0; k < op_tab[cur->rem].nbr_args; k++) {
        if (cur->type[k] == T_REG)
            cur->pc += 1;
        if (cur->type[k] == T_IND)
            cur->pc += 2;
        if (cur->type[k] == T_DIR)
            cur->pc += update_dir(cur);
    }
    return 0;
}
