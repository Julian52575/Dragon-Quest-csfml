/*
** EPITECH PROJECT, 2023
** project_name
** File description:
** my_str_append_until
*/
#include <stdio.h>
#include <stdlib.h>
int my_strlen(char *str);

//append the characters found until END in the BUFFER passed as a parameter and returns how much the STR had to advance
int my_str_append_until(char *str, char end, char *buffer, int b_start)
{
    if (!buffer) buffer = malloc(sizeof(char *) * my_strlen(str));
    if (!b_start) b_start = 0;
    int i = 0;
    for (; str[0] && (str[0] != end); str++, i++) {
        buffer[b_start++] = str[0];
    }
    buffer[b_start] = str[0];
    buffer[b_start] = '\0';
    return i + 1;
}
