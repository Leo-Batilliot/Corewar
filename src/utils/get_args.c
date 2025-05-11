/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** get_args
*/

#include "corewar.h"
#include "op.h"
#include <stddef.h>
#include <stdlib.h>

static int update_offset(champ_t *cur, int *offset, int index[2])
{
    if (op_tab[cur->rem].nbr_args > 1)
        (*offset)++;
    for (int i = 0; i < index[0]; i++) {
        if (cur->type[i] == T_REG)
            (*offset) += 1;
        if (cur->type[i] == T_DIR)
            (*offset) += update_dir(cur);
        if (cur->type[i] == 3)
            (*offset) += 2;
    }
    return 0;
}

static int up_indirect(champ_t *cur, int index[2],
    unsigned char *buffer, void **args)
{
    if (cur->type[index[0]] == 3) {
        args[index[1]] = malloc(sizeof(short));
        if (!args[index[1]])
            return 84;
        *((short *)args[index[1]]) = convert_short(buffer, cur);
        index[1]++;
    }
    return 0;
}

static int up_direct(champ_t *cur, int index[2],
    unsigned char *buffer, void **args)
{
    if (cur->type[index[0]] == T_DIR) {
        args[index[1]] = malloc(sizeof(int));
        if (!args[index[1]])
            return 84;
        if (check_array(cur))
            *((short *)args[index[1]]) = convert_short(buffer, cur);
        else
            *((int *)args[index[1]]) = convert_int(buffer, cur);
        index[1]++;
    }
    return 0;
}

static int update_type_args(champ_t *cur, int index[2],
    void **args, unsigned char *buffer)
{
    int offset = 1;

    update_offset(cur, &offset, index);
    up_direct(cur, index, buffer, args);
    if (cur->type[index[0]] == T_REG) {
        args[index[1]] = malloc(sizeof(char));
        if (!args[index[1]])
            return 84;
        *((char *)args[index[1]]) = buffer[cur->pc + offset];
        index[1]++;
    }
    up_indirect(cur, index, buffer, args);
    return 0;
}

void **get_args(champ_t *cur, unsigned char *buffer)
{
    void **args = malloc(sizeof(void *) * (op_tab[cur->rem].nbr_args + 1));
    int index[2] = {0, 0};

    if (!args)
        return NULL;
    args[(int)op_tab[(unsigned char)cur->rem].nbr_args] = NULL;
    for (; index[0] < op_tab[cur->rem].nbr_args; index[0]++) {
        if (update_type_args(cur, index, args, buffer) == 84) {
            args[index[2]] = NULL;
            free_array(args);
            return NULL;
        }
    }
    return args;
}
