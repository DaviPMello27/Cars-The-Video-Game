#include <SDL.h>
#include <iostream>
#include <random>
#include "structs.h"
#include "toi.h"
#include "highscore.h"
#include "resolution.h"

void eventCheck(SDL_Window* mainWindow, bool &end, bool &restart, int &highscore, int carState, Menu &menu, SDL_Point mouse, Screen &screen){
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
                    case SDLK_f:
                    if(screen.full == false){
                        SDL_SetWindowFullscreen(mainWindow, SDL_WINDOW_FULLSCREEN);
                        screen.full = true;
                    } else {
                        SDL_SetWindowFullscreen(mainWindow, 0);
                        screen.full = false;
                    }
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
                                saveResolution(screen, i);
                                break;
                            }
                        }
                        test = {25, (screen.h - 60), 150, 50};
                        if(SDL_PointInRect(&mouse, &test)){
                            menu.state = 1;
                        }
                        test = {screen.w/2 + 170, (screen.h/2 - 170) + 150, 50, 50};
                        if(SDL_PointInRect(&mouse, &test)){
                            if(screen.full == false){
                                SDL_SetWindowFullscreen(mainWindow, SDL_WINDOW_FULLSCREEN);
                                screen.full = true;
                            } else {
                                SDL_SetWindowFullscreen(mainWindow, 0);
                                screen.full = false;
                            }
                            saveFull(screen);
                        }
                        test = {screen.w/2 + 170, (screen.h/2 - 70) + 150, 50, 50};
                        if(SDL_PointInRect(&mouse, &test)){
                            highscore = setHighscore(0);
                        }
                    }
                    if(menu.state == 0 && carState < 1){
                        restart = true;
                    }
                    break;
                }
            break;
        }
    }
}

void restartVars(bool &restart, int &carState, Road &road, NPCCar (&npcCar)[2], CarPiece &carHood, CarPiece (&pieces)[3], int &score, SDL_Point &lamp){
    if(restart == true){
        carState = 3;
        road.speed.x = 20;
        npcCar[0] = {3000, rand() % 410 + 50, rand() % 15, {20, 0}};
        npcCar[1] = {4000, rand() % 410 + 50, rand() % 15, {20, 0}};
        carHood = {0, 0, {0, 0}, {0, 0}, false};
        pieces[0] = {0, 0, {0, 0}, {0, 0}, false};
        pieces[1] = {0, 0, {0, 0}, {0, 0}, false};
        pieces[2] = {0, 0, {0, 0}, {0, 0}, false};
        score = 0;
        road = {0, {30, 0}};
        lamp = {800, 0};
        restart = false;
    }
}

SDL_Point getMouseXY(SDL_Point mouse){
    SDL_GetMouseState(&mouse.x, &mouse.y);
    return {mouse.x, mouse.y};
}

void carControl(Car &car, SDL_Point mouse, Screen screen){
    double newMouseY = mouse.y - 20 * screen.hScale;
    double newMouseX = mouse.x - 20 * screen.hScale;
    car.y += ((newMouseY - car.y)/10);
    car.x += (newMouseX - car.x)/10;
    car.angle.value = (newMouseY - car.y)/5;
    if(car.y < toi(70*screen.hScale)){
        car.y = toi(70*screen.hScale);
    } else if (car.y > toi(screen.h - 90*screen.hScale)){
        car.y = toi(screen.h - 90*screen.hScale);
    }
}

bool collide(SDL_Rect first, SDL_Rect second){
    if(first.x + first.w > second.x && first.x < second.x + second.w && first.y < second.y + second.h && first.y + first.h > second.y){
        return true;
    }
    return false;
}

void carCollision(SDL_Rect &carPos, SDL_Rect npcCarPos[2], SDL_Point mouse, Car car, NPCCar (&npcCar)[2], Screen screen, int &carState){
    for(int i = 0; i < 2; i++){
        carPos.w -= abs(((mouse.y - car.y)/3));
        carPos.x += abs(((mouse.y - car.y)/5));
        carPos.y += ((mouse.y - car.y)/10);
        if(collide(carPos, npcCarPos[i])){
            carState--;
            npcCar[i].x = screen.w + 500;
            npcCar[i].speed.x = rand() % 10 + 10;
            if(car.moveCounter > 150){
                npcCar[i].y = car.y - toi(20*screen.hScale);
            } else {
                npcCar[i].y = rand() % (screen.h-100) + 50;
            }
        }
    }
}
