/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** handle_flags
*/

#include "corewar.h"
#include "op.h"

// name :   flag
// args :   flags, value, flag
// use :    function common to check all flags
static int flag(flags_t *flags, int *value, char *flag)
{
    int atoi_error = 0;

    if (*value != - 1)
        return mini_printf(2, "%s used twice\n", flag) + 84;
    if (!flags->array[flags->index + 1])
        return mini_printf(2, "%s require a numerical argument\n", flag) + 84;
    *value = my_atoi(flags->array[flags->index + 1], &atoi_error);
    if (!my_strcmp("-a", flag))
        *value = *value % MEM_SIZE;
    if (atoi_error)
        return mini_printf(2, "%s require a numerical argument\n", flag) + 84;
    if (*value < 0)
        return mini_printf(2, "%s argument has to be positive\n", flag) + 84;
    return 0;
}

// name :   handle_flags
// args :   flags
// use :    function handle flags
int handle_flags(flags_t *flags)
{
    int res = 0;

    for (; flags->array[flags->index]; flags->index += 2) {
        if (res != 0)
            break;
        if (!my_strcmp(flags->array[flags->index], "-dump")) {
            res = flag(flags, &flags->dump, "-dump");
            continue;
        }
        if (!my_strcmp(flags->array[flags->index], "-n")) {
            res = flag(flags, &flags->id, "-n");
            continue;
        }
        if (!my_strcmp(flags->array[flags->index], "-a")) {
            res = flag(flags, &flags->address, "-a");
            continue;
        }
        return res;
    }
    return res;
}
