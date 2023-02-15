#include "my_dragonquest.h"
#include <stdio.h>
#include <stdlib.h>

static void add_event_data(struct dragon_quest_event **e, char *line)
{
    //debug
    printf("_%s_\n", line);

    struct dragon_quest_event *element = malloc(sizeof(struct dragon_quest_event) );
    sfVector2f position = {0, 0};
    char *buffer = malloc(sizeof(char) * my_strlen(line) );

    switch (line[0]) {

        case ('C'):
            printf("  chest\n");
            element->visible = true;
            element->colision = true;
            element->id = 0;
            element->position = position;
            element->message = false;
            element->tp;

            //get the item id
            ++line;
            my_str_append_until(line, '\n', buffer, 0);
            element->item_id = my_str_to_int( buffer );

            element->rm = true;
            break;

        case ('T'):
            printf("  tp\n");
            element->visible;
            element->colision;
            element->id;
            element->position = position;
            element->message;
            element->tp;
            element->item_id;
            element->rm;

    }
    printf("    element->item_id %d\n", element->item_id);
    element->next = *e;
    *e = element;
}

static void add_map_data(struct dragon_quest **dq)
{
    for (int i = 0; i < 2; i++) {
        //initialize map, colision and upper layer
        (*dq)->m[i] = malloc(sizeof(struct dragon_quest_map));
        (*dq)->m[i]->visible = create_sprite( my_str_combine("assets/maps/map", ".png", my_int_to_str(i) ), 3, 4 );
        (*dq)->m[i]->colision = my_str_to_word_array( my_openfile( my_str_combine("assets/maps/map", "_c.txt", my_int_to_str(i) )  ) );
        (*dq)->m[i]->upper_layer = create_sprite( my_str_combine("assets/maps/map", "_u.png", my_int_to_str(i) ), 3, 4 );

        //sfSprite_setPosition((*dq)->m[i]->visible, (sfVector2f) { +(*dq)->sprite_size.x * 2, -(*dq)->sprite_size.y } );
        
        //debug
        //for(int debug = 0; (*dq)->m[i]->colision[debug][0]; debug++ ) {
        //    printf("-> _%s_\n", (*dq)->m[i]->colision[debug] );
        //}

        //initialize map size from txt
        FILE *stream;
        char *line = NULL;
        size_t len = 0;
        ssize_t nread;

        stream = fopen( my_str_combine("assets/maps/map", "_e.txt", my_int_to_str(i) ), "r" );
        if (!stream)
            continue;

        //get x size
        getline(&line, &len, stream);
        (*dq)->m[i]->map_size.x = my_str_to_int(line) / 10;
        
        //get y size
        getline(&line, &len, stream);
        (*dq)->m[i]->map_size.y = my_str_to_int(line) / 10;

        //initialize events from txt
        (*dq)->m[i]->e = NULL;
        while ( (nread = getline(&line, &len, stream)) != -1) {
            add_event_data( &(*dq)->m[i]->e , line); 
        }

        //debug
        printf("->loaded map%d\n", i);
    }
    //exit(0);
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
