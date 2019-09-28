#ifndef ANIMATIONS_H
#define ANIMATIONS_H
#include <SDL.h>
#include "structs.h"

void carBreak(CarPiece &piece, SDL_Point mousePosition, SDL_Renderer *renderer, SDL_Texture *sprite, SDL_Rect cutRect, SDL_Rect posRect);

void carCrash(Car &car, int &carState);

int roadLoop(Road &road, int carState, Screen screen);

void NPCCarLoop(NPCCar (&npcCar)[2], int &score, Screen screen, Car car);

int lampLoop(SDL_Point &lampPosition, Road road, Screen screen);

void drawCursor(SDL_Renderer *renderer, SDL_Point mousePosition, SDL_Texture *cursor);

void drawAnimation(SDL_Renderer *renderer, int carState, CarPiece (&pieces)[3], Car car, CarPiece &carHood, Img images, Screen screen);

void drawSprites(SDL_Renderer *renderer, int &carState, Road road, SDL_Rect carPosRect, SDL_Rect npcCarPosRect[2], Car &car, NPCCar npcCar[2], Img images, Screen screen);

Img initImg(SDL_Renderer* render);

void destroy(SDL_Window* window, SDL_Renderer* renderer, Img &images);

#endif // ANIMATIONS_H
