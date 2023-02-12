/*
** EPITECH PROJECT, 2022
** create
** File description:
** and render a window
*/

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdlib.h>

sfRenderWindow * create_renderwindow(unsigned int x, unsigned int y
, unsigned int bpp, char *title)
{
    //sfContextSettings settings = {99, 99, 99, 99, 99, 99, sfTrue};
    sfVideoMode video_mode = {x, y, bpp};
    sfRenderWindow *window = sfRenderWindow_create(video_mode, title, sfResize | sfClose, NULL);
    sfRenderWindow_setMouseCursorVisible(window, sfFalse);
    sfRenderWindow_setFramerateLimit(window, 60);
    sfRenderWindow_setPosition(window, (sfVector2i) {0, 0} );
    //sfRenderWindow_setIcon(window, 20, 20,
    //sfImage_getPixelsPtr(sfImage_createFromFile("assets/icon.png")));
    return window;
}
