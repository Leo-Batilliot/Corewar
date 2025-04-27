/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** exec_cmd
*/

#include "op.h"
#include "corewar.h"

const cmd_t cmd[] = {
    {"live", live},
    {NULL, NULL}
};

static int exec_func(char *cur_cmd, prog_t *prog,
    champ_t *cur, unsigned char *buffer)
{
    for (int i = 0; cmd[i].name; i++) {
        if (!my_strcmp(cur_cmd, cmd[i].name))
            return cmd[i].func(prog, cur, buffer);
    }
    return 0;
}

int exec_cmd(champ_t *cur, prog_t *prog, unsigned char *buffer)
{
    if (cur->wait_cycle == 0 && cur->status == 1) {
        exec_func(op_tab[cur->rem].mnemonique, prog, cur, buffer);
        update_pc(cur);
        cur->status = 0;
    }
    return 0;
}
