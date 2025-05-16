/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** update_pc
*/

#include "corewar.h"
#include "op.h"

// name :   check_array
// args :   cur
// use :    check if is dir
int check_array(champ_t *cur)
{
    char *array[] = {"zjmp", "ldi", "sti", "fork", "lldi", "lfork"};

    for (int i = 0; i < 6; i++)
        if (!my_strcmp(array[i], op_tab[cur->rem].mnemonique))
            return 1;
    return 0;
}

// name :   update_dir
// args :   cur
// use :    update args with dur
int update_dir(champ_t *cur)
{
    if (check_array(cur))
        return 2;
    return 4;
}

// name :   update_pc
// args :   cur
// use :    update pc for move forward in memory
int update_pc(champ_t *cur)
{
    cur->pc += 1;
    if (op_tab[cur->rem].code != 0x01 && op_tab[cur->rem].code != 0x09 &&
        op_tab[cur->rem].code != 0x0c && op_tab[cur->rem].code != 0x0f) {
        cur->pc += 1;
    }
    for (int k = 0; k < op_tab[cur->rem].nbr_args; k++) {
        if (cur->type[k] == T_REG)
            cur->pc += 1;
        if (cur->type[k] == T_DIR)
            cur->pc += update_dir(cur);
        if (cur->type[k] == 3)
            cur->pc += 2;
    }
    return 0;
}
