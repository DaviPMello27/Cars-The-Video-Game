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
using namespace std;

bool collide(SDL_Rect first, SDL_Rect second){
    if(first.x + first.w > second.x && first.x < second.x + second.w && first.y < second.y + second.h && first.y + first.h > second.y){
        return true;
    }
    return false;
}

int main(){
    //==========================INIT==========================
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);

    //==========================WINDOW==========================
    SDL_Window *mainWindow = SDL_CreateWindow("SUPER CAR RACER THE MOVIE THE GAME 2000", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);

    //==========================RENDERER==========================
    SDL_Renderer *render = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
    srand(static_cast<unsigned int>(time(nullptr)));

    //==========================VARIABLES==========================
    Road road = {0, {20, 0}};
    Car car = {0, 0, {0, 0}, {0, 0}};
    Mouse mouse;
    Barrel barrel = {3000, rand() % 410 + 50};
    CarPiece carHood = {0, 0, {0, 0}, {0, 0}, false};
    CarPiece pieces[3];
    int carState = 3, score = 0;
    bool end = false, restart = false;
    //==========================TEXTURES==========================

    SDL_Texture *carSprite = IMG_LoadTexture(render, "img/car.png");
    SDL_Texture *carPieces = IMG_LoadTexture(render, "img/carPieces.png");
    SDL_Texture *carHoodSprite = IMG_LoadTexture(render, "img/carHood.png");
    SDL_Texture *bgRoad = IMG_LoadTexture(render, "img/road.png");
    SDL_Texture *barrelSprite = IMG_LoadTexture(render, "img/barrel.png");
    SDL_Texture *font = IMG_LoadTexture(render, "img/font.png");

    //-----REMOVE-CURSOR-----
    SDL_ShowCursor(SDL_DISABLE);

    //==========================GAME-LOOP==========================
    while (!end){
        //-----EVENT-----
        eventCheck(end, restart);

        //-----CLEAR-----
        SDL_RenderClear(render);

        //==========================MOUSE==========================
        mouse = getMouseXY(mouse);
        //==========================RECTS==========================
        SDL_Rect carPos = {mouse.x - 50, mouse.y - 50, 444/3, 212/3};
        SDL_Rect barrelPos = {barrel.x, barrel.y, 54, 74};

        //==========================DRAWING==========================
        drawSprites(render, carState, road, carPos, barrelPos, car, mouse, bgRoad, carSprite, barrelSprite);

        //==========================CAR=PIECES=ANIMATIONS==========================
        drawAnimation(render, carState, pieces, mouse, carHood, carPieces, carHoodSprite);

        //==========================WRITE=SCORE==========================
        writeText(render, score, font, 370, 30);

        //==========================ROADLOOP==========================
        road.x = roadLoop(road, carState);

        //==========================BARREL=LOOP==========================
        if(carState > 0){
            barrel.x = barrelLoop(barrel, score);
        }
        //==========================HITBOXES==========================
        if(collide(carPos, barrelPos)){
            carState--;
            barrel.x = 1500;
        }
        if(restart == true){
            carState = 3;
            road.speed.x = 20;
            barrel.x = 1500;
            carHood = {0, 0, {0, 0}, {0, 0}, false};
            pieces[0] = {0, 0, {0, 0}, {0, 0}, false};
            pieces[1] = {0, 0, {0, 0}, {0, 0}, false};
            pieces[2] = {0, 0, {0, 0}, {0, 0}, false};
            score = 0;
            restart = false;
        }
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
    SDL_Quit();
    return 0;
}
