/*
** EPITECH PROJECT, 2022
** get int lenght
** File description:
** how long is this int
*/
int my_compute_power_rec(int a, int b);

int my_get_int_lenght(int nb)
{
    if (nb < 0) return my_get_int_lenght(nb * -1);
    int i = 0;
    for (; nb / my_compute_power_rec(10, i) > 0; i++);
    return i;
}
