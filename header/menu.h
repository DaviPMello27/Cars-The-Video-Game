#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include "structs.h"

void drawMenu(SDL_Renderer *renderer, Menu &menu, SDL_Point mousePosition, Img img, Car &car, Screen screen, int highScore);


#endif // MENU_H
