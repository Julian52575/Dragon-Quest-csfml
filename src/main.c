#include "my_dragonquest.h"

int main(int ac, char **av)
{
    struct csfml_tools *ct = malloc(sizeof(struct csfml_tools) + 1);
    create_ct(&ct, "My Dragon Quest");
    struct dragon_

    game_window(ct);

    printf("free\n");
    free(ct);
    return 0;
}
