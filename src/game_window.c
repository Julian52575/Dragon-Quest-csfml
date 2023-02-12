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

void game_window(struct csfml_tools *ct, struct dragon_quest *dq)
{
    while (sfRenderWindow_isOpen(ct->window)) {
        //close the window using the X
        close_this_damn_window(ct);

        //center view on player
        sfView_setCenter(ct->view, sfSprite_getPosition(dq->roto->sprite));
        sfRenderWindow_setView(ct->window, ct->view);

        //display all sprites
        sfRenderWindow_display(ct->window);
        sfRenderWindow_drawSprite(ct->window, dq->m[0]->visible, NULL);
        sfRenderWindow_drawSprite(ct->window, dq->roto->sprite, NULL);

    }
    return;
}
