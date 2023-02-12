/*
** EPITECH PROJECT, 2022
** game loop
** File description:
** ~ ~
*/

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <SFML/Graphics/Export.h>
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/Types.h>
#include <SFML/Graphics/Transform.h>
#include <SFML/System/Vector2.h>
#include <stddef.h>
#include <stdio.h>
#include "my_csfml.h"

//returns a sprite with a texture and a scale if both paramters != -84
sfSprite *create_sprite(char *image_path, float x_scale, float y_scale)
{
    sfSprite *sprite = sfSprite_create();
    if (image_path) {
        sfTexture *texture = sfTexture_createFromFile(image_path, NULL);
        sfSprite_setTexture(sprite, texture, sfFalse);
    }
    if (x_scale != -84 && y_scale != -84) {
        sfVector2f scale = {x_scale, y_scale};
        sfSprite_setScale(sprite, scale);
    }
    return sprite;
}
