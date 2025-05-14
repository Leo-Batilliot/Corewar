/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** read_pc
*/

#include "corewar.h"
#include "op.h"

// name :   parse_args_types
// args :   i, cur, buffer
// use :    add type to cur.type
int parse_args_types(int *i, champ_t *cur, unsigned char *buffer)
{
    unsigned char arg_types = buffer[cur->pc + 1];
    unsigned char type = '\0';

    for (int k = 0; k < op_tab[(*i)].nbr_args; k++) {
        type = (arg_types >> (6 - (2 * k))) & 0x03;
        cur->type[k] = type;
    }
    return 0;
}

// name :   cmd_one_arg
// args :   i, cur
// use :    check cmd with one arg
static int cmd_one_arg(int *i, champ_t *cur)
{
    char *array[] = {"live", "zjump", "fork", "lfork"};

    for (int k = 0; k < 4; k++) {
        if (!my_strcmp(op_tab[(*i)].mnemonique, array[k])) {
            cur->type[0] = 2;
            return 1;
        }
    }
    return 0;
}

// name :   get_type
// args :   i, cur, buffer
// use :    common function to get type
int get_type(int *i, champ_t *cur, unsigned char *buffer)
{
    if (op_tab[(*i)].code == buffer[cur->pc]) {
        cur->wait_cycle = op_tab[(*i)].nbr_cycles;
        cur->status = 1;
        cur->rem = (*i);
        if (cmd_one_arg(i, cur))
            return 1;
        parse_args_types(i, cur, buffer);
        return 1;
    }
    return 0;
}
