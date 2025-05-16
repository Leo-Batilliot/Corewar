/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-leo.batilliot
** File description:
** free_array
*/

#include "stdlib.h"

// name :   my_free
// args :   ptr
// use :    free pointeur
int my_free(void *ptr)
{
    if (!ptr)
        return 84;
    free(ptr);
    return 84;
}

// name :   free_array
// args :   array
// use :    free array with my free
int free_array(void **array)
{
    if (!array)
        return 84;
    for (int i = 0; array[i]; i++)
        free(array[i]);
    free(array);
    return 0;
}
