#include <SDL.h>
#include <random>
#include "structs.h"
#include "toi.h"
#include <iostream>


void carBreak(CarPiece &piece, Car car, SDL_Renderer *render, SDL_Texture *sprite, SDL_Rect cut, SDL_Rect pos, Screen screen){
    if(!piece.broke){
        piece.speed.x = (rand() % 5 + 10)*screen.wScale;
        piece.speed.y = (rand() % 10 - 5)*screen.hScale;
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

void carCrash(Car &car, int &carState, Screen screen){
    if(carState == 0){
        car.angle.speed = rand() % 5 + 20;
        car.speed.y = (rand() % 20 - 10)*screen.hScale;
        car.speed.x = 10*screen.wScale;
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

void drawAnimation(SDL_Renderer *render, int carState, CarPiece (&pieces)[3], Car car, CarPiece &carHood, Img img, Screen screen){
    if(carState == 2 || carState == 1){
        for(int i = 0; i < 3; i++){
            SDL_Rect carPieceCut = {i*20, 0, 20, 12};
            SDL_Rect carPiecePos = {pieces[i].x, pieces[i].y, toi((20/2) * screen.hScale), toi((12/2) * screen.hScale)};
            carBreak(pieces[i], car, render, img.carPieces, carPieceCut, carPiecePos, screen);
        }
    }
    if(carState == 1 && carHood.x > -50){
        for(int i = 0; i < 3; i++){
            if(pieces[i].broke == true && carHood.broke == false){
                pieces[i] = {0, 0, {0, 0}, {0, 0}, false};
            }
        }
        SDL_Rect carHoodCut = {0, 0, 140, 140};
        SDL_Rect carHoodPos = {carHood.x, carHood.y, toi((140/3) * screen.hScale), toi((140/3) * screen.hScale)};
        carBreak(carHood, car, render, img.carHoodSprite, carHoodCut, carHoodPos, screen);
    }
}

int roadLoop(Road &road, int carState, Screen screen){
    if(road.x >= 2300){
        return 0;
    }
    if(carState > 0){
        return toi(road.x + road.speed.x * screen.wScale);
    } else {
        road.speed.x /= 1.03;
        return toi(road.x + road.speed.x * screen.wScale);
    }
}

int barrelLoop(Barrel &barrel, int &score, Screen screen, Car car){
    if(barrel.x < 0){
        if(car.moveCounter > 150){
            barrel.y = car.y - toi(20*screen.hScale);
        } else {
            barrel.y = rand() % (screen.h-100) + 50;
        }
        barrel.skin = rand() % 2;
        score++;
        return screen.w + 200;
    }
    return toi(barrel.x - 20.0 * screen.w/800.0);
}

int lampLoop(SDL_Point &lamp, Road road, Screen screen){
    if(lamp.x < -800){
        return screen.w + 800;
    }
    return lamp.x - toi(road.speed.x * screen.wScale);
}

void drawCursor(SDL_Renderer *render, SDL_Point mouse, SDL_Texture *cursor){
    SDL_Rect cursorPos = {mouse.x - 15, mouse.y - 15, 30, 30};
    SDL_RenderCopy(render, cursor, nullptr, &cursorPos);
}

void drawSprites(SDL_Renderer *render, int &carState, Road road, SDL_Rect carPos, SDL_Rect barrelPos, Car &car, Barrel barrel, Img img, Screen screen){
    SDL_Rect carCut = {0, (3-carState)*212, 444, 212};
    SDL_Rect roadCut = {road.x, 0, screen.w, 600};
    SDL_Rect roadPos = {0, 0, screen.w, screen.h};

    SDL_RenderCopy(render, img.bgRoad, &roadCut, &roadPos);
    if(carState > 0){
        SDL_RenderCopyEx(render, img.carSprite, &carCut, &carPos, car.angle.value, nullptr, SDL_FLIP_NONE);
    } else {
        carCrash(car, carState, screen);
        carPos = {car.x - 61, car.y - 50, toi((444/3)*screen.hScale), toi((212/3)*(screen.hScale))};
        carCut = {0, 424, 444, 212};
        SDL_RenderCopyEx(render, img.carSprite, &carCut, &carPos, car.angle.value, nullptr, SDL_FLIP_NONE);
    }
    SDL_Rect barrelCut = {barrel.skin * 54, 0, 54, 74};
    SDL_RenderCopy(render, img.barrelSprite, &barrelCut, &barrelPos);
}
