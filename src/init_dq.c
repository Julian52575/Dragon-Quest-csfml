#include "my_dragonquest.h"
#include <fcntl.h>
#include <unistd.h>

void add_map_data(struct dragon_quest **dq)
{
    //-creer event** à la main, l'ajouter petit a petit;
    for (int i = 0; i < 2; i++) {
        //initialize map, colision and upper layer
        (*dq)->m[i] = malloc(sizeof(struct dragon_quest_map));
        (*dq)->m[i]->visible = create_sprite( my_str_combine("assets/maps/map", ".png", my_int_to_str(i) ), 3, 4 );
        (*dq)->m[i]->colision = sfTexture_createFromFile( my_str_combine("assets/maps/map", "_c.png", my_int_to_str(i) ), NULL );
        (*dq)->m[i]->upper_layer = create_sprite( my_str_combine("assets/maps/map", "_u.png", my_int_to_str(i) ), 3, 4 );
        
        //initialize events from txt
        (*dq)->m[i]->e = NULL;

        printf("->loaded map%d\n", i);
    }
}

void init_dragonquest(struct dragon_quest **dq)
{
    //reference
    (*dq)->sprite_scale.y = 4;
    (*dq)->sprite_scale.x = 3;//1.4;
    (*dq)->sprite_size.y = 20 * (*dq)->sprite_scale.y;
    (*dq)->sprite_size.x = 20 * (*dq)->sprite_scale.x;
    (*dq)->player_scale.x = 3 * 1.20;
    (*dq)->player_scale.y = 4 * 1.25;
    (*dq)->roto_sup = 7 * (*dq)->player_scale.y;

    //initialize plyer
    (*dq)->roto = malloc(sizeof(struct dragon_quest_player));
    (*dq)->roto->sprite = create_sprite("assets/characters.png", (*dq)->player_scale.x, (*dq)->player_scale.y );
    sfSprite_setTextureRect( (*dq)->roto->sprite, create_texture_rect(20, 26, 0, 0)); 
    sfSprite_setPosition((*dq)->roto->sprite, (sfVector2f) {5 * (*dq)->sprite_size.x, 6 * (*dq)->sprite_size.y } );
    sfSprite_setOrigin( (*dq)->roto->sprite, (sfVector2f) {0, 27 } );
    (*dq)->roto->mouvement.direction = 2;
    (*dq)->roto->mouvement.step = 0;
    (*dq)->roto->mouvement.next_direction = 2;
    (*dq)->roto->mouvement.next_step = 0;

    //initialize maps
    (*dq)->m = malloc(sizeof(struct dragon_quest_map*) * 42);
    add_map_data(dq);
    (*dq)->current_map = 0;

    return;
}
