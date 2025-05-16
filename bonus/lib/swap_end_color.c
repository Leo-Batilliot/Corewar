/*
** EPITECH PROJECT, 2025
** Corewar
** File description:
** swap_end_color
*/

// name :   swap_end_color_4
// args :   num
// use :    swap big to int little endian
unsigned int swap_end_color_4(unsigned int num)
{
    num = ((num >> 24) & 0x000000FF) |
        ((num >> 8) & 0x0000FF00) |
        ((num << 8) & 0x00FF0000) |
        ((num << 24) & 0xFF000000);
    return num;
}
