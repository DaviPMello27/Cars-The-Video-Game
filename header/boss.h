#ifndef BOSS_H
#define BOSS_H

#include "structs.h"
#include <SDL.h>

void truckBehavior(SDL_Renderer* render, Boss &truck, Img img, Car &car, Screen screen, int &score);

void planeBehavior(SDL_Renderer* render, Boss &plane, SDL_RendererFlip &planeFlip, Animation &bomb, Animation &explosion, Img img, Car &car, Screen screen, int &score);
#endif // BOSS_H
