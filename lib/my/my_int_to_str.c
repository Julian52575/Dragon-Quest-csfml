/*
** EPITECH PROJECT, 2022
** my_int_to_str
** File description:
** int → str
*/
#include <stdlib.h>
#include <stdio.h>
int my_compute_power_rec(int a, int b);
int my_get_int_lenght(int nb);

static char *my_int_to_str_neg(int nb)
{
    int lenght = my_get_int_lenght(nb);
    char *str;
    str = malloc(sizeof(char) * lenght + 2);
    str[0] = '-';
    str[lenght + 1] = '\0';
    nb *= -1;
    for (int i = 0; nb > 10; i++) {
        str[lenght--] = (nb % 10) + 48;
        nb /= 10;
    }
    str[1] = nb + 48;
    return str;
}

static char *my_int_to_str_pos(int nb)
{
    int lenght = my_get_int_lenght(nb);
    char *str = malloc(sizeof(char) * lenght + 1);
    str[lenght] = '\0';
    --lenght;
    while (nb > 9) {
        str[lenght--] = (nb % 10) + 48;
        nb /= 10;
    }
    str[0] = nb + 48;
    return str;
}

char * my_int_to_str(int nb)
{
    if (nb == 0) return "0";
    if (nb < 0) return my_int_to_str_neg(nb);
    return my_int_to_str_pos(nb);
}
