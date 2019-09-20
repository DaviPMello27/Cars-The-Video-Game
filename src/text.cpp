#include <iostream>
#include <SDL.h>

void writeText(SDL_Renderer *render, int text, SDL_Texture *font, int x, int y){
    std::string stringText = std::to_string(text);
    size_t i = 0;
    while(stringText[i] != 0){
        SDL_Rect textCut = {(stringText[i] - 48) * 16, 0, 16, 24};
        SDL_Rect textPos = {x + (30 * static_cast<int>(i)), y, 16*2, 24*2};
        SDL_RenderCopy(render, font, &textCut, &textPos);
        i++;
    }
}

void writeText(SDL_Renderer *render, const char text[], SDL_Texture *font, int x, int y, int w = 28, int h = 48){
    int i = 0;
    while(text[i] != 0){
        SDL_Rect textCut = {(text[i] - 48) * 16, 0, 16, 24};
        SDL_Rect textPos = {x + ((w-2) * i), y, w, h};
        SDL_RenderCopy(render, font, &textCut, &textPos);
        i++;
    }
}
