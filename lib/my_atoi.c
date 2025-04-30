/*
** EPITECH PROJECT, 2024
** B-MUL-100-LIL-1-1-myradar-gabin.wilson
** File description:
** my_get_nbr
*/

#include <stdlib.h>
#include <limits.h>

int my_atoi(const char *string)
{
    long res = 0;

    if (string == NULL)
        return 0;
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] < '0' || string[i] > '9')
            return -2;
        res = res * 10 + string[i] - '0';
        if (res > INT_MAX)
            return - 2;
    }
    return res;
}
