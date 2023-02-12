#include "my_csfml.h"
#include <stdio.h>
#include <stdbool.h>

char *my_str_combine(char *a, char *b, char *delimeter);
char * my_int_to_str(int nb);

typedef struct coordinates {
    int y;
    int x;
} coordinates;

struct dragon_quest_item {
    char *name;
    int atk;
    int hp;
    bool overworld;
};

struct dragon_quest_event {
    bool visible;
    int id;//
    coordinates position;
    bool dialogue;
    char *message;//
    bool warp;
    int warp_y;
    int warp_x;
    bool overworld;
    int what_map;//
    bool item;
    int what_item; //
    struct dragon_quest_event *next;
};

struct dragon_quest_map {
    sfSprite *visible;
    sfSprite *upper_layer;
    sfSprite *colision;
    struct dragon_quest_event *e;
};

struct dragon_quest_player {
    sfSprite *sprite;
    double y;
    double x;
    short HP;
    short ATK;
    short MP;
    coordinates facing_block;
};

struct dragon_quest {
    struct dragon_quest_map **m;
    struct dragon_quest_item **i;
    struct dragon_quest_player *roto;
    sfVector2f sprite_size;
    sfVector2f sprite_scale;
    sfVector2f player_scale;
    short roto_sup;
};

void game_window(struct csfml_tools *ct, 
struct dragon_quest *dq);
void init_dragonquest(struct dragon_quest **dq);
struct dragon_quest_map *add_new_dqmap(char *file);
