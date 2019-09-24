#ifndef CONTROLS_H
#define CONTROLS_H
#include <SDL.h>
#include "structs.h"

void eventCheck(bool&, bool&, bool&, Menu &menu, SDL_Point, Screen screen);

SDL_Point getMouseXY(SDL_Point mouse);

void carControl(Car &car, SDL_Point mouse, Screen screen);

#endif // CONTROLS_H
