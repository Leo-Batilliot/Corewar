/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** convert_type
*/

#include "corewar.h"
#include "op.h"

// name :   convert_int
// args :   buffer, offset
// use :    take value in memory and convert to int
int convert_int(unsigned char *buffer, int offset)
{
    return (int)((buffer[offset] << 24) |
            (buffer[offset + 1] << 16) |
            (buffer[offset + 2] << 8) |
            (buffer[offset + 3]));
}

// name :   convert_short
// args :   buffer, offset
// use :    take value in memory and convert to short
short convert_short(unsigned char *buffer, int offset)
{
    return (short)((buffer[offset] << 8) |
                (buffer[offset + 1]));
}
