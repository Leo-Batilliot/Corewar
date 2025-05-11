/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** convert_type
*/

#include "corewar.h"
#include "op.h"

int convert_int(unsigned char *buffer, champ_t *cur)
{
    return (int)(buffer[cur->pc + 1] << 24) |
                (buffer[cur->pc + 2] << 16) |
                (buffer[cur->pc + 3] << 8) |
                (buffer[cur->pc + 4]);
}

short convert_short(unsigned char *buffer, champ_t *cur)
{
    return (short)((buffer[cur->pc + 1] << 8) |
                (buffer[cur->pc + 2]));
}
