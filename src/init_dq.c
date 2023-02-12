#include "my_dragonquest.h"
//str combine danger !!!
void add_map_data(struct dragon_quest **dq)
{
    //creer event** à la main, l'ajouter petit a petit;
    for (int i = 0; i < 1; i++) {
        (*dq)->m[i] = malloc(sizeof(struct dragon_quest_map));
        (*dq)->m[i]->visible = create_sprite( my_str_combine("assets/maps/map", ".png", my_int_to_str(i) ), 3, 3 );
        (*dq)->m[i]->colision = create_sprite( my_str_combine("assets/maps/map", "_c.png", my_int_to_str(i) ), 3, 3 );

        //(*dq)->e = event[i]; ajouter event**
        printf("->loaded map%d\n", i);
    }
}

void init_dragonquest(struct dragon_quest **dq)
{
    //reference
    (*dq)->sprite_scale.y = 3;
    (*dq)->sprite_scale.x = 3;
    (*dq)->sprite_size.y = 19 * (*dq)->sprite_scale.y;
    (*dq)->sprite_size.x = 19 * (*dq)->sprite_scale.x;

    //initialize plyer
    (*dq)->roto = malloc(sizeof(struct dragon_quest_player));
    (*dq)->roto->sprite = create_sprite("assets/characters.png", 4, 4);
    sfSprite_setTextureRect( (*dq)->roto->sprite, create_texture_rect(20, 26, 2, 5));
    sfSprite_setPosition((*dq)->roto->sprite,
            (sfVector2f) {5 * (*dq)->sprite_size.x, 6 * (*dq)->sprite_size.y} );
    //sfSprite_setOrigin((*dq)->roto->sprite, (sfVector2f) {20 * (*dq)->sprite_scale.x, 26 * (*dq)->sprite_scale.y } );

    //initialize maps
    (*dq)->m = malloc(sizeof(struct dragon_quest_map*) * 42);
    add_map_data(dq);


    return;
}
