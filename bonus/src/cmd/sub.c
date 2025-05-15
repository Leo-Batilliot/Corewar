/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** sub
*/

#include "corewar.h"
#include "op.h"

// name :   check_reg_array
// args :   size, index[3]
// use :    check register in boucle
static int check_reg_array(int size, int index[3])
{
    for (int i = 0; i < size; i++) {
        if (!check_reg(index[i]))
            return 1;
    }
    return 0;
}

// name :   sub
// args :   prog, cur, buffer
// use :    sub command (substrac register)
int sub(corewar_t *prog, champ_t *cur, unsigned char *buffer)
{
    void **args = get_args(cur, buffer);
    int index[3] = {0, 0, 0};

    (void)prog;
    if (!args)
        return 84;
    for (int i = 0; args[i] && i < 3; i++)
        index[i] = *((char *)args[i]);
    if (!check_reg_array(3, index))
        cur->registre[index[2] - 1] =
        cur->registre[index[0] - 1] - cur->registre[index[1] - 1];
    cur->carry = (cur->registre[index[2] - 1] == 0) ? 1 : 0;
    free_array(args);
    return 0;
}
