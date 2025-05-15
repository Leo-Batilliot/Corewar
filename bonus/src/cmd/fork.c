/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** fork
*/

#include "op.h"
#include "corewar.h"
#include <stdlib.h>

// name :   update_id
// args :   cur, new_robot, new_addr
// use :    update int for new robot
static int update_id(champ_t *cur, champ_t *new_robot, int new_addr)
{
    new_robot->id = cur->id;
    new_robot->nbr_live = cur->nbr_live;
    new_robot->pc = new_addr;
    new_robot->pos = new_addr;
    new_robot->status = 0;
    new_robot->child = 1;
    new_robot->state = 0;
    new_robot->advance_pc = 1;
    new_robot->wait_cycle = 0;
    new_robot->carry = cur->carry;
    new_robot->prog_size = cur->prog_size;
    new_robot->registre[0] = cur->registre[0];
    for (int i = 1; i < REG_NUMBER; i++)
        new_robot->registre[i] = cur->registre[i];
    return 0;
}

// name :   new_champ
// args :   prog, cur, new_addr
// use :    new champ for fork
champ_t *new_champ(corewar_t *prog, champ_t *cur, int new_addr)
{
    champ_t *new_robot = malloc(sizeof(champ_t));

    if (!new_robot)
        return NULL;
    new_robot->code = my_strdup(cur->code);
    if (!new_robot->code)
        return NULL;
    update_id(cur, new_robot, new_addr);
    my_strcpy(new_robot->prog_name, cur->prog_name);
    new_robot->rem = cur->rem;
    prog->cur_id++;
    for (int i = 0; i < MAX_ARGS_NUMBER; i++)
        new_robot->type[i] = cur->type[i];
    new_robot->next = NULL;
    return new_robot;
}

// name :   fork_cmd
// args :   prog, cur, buffer
// use :    cmd fork
int fork_cmd(corewar_t *prog, champ_t *cur, unsigned char *buffer)
{
    void **args = get_args(cur, buffer);
    champ_t *new = NULL;
    int val = 0;
    int addr = 0;

    if (!args)
        return 84;
    val = get_value(cur->type[0], args[0], cur, buffer);
    addr = (cur->pc + val % IDX_MOD) % MEM_SIZE;
    new = new_champ(prog, cur, addr);
    add_to_end(prog, new);
    return free_array(args);
}
