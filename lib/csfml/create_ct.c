/*
** EPITECH PROJECT, 2022
** main
** File description:
** main for my radar
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

void create_ct(struct csfml_tools **ct, char *name)
{
    (*ct)->window = create_renderwindow(1980, 1080, 32, name);
    (*ct)->clock = sfClock_create();
    (*ct)->time = sfClock_getElapsedTime( (*ct)->clock);
    (*ct)->time_buffer = 0;
    (*ct)->event_buffer = 0;
    (*ct)->mouvement_buffer = 0;
    return;
}
