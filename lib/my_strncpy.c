/*
** EPITECH PROJECT, 2025
** B-CPE-200-LIL-2-1-robotfactory-leo.batilliot
** File description:
** my_strncpy
*/

int my_strncpy(const char *str, char *dst, int n)
{
    int i = 0;

    if (!str)
        return 84;
    for (; str[i] != '\0' && i < n; i++)
        dst[i] = str[i];
    dst[i] = '\0';
    return 0;
}
