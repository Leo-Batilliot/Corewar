/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** in_reg
*/

#include "corewar.h"
#include "op.h"

int check_reg(int dst)
{
    if (dst >= 1 && dst <= REG_NUMBER)
        return 1;
    return 0;
}
