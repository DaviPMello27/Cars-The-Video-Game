#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include "structs.h"

void createButton(SDL_Renderer *renderer, SDL_Point &mousePosition, int x, int y, int w, int h);

void drawMenu(SDL_Renderer *renderer, Menu &menu, SDL_Point mousePosition, Img img, Car &car, int &carState, Screen screen, int highScore);


#endif // MENU_H
