#define SDL_MAIN_HANDLED
#include <iostream>
#include <random>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>
#include "structs.h"
#include "animations.h"
#include "controls.h"
#include "text.h"
#include "menu.h"
using namespace std;

bool collide(SDL_Rect first, SDL_Rect second){
    if(first.x + first.w > second.x && first.x < second.x + second.w && first.y < second.y + second.h && first.y + first.h > second.y){
        return true;
    }
    return false;
}

int lampLoop(SDL_Point &lamp, Road road){
    if(lamp.x < -800){
        return 1600;
    }
    return lamp.x - static_cast<int>(road.speed.x);
}

void drawCursor(SDL_Renderer *render, SDL_Point mouse, SDL_Texture *cursor){
    SDL_Rect cursorPos = {mouse.x - 15, mouse.y - 15, 30, 30};
    SDL_RenderCopy(render, cursor, nullptr, &cursorPos);
}

int main(){
    //==========================INIT==========================
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    SDL_Window *mainWindow = SDL_CreateWindow("SUPER CAR RACER THE MOVIE THE GAME 2000", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer *render = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
    srand(static_cast<unsigned int>(time(nullptr)));

    //==========================VARIABLES==========================
    Road road = {0, {20, 0}};
    Car car = {0, 0, {0, 0}, {0, 0}};
    SDL_Point mouse, lamp = {800, 0};
    Barrel barrel = {3000, rand() % 410 + 50, 0};
    CarPiece carHood = {0, 0, {0, 0}, {0, 0}, false};
    CarPiece pieces[3];
    Menu menu = {0, 1, {0, 5}, false};
    int carState = 3, score = 0;
    bool end = false, restart = false;
    //==========================TEXTURES==========================
    SDL_Texture *carSprite = IMG_LoadTexture(render, "img/car.png");
    SDL_Texture *carPieces = IMG_LoadTexture(render, "img/carPieces.png");
    SDL_Texture *carHoodSprite = IMG_LoadTexture(render, "img/carHood.png");
    SDL_Texture *bgRoad = IMG_LoadTexture(render, "img/road.png");
    SDL_Texture *barrelSprite = IMG_LoadTexture(render, "img/barrel.png");
    SDL_Texture *font = IMG_LoadTexture(render, "img/font.png");
    SDL_Texture *cursor = IMG_LoadTexture(render, "img/cursor.png");
    SDL_Texture *lampSprite = IMG_LoadTexture(render, "img/lamp.png");
    //==========================GAME-LOOP==========================
    while (!end){
        SDL_ShowCursor(SDL_DISABLE);
        //-----EVENT-----
        eventCheck(end, restart, menu, mouse);

        //==========================MOUSE==========================
        mouse = getMouseXY(mouse);
        if(menu.state == 0){
            //-----CLEAR-----
            SDL_RenderClear(render);
            //==========================RESTART==========================
            if(restart == true){
                carState = 3;
                road.speed.x = 20;
                barrel.x = 1500;
                carHood = {0, 0, {0, 0}, {0, 0}, false};
                pieces[0] = {0, 0, {0, 0}, {0, 0}, false};
                pieces[1] = {0, 0, {0, 0}, {0, 0}, false};
                pieces[2] = {0, 0, {0, 0}, {0, 0}, false};
                score = 0;
                road.x = 0;
                lamp.x = 800;
                restart = false;
            }
            if(carState > 0){
                carControl(car, mouse);
            }
            //==========================RECTS==========================
            SDL_Rect carPos = {static_cast<int>(car.x - 100), static_cast<int>(car.y - 25), 444/3, 212/3};
            SDL_Rect barrelPos = {barrel.x, barrel.y, 54, 74};

            //==========================DRAWING==========================
            drawSprites(render, carState, road, carPos, barrelPos, car, barrel, bgRoad, carSprite, barrelSprite);
            //==========================CAR=PIECES=ANIMATIONS==========================
            drawAnimation(render, carState, pieces, car, carHood, carPieces, carHoodSprite);

            //==========================ROADLOOP==========================
            road.x = roadLoop(road, carState);

            //==========================BARREL=LOOP==========================
            if(carState > 0){
                barrel.x = barrelLoop(barrel, score);
            }
            //==========================LAMP=LOOP==========================
            lamp.x = lampLoop(lamp, road);
            SDL_Rect lampPos = {lamp.x, 0, 600, 600};
            SDL_RenderCopy(render, lampSprite, nullptr, &lampPos);

            //==========================WRITE=SCORE==========================
            writeText(render, score, font, 370, 30);

            //==========================HITBOXES==========================
            if(collide(carPos, barrelPos)){
                carState--;
                barrel.x = 1500;
            }
            //=========================================================MENU=========================================================
        } else if(menu.state == 1){
            drawMenu(render, menu, mouse, bgRoad, font, car, carState);
        }
        drawCursor(render, mouse, cursor);
        SDL_RenderPresent(render);
        SDL_Delay(1000/60);
    }

    //==========================DESTROY==========================
    SDL_DestroyWindow(mainWindow);
    SDL_DestroyRenderer(render);
    SDL_DestroyTexture(carSprite);
    SDL_DestroyTexture(bgRoad);
    SDL_DestroyTexture(barrelSprite);
    SDL_DestroyTexture(carPieces);
    SDL_DestroyTexture(carHoodSprite);
    SDL_DestroyTexture(font);
    SDL_DestroyTexture(cursor);
    SDL_DestroyTexture(lampSprite);
    SDL_Quit();
    return 0;
}
