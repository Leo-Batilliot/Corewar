/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** in_reg
*/

#include "corewar.h"
#include "op.h"

// name :   check_reg
// args :   dst
// use :    checl if args is reg
int check_reg(int dst)
{
    if (dst - 1 >= 1 && dst - 1 <= REG_NUMBER)
        return 1;
    return 0;
}
