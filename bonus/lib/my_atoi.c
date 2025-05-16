/*
** EPITECH PROJECT, 2024
** B-MUL-100-LIL-1-1-myradar-gabin.wilson
** File description:
** my_get_nbr
*/

// name :   return_error
// args :   error, return value
// use :    retur an error
static int return_error(int *error, int return_value)
{
    *error = 1;
    return return_value;
}

// name :   my_atoi
// args :   string, error
// use :    my atoi, transform string in int
int my_atoi(const char *string, int *error)
{
    long res = 0;
    int sign = 1;
    int i = 0;

    if (!string)
        return return_error(error, 2);
    if (string[0] == '-') {
        sign = -1;
        i++;
    }
    for (; string[i] != '\0'; i++) {
        if (string[i] < '0' || string[i] > '9')
            return return_error(error, 2);
        res = res * 10 + string[i] - '0';
        if (res > 2147483647)
            return return_error(error, 2);
    }
    return res * sign;
}
