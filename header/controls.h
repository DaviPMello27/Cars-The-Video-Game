#ifndef CONTROLS_H
#define CONTROLS_H
#include <SDL.h>
#include "structs.h"

void eventCheck(SDL_Window* window, bool &endFlag, bool &restartFlag, int &highscore, int &carHealth, Menu &menu, SDL_Point mousePosition, Screen &screen, Debug &debug, Rain &rain, Night &night, int &score);

void restartVars(bool &restartFlag, int &carHealth, Road &road, NPCCar (&npcCar)[2], CarPiece &carHood, CarPiece (&pieces)[3], int &score, SDL_Point &lampPosition, Night &night, Rain &rain, Boss &truck, Boss &plane);

SDL_Point getMouseXY(SDL_Point mousePosition);

void carControl(Car &car, SDL_Point mousePosition, Screen screen, Rain &rain);

bool collide(SDL_Rect first, SDL_Rect second);

bool carCollision(Car &car, NPCCar (&npcCar)[2], Screen screen, Animation &explosion);

void changeHitbox(SDL_Point mouse, Car &car, NPCCar (&npcCar)[2]);

#endif // CONTROLS_H
