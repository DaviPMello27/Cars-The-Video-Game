#ifndef CONTROLS_H
#define CONTROLS_H
#include <SDL.h>
#include "structs.h"

void eventCheck(SDL_Window* window, bool &endFlag, bool &restartFlag, int &highscore, int carState, Menu &menu, SDL_Point mousePosition, Screen &screen);

void restartVars(bool &restartFlag, int &carState, Road &road, NPCCar (&npcCar)[2], CarPiece &carHood, CarPiece (&pieces)[3], int &score, SDL_Point &lampPosition);

SDL_Point getMouseXY(SDL_Point mousePosition);

void carControl(Car &car, SDL_Point mousePosition, Screen screen);

bool carCollision(SDL_Point mousePosition, Car &car, NPCCar (&npcCar)[2], Screen screen, int &carState, Animation &explosion);

#endif // CONTROLS_H
