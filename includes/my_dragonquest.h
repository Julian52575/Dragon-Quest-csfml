#include "my_csfml.h"
#include <stdio.h>
#include <stdbool.h>

char *my_str_combine(char *a, char *b, char *delimeter);
char * my_int_to_str(int nb);
char *open_file(char *file, int *size);
int my_strlen(char *str);
int my_str_append_until(char *str, char end, char *buffer, int b_start);
int my_str_to_int(char *str);
char *my_openfile(char *file);
char **my_str_to_word_array(char *str);
int my_array_len(char **array);

typedef struct coordinates {
    int y;
    int x;
} coordinates;

typedef struct mouvement {
    unsigned direction;
    unsigned short step;
    unsigned short next_direction;
    unsigned short next_step;
} mouvement_info;

struct dragon_quest_item {
    char *name;
    int atk;
    int hp;
    bool overworld;
};

struct teleportation {
    unsigned int warp_y;
    unsigned int warp_x;
    unsigned int new_map;
};

struct dragon_quest_event {
    bool visible;
    bool colision;
    int id;//
    sfVector2f position;
    char *message;//
    struct teleportation tp;
    int item_id; //
    bool rm;
    struct dragon_quest_event *next;
};

struct dragon_quest_map {
    sfSprite *visible;
    sfSprite *upper_layer;
    char **colision;
    struct dragon_quest_event *e;
    sfVector2f map_size;
};

struct dragon_quest_player {
    sfSprite *sprite;
    double y;
    double x;
    short HP;
    short ATK;
    short MP;
    coordinates facing_block;
    mouvement_info mouvement;
};

struct dragon_quest {
    struct dragon_quest_map **m;
    struct dragon_quest_item **i;
    struct dragon_quest_player *roto;
    sfVector2f sprite_size;//size of tiles
    sfVector2f sprite_scale;//multiplication of tiles
    sfVector2f player_scale;//multiplication of characters
    short roto_sup;
    unsigned int current_map;
};

void game_window(struct csfml_tools *ct, 
struct dragon_quest *dq);
void init_dragonquest(struct dragon_quest **dq);
struct dragon_quest_map *add_new_dqmap(char *file);
