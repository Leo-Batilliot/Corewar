/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** convert_type
*/

#include "corewar.h"
#include "op.h"

int convert_int(unsigned char *buffer, int offset)
{
    return (int)((buffer[offset] << 24) |
            (buffer[offset + 1] << 16) |
            (buffer[offset + 2] << 8) |
            (buffer[offset + 3]));
}

short convert_short(unsigned char *buffer, int offset)
{
    return (short)((buffer[offset] << 8) |
                (buffer[offset + 1]));
}
