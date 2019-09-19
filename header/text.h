#ifndef TEXT_H
#define TEXT_H

#include <SDL.h>

void writeText(SDL_Renderer *render, int text, SDL_Texture *font, int x, int y);

void writeText(SDL_Renderer *render, const char text[], SDL_Texture *font, int x, int y);

#endif // TEXT_H
