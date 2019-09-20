#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include "structs.h"

void createButton(SDL_Renderer *render, SDL_Point &mouse, int x, int y, int w, int h);

void drawMenu(SDL_Renderer *render, Menu &menu, SDL_Point mouse, SDL_Texture *bgRoad, SDL_Texture *font, Car &car, int &carState);


#endif // MENU_H
