#include <SDL.h>
#include <iostream>
#include "structs.h"
#include "toi.h"

void eventCheck(SDL_Window* mainWindow, bool &end, bool &restart, bool &changeRes, Menu &menu, SDL_Point mouse, Screen &screen){
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
                    case SDLK_q:
                        end = true;
                    break;
                    case SDLK_ESCAPE:
                        menu.state = 1;
                    break;
                    case SDLK_e:
                        changeRes = true;
                    break;
                }
            break;
            case SDL_MOUSEBUTTONDOWN:
                switch(gameEvent.button.button){
                    case SDL_BUTTON_LEFT:
                    SDL_Rect test;
                    if(menu.state == 1){
                        test = {(screen.w / 2) - 150, (200 - menu.y), 300, 100};
                        if(SDL_PointInRect(&mouse, &test)){
                                restart = true;
                                menu.animate = true;
                        }
                        test = {(screen.w / 2) - 100, (350 - menu.y), 200, 75};
                        if(SDL_PointInRect(&mouse, &test)){
                                menu.state = 2;
                        }
                        test = {(screen.w / 2) - 100, (475 - menu.y), 200, 75};
                        if(SDL_PointInRect(&mouse, &test)){
                                end = true;
                        }
                    } else if (menu.state == 2){
                        for(int i = 0; i < 13; i++){
                            if(i < 6){
                                test = {(screen.w/2 - 270), (screen.h/2 - 110) + i*56, 150, 50};
                            } else {
                                test = {(screen.w/2 - 60), (screen.h/2 - 166) + (i - 6)*56, 150, 50};
                            }
                            if(SDL_PointInRect(&mouse, &test)){
                                screen.w = stoi(res[0][i]);
                                screen.h = stoi(res[1][i]);
                                SDL_SetWindowSize(mainWindow, screen.w, screen.h);
                                break;
                            }
                        }
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

void carControl(Car &car, SDL_Point mouse, Screen screen){
    car.y += (mouse.y - car.y)/10;
    car.angle.value = (mouse.y - car.y)/5;
    if(mouse.x > car.x){
        car.x += (mouse.x - car.x)/10;
    } else if (mouse.x < car.x){
        car.x -= (car.x - mouse.x)/10;
    }
    if(car.y < toi(70*screen.hScale)){
        car.y = toi(70*screen.hScale);
    } else if (car.y > toi(screen.w - 90*screen.hScale)){
        car.y = toi(screen.w - 90*screen.hScale);
    }
}
