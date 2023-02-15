/*
** EPITECH PROJECT, 2022
** Str to int
** File description:
** no more str
*/
int my_compute_power_rec(int nb, int p);
int my_strlen(char *str);

int my_str_to_int(char *str)
{
    long nb = 0;
    int len = my_strlen(str);
    int p = 0;
    for (int i = 0; i <= len; i++) {
        if (48 <= str[i] && str[i] <= 57) {
            nb += ((str[i] - 48) * my_compute_power_rec(10, len - 1 - p));
            p++;
        }
    }
    return nb;
}
