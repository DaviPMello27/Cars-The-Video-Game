#include <SDL.h>
#include <random>
#include "structs.h"
#include <iostream>


void carBreak(CarPiece &piece, Car car, SDL_Renderer *render, SDL_Texture *sprite, SDL_Rect cut, SDL_Rect pos){
    if(!piece.broke){
        piece.speed.x = rand() % 5 + 10;
        piece.speed.y = rand() % 10 - 5;
        piece.angle.speed = rand() % 10 + 30;
        piece.x = car.x + 20;
        piece.y = car.y;
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

void carCrash(Car &car, int &carState){
    if(carState == 0){
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

void drawAnimation(SDL_Renderer *render, int carState, CarPiece (&pieces)[3], Car car, CarPiece &carHood, SDL_Texture *carPieces, SDL_Texture *carHoodSprite){
    if(carState == 2 || carState == 1){
        for(int i = 0; i < 3; i++){
            SDL_Rect carPieceCut = {i*20, 0, 20, 12};
            SDL_Rect carPiecePos = {pieces[i].x, pieces[i].y, 20/2, 12/2};
            carBreak(pieces[i], car, render, carPieces, carPieceCut, carPiecePos);
        }
    }
    if(carState == 1 && carHood.x > -50){
        for(int i = 0; i < 3; i++){
            if(pieces[i].broke == true && carHood.broke == false){
                pieces[i] = {0, 0, {0, 0}, {0, 0}, false};
            }
        }
        SDL_Rect carHoodCut = {0, 0, 140, 140};
        SDL_Rect carHoodPos = {carHood.x, carHood.y, 140/3, 140/3};
        carBreak(carHood, car, render, carHoodSprite, carHoodCut, carHoodPos);
    }
}

int roadLoop(Road &road, int carState){
    if(road.x >= 2300){
        return 0;
    }
    if(carState > 0){
        return static_cast<int>(road.x + road.speed.x);
    } else {
        road.speed.x /= 1.03;
        return static_cast<int>(road.x + road.speed.x);
    }
}

int barrelLoop(Barrel &barrel, int &score){
    if(barrel.x < 0){
        barrel.y = rand() % 410 + 50;
        barrel.skin = rand() % 2;
        score++;
        return 1000;
    }
    return barrel.x - 20;
}

void drawSprites(SDL_Renderer *render, int &carState, Road road, SDL_Rect carPos, SDL_Rect barrelPos, Car &car, Barrel barrel, SDL_Texture *bgRoad, SDL_Texture *carSprite, SDL_Texture *barrelSprite){
    SDL_Rect carCut = {0, (3-carState)*212, 444, 212};
    SDL_Rect roadCut = {road.x, 0, 800, 600};
    SDL_Rect roadPos = {0, 0, 800, 600};

    SDL_RenderCopy(render, bgRoad, &roadCut, &roadPos);
    if(carState > 0){
        SDL_RenderCopyEx(render, carSprite, &carCut, &carPos, car.angle.value, nullptr, SDL_FLIP_NONE);
    } else {
        carCrash(car, carState);
        carPos = {car.x - 61, car.y - 50, 444/3, 212/3};
        carCut = {0, 424, 444, 212};
        SDL_RenderCopyEx(render, carSprite, &carCut, &carPos, car.angle.value, nullptr, SDL_FLIP_NONE);
    }
    SDL_Rect barrelCut = {barrel.skin * 54, 0, 54, 74};
    SDL_RenderCopy(render, barrelSprite, &barrelCut, &barrelPos);
}
