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

// name :   update_offset
// args :   cur, offsetn index[2]
// use :    update offset for next cmd
static int update_offset(champ_t *cur, int *offset, int index[2])
{
    if (op_tab[cur->rem].code != 0x01 && op_tab[cur->rem].code != 0x09 &&
        op_tab[cur->rem].code != 0x0c && op_tab[cur->rem].code != 0x0f) {
        (*offset)++;
    }
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

// name :   up_indirect
// args :   cur, index[2], buffer, args
// use :    update indirext value
static int up_indirect(champ_t *cur, int index[2],
    unsigned char *buffer, void **args)
{
    int offset = cur->pc + 1;

    update_offset(cur, &offset, index);
    if (cur->type[index[0]] == 3) {
        args[index[1]] = malloc(sizeof(short));
        if (!args[index[1]])
            return 84;
        *((short *)args[index[1]]) = convert_short(buffer, offset);
        index[1]++;
    }
    return 0;
}

// name :   up_direct
// args :   cur, index[2], buffer, args
// use :    update direct value
static int up_direct(champ_t *cur, int index[2],
    unsigned char *buffer, void **args)
{
    int offset = cur->pc + 1;

    update_offset(cur, &offset, index);
    if (cur->type[index[0]] == T_DIR) {
        if (check_array(cur)) {
            args[index[1]] = malloc(sizeof(short));
            *((short *)args[index[1]]) = convert_short(buffer, offset);
        } else {
            args[index[1]] = malloc(sizeof(int));
            *((int *)args[index[1]]) = convert_int(buffer, offset);
        }
        index[1]++;
    }
    return 0;
}

// name :   update_type_args
// args :   cur, index[2], args, buffer
// use :    update args
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
        *((char *)args[index[1]]) = buffer[(cur->pc + offset) % MEM_SIZE];
        index[1]++;
    }
    up_indirect(cur, index, buffer, args);
    return 0;
}

// name :   get_args
// args :   cur, buffer
// use :    common function to get args
void **get_args(champ_t *cur, unsigned char *buffer)
{
    int arg_count = op_tab[cur->rem].nbr_args;
    void **args = malloc(sizeof(void *) * (arg_count + 1));
    int index[2] = {0, 0};

    if (!args)
        return NULL;
    for (int i = 0; i <= arg_count; i++)
        args[i] = NULL;
    args[(int)op_tab[(unsigned char)cur->rem].nbr_args] = NULL;
    for (; index[0] < op_tab[cur->rem].nbr_args; index[0]++) {
        if (update_type_args(cur, index, args, buffer) == 84) {
            args[index[2]] = NULL;
            free_array(args);
            return NULL;
        }
    }
    args[arg_count] = NULL;
    return args;
}
