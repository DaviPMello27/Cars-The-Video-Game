#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include "structs.h"

void createButton(SDL_Renderer *render, SDL_Point &mouse, int x, int y, int w, int h);

void drawMenu(SDL_Renderer *render, Menu &menu, SDL_Point mouse, Img img, Car &car, int &carState, Screen screen, bool fullscreen);


#endif // MENU_H
