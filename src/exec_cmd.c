/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** exec_cmd
*/

#include "op.h"
#include "corewar.h"
#include <stddef.h>

const cmd_t cmd[] = {
    {"live", live},
    {"st", store},
    {"ld", load},
    {"add", add},
    {"and", and_cmd},
    {"or", or_cmd},
    {"xor", xor_cmd},
    {"zjmp", zjump},
    {"ldi", ldi},
    {"sti", sti},
    {"lld", lld},
    {"lldi", lldi},
    {"aff", aff},
    {NULL, NULL}
};

static int exec_func(char *cur_cmd, corewar_t *prog,
    champ_t *cur, unsigned char *buffer)
{
    for (int i = 0; cmd[i].name; i++) {
        if (!my_strcmp(cur_cmd, cmd[i].name))
            return cmd[i].func(prog, cur, buffer);
    }
    return 0;
}

int exec_cmd(champ_t *cur, corewar_t *prog, unsigned char *buffer)
{
    if (cur->wait_cycle == 0 && cur->status == 1) {
        cur->advance_pc = 1;
        exec_func(op_tab[cur->rem].mnemonique, prog, cur, buffer);
        if (cur->advance_pc == 1) {
            update_pc(cur);
        }
        cur->status = 0;
    }
    return 0;
}
