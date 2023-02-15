#include "my_dragonquest.h"

static void animate_character(sfSprite *sprite)
{
    sfIntRect rect = sfSprite_getTextureRect(sprite);
    if (rect.left % 2 == 0)
        rect.left += 21;
    else 
        rect.left -= 21;
    sfSprite_setTextureRect(sprite, rect);
}

static void set_character_facing_direction(sfSprite *sprite, mouvement_info mouvement)
{
    //  8
    //6   4
    //  2
    sfIntRect rect = sfSprite_getTextureRect(sprite);
    switch (mouvement.direction) {
        case (8) :
            rect.left = 147 - (21 * (rect.left % 2) );
            break;

        case (2) :
            rect.left = 21 - (21 * (rect.left % 2) );
            break;
        
        case (4) :
            rect.left = 105 - (21 * (rect.left % 2) );
            break;

        case (6) :
            rect.left = 63 - (21 * (rect.left % 2) );
            break;

    }
    sfSprite_setTextureRect(sprite, rect);
}

static void move_character(struct dragon_quest *dq, sfSprite *sprite, mouvement_info mouvement)
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

    sfVector2f pos = sfSprite_getPosition(dq->roto->sprite);
    int x = pos.x /= dq->sprite_size.x;
    int y = pos.y /= dq->sprite_size.y;

    if (sfKeyboard_isKeyPressed(sfKeyDown) == sfTrue && dq->m[ dq->current_map ]->colision[y + 1][x] != '#' ) {
        dq->roto->mouvement.next_direction = 2;
        dq->roto->mouvement.next_step = 8;
    }
    
    else if (sfKeyboard_isKeyPressed(sfKeyLeft) == sfTrue && dq->m[ dq->current_map ]->colision[y][x - 1] != '#'  ) {
        dq->roto->mouvement.next_direction = 4;
        dq->roto->mouvement.next_step = 8;
    }

    else if (sfKeyboard_isKeyPressed(sfKeyRight) == sfTrue && dq->m[ dq->current_map ]->colision[y][x + 1] != '#' ) {
        dq->roto->mouvement.next_direction = 6;
        dq->roto->mouvement.next_step = 8;
    }

    else if (sfKeyboard_isKeyPressed(sfKeyUp) == sfTrue && dq->m[ dq->current_map ]->colision[y - 1][x] != '#') {
        dq->roto->mouvement.next_direction = 8;
        dq->roto->mouvement.next_step = 8;
    }
}

void game_window(struct csfml_tools *ct, struct dragon_quest *dq)
{// !!!!!!!!!!!!!!!! 4 && 6 are inverted for mouvements

    //debug
    //sfSprite_setPosition(dq->roto->sprite, (sfVector2f) {0, 0});

    //screen clearing 
    sfSprite *background = create_sprite("assets/black.png", 1920, 1080);
    sfSprite_setOrigin(background, (sfVector2f) {1, 1} );
    while (sfRenderWindow_isOpen(ct->window)) {

        //gets elapsed time since last loop
        ct->time = sfClock_getElapsedTime(ct->clock);
        ct->mouvement_buffer += ct->time.microseconds / 1000000.0;
        ct->event_buffer += ct->time.microseconds/ 1000000.0;
        ct->player_animation_buffer += ct->time.microseconds / 1000000.0;
        sfClock_restart(ct->clock);

        //center view on player
        sfView_setCenter(ct->view, sfSprite_getPosition(dq->roto->sprite));
        sfRenderWindow_setView(ct->window, ct->view);

        //display all sprites
        sfRenderWindow_display(ct->window);
        sfSprite_setPosition(background, sfSprite_getPosition(dq->roto->sprite) );
        sfRenderWindow_drawSprite(ct->window, background, NULL);
        sfRenderWindow_drawSprite(ct->window, dq->m[ dq->current_map ]->visible, NULL);
        sfRenderWindow_drawSprite(ct->window, dq->roto->sprite, NULL);
            //-display NPC
        if (dq->m[0]->upper_layer)
            sfRenderWindow_drawSprite(ct->window, dq->m[ dq->current_map ]->upper_layer, NULL);

        //player interaction
        if (ct->event_buffer > 0.2) {
            player_imput(ct, dq);
            ct->event_buffer = 0.0;
        }

        //player and NPC mouvement
        if (ct->mouvement_buffer > 0.02) {
                      
            //when the player is about to move
            if (dq->roto->mouvement.step == 8 && (dq->roto->mouvement.direction != dq->roto->mouvement.next_direction) ) {
                //dq->roto->mouvement.direction = dq->roto->mouvement.next_direction;
                set_character_facing_direction(dq->roto->sprite, dq->roto->mouvement);
                ct->player_animation_buffer = 0.0;
            }

            //when the player ended its movement
            if (dq->roto->mouvement.step == 0) {
                dq->roto->mouvement.step = dq->roto->mouvement.next_step;
                dq->roto->mouvement.next_step = 0;
                dq->roto->mouvement.direction = dq->roto->mouvement.next_direction;
                dq->roto->mouvement.next_direction = 0;
                
            //when the player is moving between tiles
            } else if (dq->roto->mouvement.step > 0) {
                move_character( dq, dq->roto->sprite, dq->roto->mouvement);
                dq->roto->mouvement.step -= 1;            
            } 
            
            ct->mouvement_buffer = 0.0;
        }

        //animate characters
        if (ct->player_animation_buffer > 0.4) {
            animate_character(dq->roto->sprite);
            ct->player_animation_buffer = 0.0;
        }

        //debug
        printf("tile size (%.2f, %.2f)\n", dq->sprite_size.x, dq->sprite_size.y);
        printf("character position : (x, y)(%.2f, %.2f)\n", sfSprite_getPosition(dq->roto->sprite).x, sfSprite_getPosition(dq->roto->sprite).y);
        printf("position in smaller int : (%.2f, %.2f)\n", sfSprite_getPosition(dq->roto->sprite).x / dq->sprite_size.x, sfSprite_getPosition(dq->roto->sprite).y / dq->sprite_size.y);
        printf("modulo 80 (%.d, %d)\n", (int) sfSprite_getPosition(dq->roto->sprite).x % 60, (int) sfSprite_getPosition(dq->roto->sprite).y % 80);
        printf("mouvement.step && mouvement.direction (%d, %d)\n", dq->roto->mouvement.step, dq->roto->mouvement.direction);
        printf("---\n");

        for (int debug = 0; dq->m[ dq->current_map ]->colision[debug][0] ; debug++) {
            printf("_%s_\n", dq->m[ dq->current_map ]->colision[debug] );
        }
    }
    sfSprite_destroy(background);
    return;
}
