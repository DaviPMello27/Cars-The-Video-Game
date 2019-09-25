#ifndef ANIMATIONS_H
#define ANIMATIONS_H
#include <SDL.h>
#include "structs.h"

void carBreak(CarPiece &piece, SDL_Point mouse, SDL_Renderer *render, SDL_Texture *sprite, SDL_Rect cut, SDL_Rect pos);

void carCrash(Car &car, int &carState);

int roadLoop(Road &road, int carState, Screen screen);

int barrelLoop(Barrel &barrel, int &score, int screenWidth);

int lampLoop(SDL_Point &lamp, Road road, Screen screen);

void drawCursor(SDL_Renderer *render, SDL_Point mouse, SDL_Texture *cursor);

void drawAnimation(SDL_Renderer *render, int carState, CarPiece (&pieces)[3], Car car, CarPiece &carHood, Img img, Screen screen);

void drawSprites(SDL_Renderer *render, int &carState, Road road, SDL_Rect carPos, SDL_Rect barrelPos, Car &car, Barrel barrel, Img img, Screen screen);
#endif // ANIMATIONS_H
