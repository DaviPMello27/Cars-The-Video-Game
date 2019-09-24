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

int lampLoop(SDL_Point &lamp, Road road, Screen screen){
    if(lamp.x < -800){
        return screen.w + 800;
    }
    return lamp.x - static_cast<int>(road.speed.x * screen.wScale);
}

void drawCursor(SDL_Renderer *render, SDL_Point mouse, SDL_Texture *cursor){
    SDL_Rect cursorPos = {mouse.x - 15, mouse.y - 15, 30, 30};
    SDL_RenderCopy(render, cursor, nullptr, &cursorPos);
}

int main(){
    //==========================INIT==========================
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    SDL_Window *mainWindow = SDL_CreateWindow("Cars: The Movie: The Game", 20, 20, 800, 600, 0);
    SDL_Renderer *render = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
    srand(static_cast<unsigned int>(time(nullptr)));

    //==========================VARIABLES==========================
    Screen screen = {800, 600, 0, 0, false};
    Road road = {0, {20, 0}};
    Car car = {0, 0, {0, 0}, {0, 0}};
    SDL_Point mouse, lamp = {800, 0};
    Barrel barrel = {3000, rand() % 410 + 50, 0};
    CarPiece carHood = {0, 0, {0, 0}, {0, 0}, false};
    CarPiece pieces[3];
    Menu menu = {0, 1, {0, 5}, false};
    int carState = 3, score = 0;
    bool end = false, restart = false, changeRes = false;
    //==========================TEXTURES==========================
    Img img;
    img.carSprite = IMG_LoadTexture(render, "img/car.png");
    img.carPieces = IMG_LoadTexture(render, "img/carPieces.png");
    img.carHoodSprite = IMG_LoadTexture(render, "img/carHood.png");
    img.bgRoad = IMG_LoadTexture(render, "img/road.png");
    img.barrelSprite = IMG_LoadTexture(render, "img/barrel.png");
    img.font = IMG_LoadTexture(render, "img/font.png");
    img.cursor = IMG_LoadTexture(render, "img/cursor.png");
    img.lampSprite = IMG_LoadTexture(render, "img/lamp.png");
    //==========================GAME-LOOP==========================
    while (!end){
        SDL_ShowCursor(SDL_DISABLE);
        //-----EVENT-----
        eventCheck(end, restart, changeRes, menu, mouse, screen);
        //==========================RESOLUTION==========================
        screen.wScale = screen.w/800.0;
        screen.hScale = screen.h/600.0;
        if(changeRes){
            screen.w = 1240;
            screen.h = 720;
            changeRes = false;
            SDL_SetWindowSize(mainWindow, screen.w, screen.h);
        }
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
                carControl(car, mouse, screen);
            }
            //==========================RECTS==========================
            SDL_Rect carPos = {static_cast<int>(car.x - 100), static_cast<int>(car.y - 25), static_cast<int>((444/3)*screen.wScale), static_cast<int>((212/3)*(screen.wScale))};
            SDL_Rect barrelPos = {barrel.x, barrel.y, static_cast<int>(54*screen.wScale), static_cast<int>(74*screen.hScale)};

            //==========================DRAWING==========================
            drawSprites(render, carState, road, carPos, barrelPos, car, barrel, img, screen);

            //==========================CAR=PIECES=ANIMATIONS==========================
            drawAnimation(render, carState, pieces, car, carHood, img, screen);

            //==========================ROADLOOP==========================
            road.x = roadLoop(road, carState, screen);

            //==========================BARREL=LOOP==========================
            if(carState > 0){
                barrel.x = barrelLoop(barrel, score, screen.w);
            }
            //==========================LAMP=LOOP==========================
            lamp.x = lampLoop(lamp, road, screen);
            SDL_Rect lampPos = {lamp.x, 0, static_cast<int>(600*screen.wScale), static_cast<int>(600*screen.wScale)};
            SDL_RenderCopy(render, img.lampSprite, nullptr, &lampPos);

            //==========================WRITE=SCORE==========================
            writeText(render, score, img.font, static_cast<int>((screen.w / 2) - 30), 30);

            //==========================HITBOXES==========================
            if(collide(carPos, barrelPos)){
                carState--;
                barrel.x = screen.w + 500;
            }
            //=========================================================MENU=========================================================
        } else if(menu.state > 0){
            drawMenu(render, menu, mouse, img, car, carState, screen);
        }
        drawCursor(render, mouse, img.cursor);
        SDL_RenderPresent(render);
        SDL_Delay(1000/60);
    }

    //==========================DESTROY==========================
    SDL_DestroyWindow(mainWindow);
    SDL_DestroyRenderer(render);
    SDL_DestroyTexture(img.carSprite);
    SDL_DestroyTexture(img.bgRoad);
    SDL_DestroyTexture(img.barrelSprite);
    SDL_DestroyTexture(img.carPieces);
    SDL_DestroyTexture(img.carHoodSprite);
    SDL_DestroyTexture(img.font);
    SDL_DestroyTexture(img.cursor);
    SDL_DestroyTexture(img.lampSprite);
    SDL_Quit();
    return 0;
}
