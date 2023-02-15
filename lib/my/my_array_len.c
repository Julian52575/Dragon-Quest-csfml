/*
** EPITECH PROJECT, 2022
** my array len
** File description:
** strlen with one more star
*/

int my_array_len(char **array)
{
    int y = 0;
    for (;array[y][0] != '\0'; y++);
    return y;
}
