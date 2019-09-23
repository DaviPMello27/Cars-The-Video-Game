#ifndef CONTROLS_H
#define CONTROLS_H
#include <SDL.h>
#include "structs.h"

void eventCheck(bool &end, bool &restart, Menu &menu, SDL_Point);

SDL_Point getMouseXY(SDL_Point mouse);

void carControl(Car &car, SDL_Point mouse);

#endif // CONTROLS_H
