/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-leo.batilliot
** File description:
** my_strcmp
*/

#include "corewar.h"

// name :   my_strcmp
// args :   str_1, str_2
// use :    compar two string
int my_strcmp(const char *str1, const char *str2)
{
    if (!str1 || !str2 || my_strlen(str1) != my_strlen(str2))
        return 84;
    for (int i = 0; str1[i] != '\0'; i++)
        if (str1[i] != str2[i])
            return str1[i] - str2[i];
    return 0;
}
