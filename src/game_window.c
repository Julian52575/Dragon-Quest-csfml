#include "my_dragonquest.h"

static void close_this_damn_window(struct csfml_tools *ct)
{
    while (sfRenderWindow_pollEvent(ct->window, &ct->event) == sfTrue) {
        if (ct->event.type == sfEvtClosed) {
            sfRenderWindow_close(ct->window);
        }
    }
    return;
}

void game_window(struct csfml_tools *ct)
{
    while (sfRenderWindow_isOpen(ct->window)) {
        close_this_damn_window(ct);
        sfRenderWindow_display(ct->window);
    }
    return;
}
