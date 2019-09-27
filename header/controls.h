#ifndef CONTROLS_H
#define CONTROLS_H
#include <SDL.h>
#include "structs.h"

void eventCheck(SDL_Window* mainWindow, bool&, bool&, bool&, Menu &menu, SDL_Point, Screen &screen);

void restartVars(bool &restart, int &carState, Road &road, Barrel &barrel, CarPiece &carHood, CarPiece (&pieces)[3], int &score, SDL_Point &lamp);

SDL_Point getMouseXY(SDL_Point mouse);

void carControl(Car &car, SDL_Point mouse, Screen screen);

bool collide(SDL_Rect first, SDL_Rect second);

#endif // CONTROLS_H
