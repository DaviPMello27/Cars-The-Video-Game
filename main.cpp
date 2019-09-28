#define SDL_MAIN_HANDLED
#include <iostream>
#include <random>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>
#include <fstream>
#include "structs.h"
#include "animations.h"
#include "controls.h"
#include "text.h"
#include "menu.h"
#include "highscore.h"
#include "toi.h"
#include "resolution.h"
using namespace std;

///===============================================================================================================
///===================================================TO=DO=======================================================
///===============================================================================================================
///======                                                                                                   ======
///======                                  - EXPLODE CAR ANIMATION                                          ======
///======                                                                                                   ======
///======                                      - ADD COMMENTS                                               ======
///======                                                                                                   ======
///===============================================================================================================
///===============================================================================================================
///===============================================================================================================

int main(){
    //==========================INIT==========================
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    SDL_Window *mainWindow = SDL_CreateWindow("Cars: The Movie: The Game", 20, 20, 800, 600, SDL_WINDOW_RESIZABLE);
    SDL_SetWindowDisplayMode(mainWindow, nullptr);
    SDL_Renderer *render = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
    srand(static_cast<unsigned int>(time(nullptr)));

    //==========================VARIABLES==========================
    Screen screen = {800, 600, 0, 0, false};
    loadResolution(screen, mainWindow);
    loadFull(screen, mainWindow);
    cout << screen.w << ", " << screen.h << ", " << screen.full << "\n";
    Road road;
    Car car = {0, 0, {0, 0}, {0, 0}, 0};
    SDL_Point mouse, lamp;
    NPCCar npcCar[2];
    CarPiece carHood;
    CarPiece pieces[3];
    Menu menu = {0, 1, {0, 5}, false};
    int carState = 3, score, highscore;
    bool end = false, restart = false;
    //==========================TEXTURES==========================
    Img img = initImg(render);

    //==========================SET=HIGHSCORE==========================
    highscore = getHighscore();
    //==========================GAME-LOOP==========================
    while (!end){
        SDL_ShowCursor(SDL_DISABLE);
        //-----EVENT-----
        eventCheck(mainWindow, end, restart, highscore, carState, menu, mouse, screen);
        //==========================RESOLUTION==========================
        SDL_GetWindowSize(mainWindow, &screen.w, &screen.h);
        screen.wScale = screen.w/800.0;
        screen.hScale = screen.h/600.0;
        //==========================MOUSE==========================
        mouse = getMouseXY(mouse);
        if(menu.state == 0){
            //-----CLEAR-----
            SDL_RenderClear(render);

            //==========================RESTART==========================
            restartVars(restart, carState, road, npcCar, carHood, pieces, score, lamp);

            //==========================HIGHSCORE==========================
            if(carState == 0){
                if(score > highscore){
                    highscore = setHighscore(score);
                }
            }
            //==========================CONTROLS==========================
            if(carState > 0){
                carControl(car, mouse, screen);
            }
            //==========================RECTS==========================
            SDL_Rect carPos = {car.x - 100, car.y - 25, toi((444/2.5)*screen.hScale), toi((212/2.5)*(screen.hScale))};
            SDL_Rect* npcCarPos = new SDL_Rect[2];
            for(int i = 0; i < 2; i++){
                npcCarPos[i] = {npcCar[i].x, npcCar[i].y, toi((444/2.5)*screen.hScale), toi((212/2.5)*(screen.hScale))};
            }
            //==========================DRAWING==========================
            drawSprites(render, carState, road, carPos, npcCarPos, car, npcCar, img, screen);

            //==========================CAR=PIECES=ANIMATIONS==========================
            drawAnimation(render, carState, pieces, car, carHood, img, screen);

            //==========================ROADLOOP==========================
            road.x = roadLoop(road, carState, screen);

            //==========================NPCCAR=LOOP==========================
            if(carState > 0){
                NPCCarLoop(npcCar, score, screen, car);
            }
            //==========================LAMP=LOOP==========================
            lamp.x = lampLoop(lamp, road, screen);
            SDL_Rect lampPos = {lamp.x, 0, toi(600*screen.hScale), toi(600*screen.hScale)};
            SDL_RenderCopy(render, img.lampSprite, nullptr, &lampPos);

            //==========================WRITE=SCORE==========================
            writeText(render, score, img.font, toi((screen.w / 2.0f) - 30), 30);
            if(carState < 1 || score == 0){
                string scoreText = "Highscore: " + to_string(highscore);
                writeText(render, scoreText, img.font, screen.w / 2 - 90, 100, 14, 24);
            }
            //==========================ANTI=STAND-STILL=COUNTER==========================
            if((mouse.y > car.y - 20 && mouse.y < car.y + 20) || car.y == toi(70*screen.hScale) || car.y == toi(screen.h - 90*screen.hScale)){
                car.moveCounter++;
            } else {
                car.moveCounter = 0;
            }
            //==========================HITBOXES==========================
            carCollision(carPos, npcCarPos, mouse, car, npcCar, screen, carState);
            delete [] npcCarPos;

            ///Enable this line to show the car's hitbox
            //SDL_RenderFillRect(render, &carPos);
        //=========================================================MENU=========================================================
        } else if(menu.state > 0){
            drawMenu(render, menu, mouse, img, car, carState, screen, highscore);
        }
        drawCursor(render, mouse, img.cursor);
        SDL_RenderPresent(render);
        SDL_Delay(1000/60);
    }

    //==========================DESTROY==========================
    destroy(mainWindow, render, img);
    SDL_Quit();
    return 0;
}
