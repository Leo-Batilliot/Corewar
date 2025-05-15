/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** parsing
*/

#include "corewar.h"
#include <stddef.h>

// name :   reset_flags
// args :   flags
// use :    reset value for flags
static void reset_flags(flags_t *flags)
{
    flags->address = -1;
    flags->id = -1;
}

// name :   parsing_main
// args :   array
// use :    parsing main, check flags
corewar_t *parsing_main(char **array)
{
    corewar_t *corewar = init_main_struct();
    flags_t *flags = NULL;
    int len = array_len((const void **)array);

    if (!corewar)
        return NULL;
    flags = init_flags(array);
    if (!flags)
        return NULL + free_corewar(corewar);
    for (; flags->index < len; flags->index++) {
        reset_flags(flags);
        if (handle_flags(flags) == 84 || parse_champion_file(corewar, flags)) {
            my_free(flags);
            free_corewar(corewar);
            return NULL;
        }
    }
    corewar->dump = flags->dump;
    my_free(flags);
    return corewar;
}
