#ifndef ANIMATIONS_H
#define ANIMATIONS_H
#include <SDL.h>
#include "structs.h"

int roadLoop(Road &road, int carState, Screen screen);

void NPCCarLoop(NPCCar (&npcCar)[2], int &score, Screen screen, Car car, bool restart, bool restart2);

int lampLoop(SDL_Point &lampPosition, Road road, Screen screen);

void drawCursor(SDL_Renderer *renderer, SDL_Point mousePosition, SDL_Texture *cursor);

void drawAnimation(SDL_Renderer *renderer, CarPiece (&pieces)[3], Car car, CarPiece &carHood, Img images, Screen screen);

void drawSprites(SDL_Renderer *renderer, Road road, Car &car, NPCCar npcCar[2], Img images, Screen screen, bool night, Rain rain);

void explodeAnimation(SDL_Renderer *render, Img img, Animation &explosion);

void toggleNight(Night &night, int score);

void toggleRain(SDL_Renderer *render, Rain &rain, SDL_Texture* sprite, int score);

Img initImg(SDL_Renderer* render);

void destroy(SDL_Window* window, SDL_Renderer* renderer, Img &images);

#endif // ANIMATIONS_H
