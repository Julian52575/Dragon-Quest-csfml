#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>

//Open a file and returns the whole buffer or NULL if the file cannot be openned
char *my_openfile(char *file_path)
{
    struct stat sb;
    char *buffer = NULL;
    int fd = 0;

    fd = open(file_path, O_RDONLY);
    if (fd == -1)
        return NULL;
    if (stat(file_path, &sb) == -1)
        return NULL;
    if (sb.st_mode == 16893)
        return NULL;
    buffer = malloc(sizeof(char) * (sb.st_size + 1));
    buffer[sb.st_size ] = '\0';
    if (read(fd, buffer, sb.st_size) == -1)
        return NULL;

    return (buffer);
}
