/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** init_champ
*/

#include "corewar.h"
#include "op.h"
#include <sys/stat.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

// name :   set_champions_positions
// args :   prog, buffer
// use :    set champions position in memory
int set_champions_positions(corewar_t *prog, unsigned char *buffer)
{
    int k = 0;

    for (champ_t *tmp = prog->champions; tmp; tmp = tmp->next) {
        if (tmp->pos == -1)
            tmp->pos = (MEM_SIZE / prog->nb_robot) * k;
        k++;
        tmp->pc = tmp->pos;
        for (unsigned int i = 0; i < tmp->prog_size; i++)
            buffer[(tmp->pos + i) % MEM_SIZE] = tmp->code[i];
        tmp->registre[0] = tmp->id;
        for (int i = 1; i < REG_NUMBER; i++)
            tmp->registre[i] = 0;
        tmp->state = 0;
    }
    return 0;
}

// name :   add_to_end
// args :   prog, champion
// use :    add robot at end of the list
void add_to_end(corewar_t *prog, champ_t *champion)
{
    champ_t *tmp = NULL;

    prog->nb_robot++;
    if (!prog->champions) {
        prog->champions = champion;
        return;
    }
    for (tmp = prog->champions; tmp->next; tmp = tmp->next);
    tmp->next = champion;
}

// name :   invalid_champ_info
// args :   FD, champion
// use :    check if valid info
static int invalid_champ_info(FILE *fd, champ_t *champion)
{
    unsigned int padding = 0;

    if (fread(&champion->magic_number, sizeof(unsigned int), 1, fd) != 1)
        return 84;
    if (fread(champion->prog_name, sizeof(char), PROG_NAME_LENGTH, fd)
        != PROG_NAME_LENGTH)
        return 84;
    champion->prog_name[PROG_NAME_LENGTH] = '\0';
    if (fseek(fd, 4, SEEK_CUR) != 0)
        return 84;
    if (fread(&champion->prog_size, sizeof(unsigned int), 1, fd) != 1)
        return 84;
    champion->prog_size = swap_end_color_4(champion->prog_size);
    padding = 4 + COMMENT_LENGTH;
    if (fseek(fd, padding, SEEK_CUR) != 0)
        return 84;
    return 0;
}

// name :   invalid_champ_code
// args :   fd, champion
// use :    check if valid champ code
static int invalid_champ_code(FILE *fd, champ_t *champion)
{
    champion->code = malloc(sizeof(char) * champion->prog_size);
    if (!champion->code)
        return 84;
    if (fread(champion->code, sizeof(char), champion->prog_size, fd)
        != champion->prog_size)
        return 84;
    return 0;
}

// name :   handle_file_content
// args :   fd, prog, flags
// use :    check file content for add robot
static int handle_file_content(FILE *fd, corewar_t *prog, flags_t *flags)
{
    static int id = 1;
    champ_t *champion = init_champion(id, flags, prog);

    if (!champion)
        return 84;
    if (invalid_champ_info(fd, champion) || invalid_champ_code(fd, champion))
        return free_champion(champion) + 84;
    if (champion->magic_number != COREWAR_EXEC_MAGIC) {
        mini_printf(2, "incorrect magic number in %s.\n",
            flags->array[flags->index]);
        return free_champion(champion) + 84;
    }
    add_to_end(prog, champion);
    id = champion->id + 1;
    return 0;
}

// name :   print_file_error
// args :   filepath
// use :    function to print error
static void print_file_error(const char *filepath)
{
    struct stat file;

    if (stat(filepath, &file) != 0) {
        mini_printf(2, "[%s]: ", filepath);
        if (errno == ENOENT)
            mini_printf(2, "Not found.");
        if (errno == EACCES)
            mini_printf(2, "Permission denied");
        mini_printf(2, "\n");
    }
}

// name :   try_to_open
// args :   str
// use :    try open a FILE
static FILE *try_to_open(char *str)
{
    FILE *fd;

    if (my_strlen(str) < 4
        || my_strcmp(str + (my_strlen(str) - 4), ".cor")) {
        mini_printf(2, "[%s]: file name must end with \".cor\"\n", str);
        return NULL;
    }
    fd = fopen(str, "rb");
    if (!fd) {
        print_file_error(str);
        return NULL;
    }
    return fd;
}

// name :   parse_champion_file
// args :   corewar, flags
// use :    function to parse new file
int parse_champion_file(corewar_t *corewar, flags_t *flags)
{
    FILE *fd = NULL;
    int res = 0;

    if (!flags->array[flags->index]) {
        if ((flags->id != -1) || (flags->address != -1))
            return mini_printf(2, "missing argument after flags\n") + 84;
        else
            return 0;
    }
    fd = try_to_open(flags->array[flags->index]);
    if (!fd)
        return 84;
    res = handle_file_content(fd, corewar, flags);
    fclose(fd);
    return res;
}
