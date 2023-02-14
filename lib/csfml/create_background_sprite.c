#include "my_csfml.h"

sfSprite *create_background_sprite(void)
{
    sfSprite *b = sfSprite_create();
    sfTexture *t = sfTexture_createFromFile("assets\black.png", NULL);

    sfSprite_setTexture(b, t, sfFalse);
    sfSprite_setScale(b, (sfVector2f) {1920, 1080} );
    sfSprite_setOrigin(b, (sfVector2f) {1920 /2, 1080 /2} );
    return b;
}
