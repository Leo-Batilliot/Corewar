/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** init_champ
*/

#include "corewar.h"
#include "op.h"

int init_champ(prog_t *prog, unsigned char *buffer)
{
    int k = 0;

    for (champ_t *tmp = prog->champions; tmp; tmp = tmp->next) {
        tmp->pos = (MEM_SIZE / prog->nb_robot) * k;
        k++;
        tmp->pc = tmp->pos;
        for (unsigned int i = 0; i < tmp->prog_size; i++)
            buffer[(tmp->pos + i) % MEM_SIZE] = tmp->code[i];
    }
    return 0;
}

static int declare_pos(champ_t *new_prog, int id)
{
    new_prog->wait_cycle = 0;
    new_prog->pc = 0;
    new_prog->status = 0;
    new_prog->rem = 0;
    new_prog->nbr_live = 0;
    new_prog->pos = 0;
    new_prog->id = id;
    return 0;
}

int read_champ_info(FILE *fd, champ_t *new_prog)
{
    unsigned int padding = 0;

    if (fread(&new_prog->magic_number, sizeof(unsigned int), 1, fd) != 1)
        return 84;
    if (fread(new_prog->prog_name, sizeof(char), PROG_NAME_LENGTH, fd)
        != PROG_NAME_LENGTH)
        return 84;
    new_prog->prog_name[PROG_NAME_LENGTH] = '\0';
    if (fseek(fd, 4, SEEK_CUR) != 0)
        return 84;
    if (fread(&new_prog->prog_size, sizeof(unsigned int), 1, fd) != 1)
        return 84;
    new_prog->prog_size = swap_end_color_4(new_prog->prog_size);
    padding = 4 + COMMENT_LENGTH;
    if (fseek(fd, padding, SEEK_CUR) != 0)
        return 84;
    return 0;
}

int read_champ_code(FILE *fd, champ_t *new_prog)
{
    new_prog->code = malloc(sizeof(char) * new_prog->prog_size);
    if (fread(new_prog->code, sizeof(char), new_prog->prog_size, fd)
        != new_prog->prog_size)
        return 84;
    return 0;
}

void add_to_end(prog_t *prog, champ_t *new_prog)
{
    champ_t *cur = NULL;

    if (!prog->champions)
        prog->champions = new_prog;
    else {
        cur = prog->champions;
        for (; cur->next; cur = cur->next);
        cur->next = new_prog;
    }
    prog->nb_robot++;
}

int add_champ(FILE *fd, prog_t *prog, int id)
{
    champ_t *new_prog = malloc(sizeof(champ_t));

    if (!new_prog)
        return 84;
    if (read_champ_info(fd, new_prog) == 84)
        return 84;
    if (read_champ_code(fd, new_prog) == 84)
        return 84;
    declare_pos(new_prog, id);
    new_prog->next = NULL;
    add_to_end(prog, new_prog);
    return 0;
}
