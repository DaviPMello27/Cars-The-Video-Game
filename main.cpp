#define SDL_MAIN_HANDLED
#include <iostream>
#include <random>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;

void eventCheck(int &carState){
    //==========================EVENTS==========================
    SDL_Event gameEvent;
    while(SDL_PollEvent(&gameEvent)){
        switch(gameEvent.type){
            case SDL_QUIT:
                carState = 0;
            break;
        }
    }
}

int roadLoop(int pos){
    //==========================ROADLOOP==========================
    if(pos >= 200){
        return 0;
    }
    return pos + 20;
}

int barrelLoop(int pos, int &barrelY){
    if(pos < 0){
        barrelY = rand() % 410 + 50;
        return 1000;
    }
    return pos - 20;
}

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
    int mouseX, mouseY, carState = 3;
    int roadPos = 0;
    int barrelX = 1000, barrelY = rand() % 410 + 50;
    int pieceX = 0, pieceY = 0, pieceSpeed = rand() % 5 + 10;
    double pieceA = 0, angleSpeed = 50;
    bool carPieceFlag = false;

    //==========================TEXTURES==========================

    SDL_Texture *carSprite = IMG_LoadTexture(render, "img/car.png");
    SDL_Texture *carPiece = IMG_LoadTexture(render, "img/carPiece.png");
    SDL_Texture *bgRoad = IMG_LoadTexture(render, "img/road.png");
    SDL_Texture *barrelSprite = IMG_LoadTexture(render, "img/barrel.png");


    SDL_ShowCursor(SDL_DISABLE);

    //==========================GAME-LOOP==========================
    while (carState){
        eventCheck(carState);

        //-----CLEAR-----
        SDL_RenderClear(render);

        //==========================MOUSE==========================
        SDL_GetMouseState(&mouseX, &mouseY);
        if(mouseY < 95){
            mouseY = 95;
        } else if (mouseY > 530){
            mouseY = 530;
        }
        //==========================RECTS==========================
        SDL_Rect carPos = {mouseX - 50, mouseY - 50, 444/3, 212/3};
        SDL_Rect carCut = {0, (3-carState)*212, 444, 212};
        SDL_Rect barrelPos = {barrelX, barrelY, 54, 74};
        SDL_Rect roadCut = {roadPos, 0, 800, 600};
        SDL_Rect roadPlace = {0, 0, 800, 600};

        //==========================DRAWING==========================
        SDL_RenderCopy(render, bgRoad, &roadCut, &roadPlace);
        SDL_RenderCopy(render, carSprite, &carCut, &carPos);
        SDL_RenderCopy(render, barrelSprite, nullptr, &barrelPos);

        //==========================CAR=PIECE=ANIMATION==========================
        if(carState == 1){
            if(!carPieceFlag){
                pieceX = mouseX + 40;
                pieceY = mouseY - 30;
                carPieceFlag = true;
            }
            SDL_Rect piecePos = {pieceX, pieceY, 140/3, 140/3};
            SDL_RenderCopyEx(render, carPiece, nullptr, &piecePos, pieceA, NULL, SDL_FLIP_NONE);
            pieceY -= 2;
            pieceX += pieceSpeed;
            pieceSpeed--;
            pieceA += angleSpeed;
            angleSpeed /= 1.1;
        }
        //==========================ROADLOOP==========================
        roadPos = roadLoop(roadPos);

        //==========================BARREL=LOOP==========================
        barrelX = barrelLoop(barrelX, barrelY);

        //==========================HITBOXES==========================
        if(collide(carPos, barrelPos)){
            carState--;
            barrelX = 1500;
        }
        SDL_RenderPresent(render);
        SDL_Delay(1000/60);
    }

    //==========================GAME=OVER==========================
    SDL_Delay(5000);

    //==========================DESTROY==========================
    SDL_DestroyWindow(mainWindow);
    SDL_DestroyRenderer(render);
    SDL_DestroyTexture(carSprite);
    SDL_DestroyTexture(bgRoad);
    SDL_DestroyTexture(barrelSprite);
    SDL_DestroyTexture(carPiece);
    SDL_Quit();
    return 0;
}
