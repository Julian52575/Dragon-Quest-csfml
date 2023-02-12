#include "my_dragonquest.h"
//str combine danger !!!
void add_map_data(struct dragon_quest **dq)
{
    //creer event** à la main, l'ajouter petit a petit;
    for (int i = 0; i < 1; i++) {
        (*dq)->m[i] = malloc(sizeof(struct dragon_quest_map));
        (*dq)->m[i]->visible = create_sprite( my_str_combine("assets/maps/map", ".png", my_int_to_str(i) ), 3, 4 );
        (*dq)->m[i]->colision = create_sprite( my_str_combine("assets/maps/map", "_c.png", my_int_to_str(i) ), 3, 4 );

        //(*dq)->e = event[i]; ajouter event**
        printf("->loaded map%d\n", i);
    }
}

void init_dragonquest(struct dragon_quest **dq)
{
    //reference
    (*dq)->sprite_scale.y = 4;
    (*dq)->sprite_scale.x = 3;//1.4;
    (*dq)->sprite_size.y = 19 * (*dq)->sprite_scale.y;
    (*dq)->sprite_size.x = 19 * (*dq)->sprite_scale.x;
    (*dq)->player_scale.x = 3 * 1.25;
    (*dq)->player_scale.y = 4 * 1.25;
    (*dq)->roto_sup = 7 * (*dq)->player_scale.y;

    //initialize plyer
    (*dq)->roto = malloc(sizeof(struct dragon_quest_player));
    (*dq)->roto->sprite = create_sprite("assets/characters.png", (*dq)->player_scale.x, (*dq)->player_scale.y );
    sfSprite_setTextureRect( (*dq)->roto->sprite, create_texture_rect(20, 26, 2, 5)); 
    sfSprite_setPosition((*dq)->roto->sprite,
            (sfVector2f) {5 * (*dq)->sprite_size.x, 6 * (*dq)->sprite_size.y - (*dq)->roto_sup } );

    //initialize maps
    (*dq)->m = malloc(sizeof(struct dragon_quest_map*) * 42);
    add_map_data(dq);


    return;
}
