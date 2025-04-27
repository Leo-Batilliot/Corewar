/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** get_args
*/

#include "corewar.h"
#include "op.h"

static int update_type_args(champ_t *cur, int index[2],
    void **args, unsigned char *buffer)
{
    if (cur->type[index[0]] == T_DIR) {
        args[index[1]] = malloc(sizeof(int));
        if (!args[index[1]])
            return 84;
        *((int *)args[index[1]]) = convert_int(buffer, cur);
        index[1]++;
    }
    return 0;
}

void **get_args(champ_t *cur, unsigned char *buffer)
{
    void **args = malloc(sizeof(void *) * op_tab[cur->rem].nbr_args);
    int index[2] = {0, 0};

    if (!args)
        return NULL;
    for (; index[0] < op_tab[cur->rem].nbr_args; index[0]++) {
        if (update_type_args(cur, index, args, buffer) == 84)
            return NULL;
    }
    return args;
}
