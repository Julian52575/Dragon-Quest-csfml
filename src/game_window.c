#include "my_dragonquest.h"

static void move_character(sfSprite *sprite, mouvement_info mouvement)
{
    switch (mouvement.direction) {
        
        //up
        case (8):
            sfSprite_move(sprite, (sfVector2f) {0, -(80/8)} );
            break;

        //down
        case (2):
            sfSprite_move(sprite, (sfVector2f) {0, 80/8} );
            break;

        //left
        case (6):
            sfSprite_move(sprite, (sfVector2f) {7.5 , 0} );
            break;

        //right
        case (4):
            sfSprite_move(sprite, (sfVector2f) {-7.5, 0});
            break;
    }
    //sleep(2);
}

static void player_imput(struct csfml_tools *ct, struct dragon_quest *dq)
{
    //doesn't register imputs if window is hidden
    if (sfRenderWindow_hasFocus(ct->window) == sfFalse)
        return;

    //debug
    if (sfKeyboard_isKeyPressed(sfKeyX) == sfTrue)
        dq->current_map = 1;
    if (sfKeyboard_isKeyPressed(sfKeyEnter) == sfTrue) {
        dq->roto->mouvement.direction = 2;
        dq->roto->mouvement.step = 8;
    }

    //close the window
    while (sfRenderWindow_pollEvent(ct->window, &ct->event) == sfTrue) {
        if (ct->event.type == sfEvtClosed)
            return sfRenderWindow_close(ct->window);
    }

    //increase the mouvement info struct to moves the characters if it isn't already moving
    if (dq->roto->mouvement.step > 0)
        return;
    if (sfKeyboard_isKeyPressed(sfKeyDown) == sfTrue) {
        dq->roto->mouvement.next_direction = 2;
        dq->roto->mouvement.next_step = 8;
    }
    
    else if (sfKeyboard_isKeyPressed(sfKeyLeft) == sfTrue) {
        dq->roto->mouvement.next_direction = 4;
        dq->roto->mouvement.next_step = 8;
    }

    else if (sfKeyboard_isKeyPressed(sfKeyRight) == sfTrue) {
        dq->roto->mouvement.next_direction = 6;
        dq->roto->mouvement.next_step = 8;
    }

    else if (sfKeyboard_isKeyPressed(sfKeyUp) == sfTrue) {
        dq->roto->mouvement.next_direction = 8;
        dq->roto->mouvement.next_step = 8;
    }
}

void game_window(struct csfml_tools *ct, struct dragon_quest *dq)
{// !!!!!!!!!!!!!!!! 4 && 6 are inverted for mouvements
    sfSprite_setPosition(dq->roto->sprite, (sfVector2f) {0, 0});
    //clear the screen to avoid residus <- traduit 
    sfRenderWindow_clear(ct->window, sfBlack);

    while (sfRenderWindow_isOpen(ct->window)) {
        //gets elapsed time since last loop
        ct->time = sfClock_getElapsedTime(ct->clock);
        ct->mouvement_buffer += ct->time.microseconds / 1000000.0;
        ct->event_buffer += ct->time.microseconds/ 1000000.0;
        
        //center view on player
        sfView_setCenter(ct->view, sfSprite_getPosition(dq->roto->sprite));
        sfRenderWindow_setView(ct->window, ct->view);

        //display all sprites
        sfRenderWindow_display(ct->window);
        sfRenderWindow_drawSprite(ct->window, dq->m[ dq->current_map ]->visible, NULL);
        sfRenderWindow_drawSprite(ct->window, dq->roto->sprite, NULL);
            //-display NPC
        if (dq->m[0]->upper_layer)
            sfRenderWindow_drawSprite(ct->window, dq->m[ dq->current_map ]->upper_layer, NULL);

        //player interaction
        if (ct->event_buffer > 0.02) {
            player_imput(ct, dq);
            ct->event_buffer = 0.0;
        }

        //player and NPC mouvement after a certain time passes
        if (ct->mouvement_buffer > 0.02) {
                
            //si le joueur ne se déplace pas
            if (dq->roto->mouvement.step == 0) {
                dq->roto->mouvement.step = dq->roto->mouvement.next_step;
                dq->roto->mouvement.next_step = 0;
                dq->roto->mouvement.direction = dq->roto->mouvement.next_direction;
                dq->roto->mouvement.next_direction = 0;

            //si le joueur est en plein deplacement 
            } else if (dq->roto->mouvement.step > 0) {
                printf("-- mouvement step > 0! --\n");
                move_character(dq->roto->sprite, dq->roto->mouvement);
                dq->roto->mouvement.step -= 1;
            }
            ct->mouvement_buffer = 0.0;
        }

        printf("tile size (%.2f, %.2f)\n", dq->sprite_size.x, dq->sprite_size.y);
        printf("character position : (x, y)(%.2f, %.2f)\n", sfSprite_getPosition(dq->roto->sprite).x, sfSprite_getPosition(dq->roto->sprite).y);
        printf("position in smaller int : (%.2f, %.2f)\n", sfSprite_getPosition(dq->roto->sprite).x / dq->sprite_size.x, sfSprite_getPosition(dq->roto->sprite).y / dq->sprite_size.y);
        printf("modulo 80 (%.d, %d)\n", (int) sfSprite_getPosition(dq->roto->sprite).x % 60, (int) sfSprite_getPosition(dq->roto->sprite).y % 80);
        printf("mouvement.step && mouvement.direction (%d, %d)\n", dq->roto->mouvement.step, dq->roto->mouvement.direction);

        printf("---\n");
    }
    return;
}
