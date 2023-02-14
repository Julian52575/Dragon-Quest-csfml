#include "my_csfml.h"

sfRectangleShape *create_background_rectangle(void)
{
    sfRectangleShape *rect = sfRectangleShape_create();
    sfRectangleShape_setSize(rect, (sfVector2f) {1980, 1080} );
    sfRectangleShape_setFillColor(rect, sfBlack);
    return rect;
}
