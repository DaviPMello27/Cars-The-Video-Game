#ifndef TEXT_H
#define TEXT_H

#include <iostream>
#include <SDL.h>

void writeText(SDL_Renderer *renderer, int text, SDL_Texture *font, int x, int y);

void writeText(SDL_Renderer *renderer, std::string, SDL_Texture *font, int x, int y, int w = 28, int h = 48);

#endif // TEXT_H
