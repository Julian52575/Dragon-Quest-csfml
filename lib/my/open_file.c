/*
** EPITECH PROJECT, 2022
** Open file
** File description:
** open a file and returns its content as a char * or NULL in case of error
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
int my_ascii_test(char c);

//max ~30  / 31 avec \n
char *open_file(char *file_path, int *size)
{
    struct stat sb;
    int fd = 0;
    char *txt = NULL;
    if ( (fd = open(file_path, O_RDONLY)) == -1)
        return NULL;
    if ( stat(file_path, &sb) == -1 )
        return NULL;
    txt = malloc(sizeof(char) * (sb.st_size + 1) );
    read(fd, txt, sb.st_size);
    txt[sb.st_size + 1] = '\0';
    if (*size)
        *size = (long int) sb.st_size;
    return txt;
}
