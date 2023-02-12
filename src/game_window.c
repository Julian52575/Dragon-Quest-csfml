#include "my_dragonquest.h"

static void player_imput(struct csfml_tools *ct, struct dragon_quest *dq)
{
    if (sfRenderWindow_hasFocus(ct->window) == sfFalse)
        return;
    while (sfRenderWindow_pollEvent(ct->window, &ct->event) == sfTrue) {
        //close the window
        if (ct->event.type == sfEvtClosed)
            return sfRenderWindow_close(ct->window);
    } 
        //player mouvement
        /*
        switch (ct->event.key.code) {
            case (sfKeyLeft) :
                sfSprite_move(dq->roto->sprite, (sfVector2f) {-1 * dq->sprite_size.x / 8, 0} );
            case (sfKeyRight) :
                sfSprite_move(dq->roto->sprite, (sfVector2f) {dq->sprite_size.x / 8, 0} );
            case (sfKeyUp) :
                sfSprite_move(dq->roto->sprite, (sfVector2f) {0, -1 * dq->sprite_size.y / 8} );
            case (sfKeyDown) :
                sfSprite_move(dq->roto->sprite, (sfVector2f) {0, dq->sprite_size.y / 8} );
            default :
                ;
        }
        */
        
    if (sfKeyboard_isKeyPressed(sfKeyDown) == sfTrue) {
        sfSprite_move(dq->roto->sprite, (sfVector2f) {0, 26 * dq->sprite_scale.y / 8} );
    }
    else if (sfKeyboard_isKeyPressed(sfKeyRight) == sfTrue) {
           sfSprite_move(dq->roto->sprite, (sfVector2f) {20 * dq->sprite_scale.x / 8, 0} );
    }
    else if (sfKeyboard_isKeyPressed(sfKeyUp) == sfTrue) {
        sfSprite_move(dq->roto->sprite, (sfVector2f) {0, -1 * ( 26 * dq->sprite_scale.y / 8) } );
    }
    else if (sfKeyboard_isKeyPressed(sfKeyLeft) == sfTrue) {
        sfSprite_move(dq->roto->sprite, (sfVector2f) {-1 * (20 * dq->sprite_scale.x / 8), 0} );
    }
}

void game_window(struct csfml_tools *ct, struct dragon_quest *dq)
{
    //clear the screen to avoid residus <- traduit 
    sfRenderWindow_clear(ct->window, sfBlack);

    while (sfRenderWindow_isOpen(ct->window)) {
        ct->time = sfClock_getElapsedTime(ct->clock);
        ct->mouvement_buffer += ct->time.microseconds / 1000000.0;

        //center view on player
        sfView_setCenter(ct->view, sfSprite_getPosition(dq->roto->sprite));
        sfRenderWindow_setView(ct->window, ct->view);

        //display all sprites
        sfRenderWindow_display(ct->window);
        sfRenderWindow_drawSprite(ct->window, dq->m[0]->visible, NULL);
        sfRenderWindow_drawSprite(ct->window, dq->roto->sprite, NULL);
        //NPC
        if (dq->m[0]->upper_layer)
            sfRenderWindow_drawSprite(ct->window, dq->m[0]->upper_layer, NULL);

        //player interaction
        if (ct->mouvement_buffer > 0.02) {
            player_imput(ct, dq);
            ct->event_buffer = 0.0;
        }
    }
    return;
}
