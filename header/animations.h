#ifndef ANIMATIONS_H
#define ANIMATIONS_H
#include <SDL.h>
#include "structs.h"

void carBreak(CarPiece &piece, Mouse mouse, SDL_Renderer *render, SDL_Texture *sprite, SDL_Rect cut, SDL_Rect pos);

void carCrash(Car &car, Mouse mouse, int &carState);

int roadLoop(Road &road, int carState);

int barrelLoop(Barrel &barrel, int &score);

void drawAnimation(SDL_Renderer *render, int carState, CarPiece (&pieces)[3], Mouse mouse, CarPiece &carHood, SDL_Texture *carPieces, SDL_Texture *carHoodSprite);

void drawSprites(SDL_Renderer *render, int &carState, Road road, SDL_Rect carPos, SDL_Rect barrelPos, Car &car, Mouse mouse, SDL_Texture *bgRoad, SDL_Texture *carSprite, SDL_Texture *barrelSprite);
#endif // ANIMATIONS_H
