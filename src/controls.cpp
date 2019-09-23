#include <SDL.h>
#include "structs.h"

void eventCheck(bool &end, bool &restart, Menu &menu, SDL_Point mouse){
    SDL_Event gameEvent;
    while(SDL_PollEvent(&gameEvent)){
        switch(gameEvent.type){
            case SDL_QUIT:
                end = true;
            break;
            case SDL_KEYDOWN:
                switch(gameEvent.key.keysym.sym){
                    case SDLK_r:
                        restart = true;
                    break;
                    case SDLK_ESCAPE:
                        menu.state = 1;
                    break;
                }
            break;
            case SDL_MOUSEBUTTONDOWN:
                switch(gameEvent.button.button){
                    case SDL_BUTTON_LEFT:
                    SDL_Rect test = {250, 200, 300, 100};
                    if(SDL_PointInRect(&mouse, &test)){
                            //menu.state = 0;
                            restart = true;
                            menu.animate = true;
                    }
                    test = {300, 350, 200, 75};
                    if(SDL_PointInRect(&mouse, &test)){
                            end = true;
                    }
                    test = {300, 475, 200, 75};
                    if(SDL_PointInRect(&mouse, &test)){
                            end = true;
                    }
                    break;
                }
            break;
        }
    }
}

SDL_Point getMouseXY(SDL_Point mouse){
    SDL_GetMouseState(&mouse.x, &mouse.y);
    return {mouse.x, mouse.y};
}

void carControl(Car &car, SDL_Point mouse){
    car.y += (mouse.y - car.y)/10;
    car.angle.value = (mouse.y - car.y)/5;
    if(mouse.x > car.x){
        car.x += (mouse.x - car.x)/10;
    } else if (mouse.x < car.x){
        car.x -= (car.x - mouse.x)/10;
    }
    if(car.y < 70){
        car.y = 70;
    } else if (car.y > 510){
        car.y = 510;
    }
}
