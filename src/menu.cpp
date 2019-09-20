#include <SDL.h>
#include "structs.h"
#include "text.h"

void createButton(SDL_Renderer *render, SDL_Point &mouse, int x, int y, int w, int h){
    SDL_Rect button = {x, y, w, h};
    if(SDL_PointInRect(&mouse, &button)){
        SDL_SetRenderDrawColor(render, 255, 255, 255, 64);
    } else {
        SDL_SetRenderDrawColor(render, 255, 255, 255, 24);
    }
    SDL_RenderFillRect(render, &button);
}

void drawMenu(SDL_Renderer *render, Menu &menu, SDL_Point mouse, SDL_Texture *bgRoad, SDL_Texture *font, Car &car, int &carState){
    SDL_Rect bgCut = {0, 0, 800, 600};
    SDL_RenderCopy(render, bgRoad, &bgCut, nullptr);
    SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(render, 0, 0, 0, 128);
    bgCut = {0, static_cast<int>(0 - menu.y), 800, 600};
    SDL_RenderFillRect(render, &bgCut);
    writeText(render, "CARS: THE MOVIE: THE GAME", font, 65, static_cast<int>(100 - menu.y));
    createButton(render, mouse, 250, static_cast<int>(200 - menu.y), 300, 100);
    writeText(render, "START", font, 300, static_cast<int>(222 - menu.y), 44, 72);
    createButton(render, mouse, 300, static_cast<int>(350 - menu.y), 200, 75);
    writeText(render, "Options", font, 311, static_cast<int>(370 - menu.y));
    createButton(render, mouse, 300, static_cast<int>(475 - menu.y), 200, 75);
    writeText(render, "Quit", font, 350, static_cast<int>(495 - menu.y));
    if(menu.animate){
        menu.y += menu.speed.y;
        menu.speed.y *= 1.2;
        if(menu.y > 1000){
            menu.y = 0;
            menu.speed.y = 3;
            menu.animate = false;
            menu.state = 0;
            car = {mouse.x, mouse.y, {0, 0}, {0, 0}};
            carState = 3;
        }
    }
}
