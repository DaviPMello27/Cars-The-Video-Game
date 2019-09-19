#define SDL_MAIN_HANDLED
#include <iostream>
#include <random>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;

struct Mouse {
    int x;
    int y;
};

struct Barrel {
    int x;
    int y;
};

struct Angle {
    double speed;
    double value;
};

struct Speed {
    double x;
    double y;
};

struct Car {
    int x;
    int y;
    Angle angle;
    Speed speed;
};

struct Road {
    int x;
    Speed speed;
};

struct CarPiece {
    int x;
    int y;
    Speed speed;
    Angle angle;
    bool broke;
};

void eventCheck(bool &end, bool &restart){
    //==========================EVENTS==========================
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
                        end = true;
                    break;
                }
            break;
        }
    }
}

int roadLoop(Road &road, int carState){
    if(road.x >= 200){
        return 0;
    }
    if(carState > 0){
        return static_cast<int>(road.x + road.speed.x);
    } else {
        road.speed.x /= 1.03;
        return static_cast<int>(road.x + road.speed.x);
    }
}

int barrelLoop(int pos, Barrel &barrel){
    if(pos < 0){
        barrel.y = rand() % 410 + 50;
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

void carBreak(CarPiece &piece, Mouse mouse, SDL_Renderer *render, SDL_Texture *sprite, SDL_Rect cut, SDL_Rect pos){
    if(!piece.broke){
        piece.speed.x = rand() % 5 + 10;
        piece.speed.y = rand() % 10 - 5;
        piece.angle.speed = rand() % 10 + 30;
        piece.x = mouse.x + 40;
        piece.y = mouse.y - 30;
        pos.x = piece.x;
        pos.y = piece.y;
        piece.broke = true;
    }
    SDL_RenderCopyEx(render, sprite, &cut, &pos, static_cast<double>(piece.angle.value), nullptr, SDL_FLIP_NONE);
    piece.y -= piece.speed.y;
    piece.x += piece.speed.x;
    piece.speed.x--;
    piece.angle.value += piece.angle.speed;
    piece.angle.speed /= 1.1;
}

void carCrash(Car &car, Mouse mouse, int &carState){
    if(carState == 0){
        car.x = mouse.x;
        car.y = mouse.y;
        car.angle.speed = rand() % 5 + 20;
        car.speed.y = rand() % 20 - 10;
        car.speed.x = 10;
        carState = -1;
    }
    car.angle.value += car.angle.speed;
    car.angle.speed /= 1.05;
    if(car.speed.y > 0.5){
        car.y += car.speed.y;
        car.speed.y /= 1.05;
    }
    if(car.speed.x > 0.05){
        car.x -= car.speed.x;
        car.speed.x /= 1.1;
    }
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
    int carState = 3;
    bool end = false, restart = false;
    //==========================TEXTURES==========================

    SDL_Texture *carSprite = IMG_LoadTexture(render, "img/car.png");
    SDL_Texture *carPieces = IMG_LoadTexture(render, "img/carPieces.png");
    SDL_Texture *carHoodSprite = IMG_LoadTexture(render, "img/carHood.png");
    SDL_Texture *bgRoad = IMG_LoadTexture(render, "img/road.png");
    SDL_Texture *barrelSprite = IMG_LoadTexture(render, "img/barrel.png");


    SDL_ShowCursor(SDL_DISABLE);

    //==========================GAME-LOOP==========================
    while (!end){
        eventCheck(end, restart);

        //-----CLEAR-----
        SDL_RenderClear(render);

        //==========================MOUSE==========================
        SDL_GetMouseState(&mouse.x, &mouse.y);
        if(mouse.y < 95){
            mouse.y = 95;
        } else if (mouse.y > 530){
            mouse.y = 530;
        }
        //==========================RECTS==========================
        SDL_Rect carPos = {mouse.x - 50, mouse.y - 50, 444/3, 212/3};
        SDL_Rect carCut = {0, (3-carState)*212, 444, 212};
        SDL_Rect barrelPos = {barrel.x, barrel.y, 54, 74};
        SDL_Rect roadCut = {road.x, 0, 800, 600};
        SDL_Rect roadPos = {0, 0, 800, 600};

        //==========================DRAWING==========================
        SDL_RenderCopy(render, bgRoad, &roadCut, &roadPos);
        if(carState > 0){
            SDL_RenderCopy(render, carSprite, &carCut, &carPos);
        } else {
            carCrash(car, mouse, carState);
            carPos = {car.x - 50, car.y - 50, 444/3, 212/3};
            carCut = {0, 424, 444, 212};
            SDL_RenderCopyEx(render, carSprite, &carCut, &carPos, car.angle.value, nullptr, SDL_FLIP_NONE);
        }
        SDL_RenderCopy(render, barrelSprite, nullptr, &barrelPos);

        //==========================CAR=PIECES=ANIMATIONS==========================
        if(carState == 2){
            for(int i = 0; i < 3; i++){
                SDL_Rect carPieceCut = {i*20, 0, 20, 12};
                SDL_Rect carPiecePos = {pieces[i].x, pieces[i].y, 20/2, 12/2};
                carBreak(pieces[i], mouse, render, carPieces, carPieceCut, carPiecePos);
            }
        }
        if(carState == 1 && carHood.x > -50){
            SDL_Rect carHoodCut = {0, 0, 140, 140};
            SDL_Rect carHoodPos = {carHood.x, carHood.y, 140/3, 140/3};
            carBreak(carHood, mouse, render, carHoodSprite, carHoodCut, carHoodPos);
        }
        //==========================ROADLOOP==========================
        road.x = roadLoop(road, carState);

        //==========================BARREL=LOOP==========================
        if(carState > 0){
            barrel.x = barrelLoop(barrel.x, barrel);
        }
        //==========================HITBOXES==========================
        if(collide(carPos, barrelPos)){
            carState--;
            barrel.x = 1500;
        }
        if(restart == true){
            carState = 3;
            road.speed.x = 20;
            carHood = {0, 0, {0, 0}, {0, 0}, false};
            pieces[0] = {0, 0, {0, 0}, {0, 0}, false};
            pieces[1] = {0, 0, {0, 0}, {0, 0}, false};
            pieces[2] = {0, 0, {0, 0}, {0, 0}, false};
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
    SDL_Quit();
    return 0;
}
