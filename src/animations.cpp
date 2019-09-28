#include <SDL.h>
#include <SDL_image.h>
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
        SDL_Rect carHoodPos = {carHood.x, carHood.y, toi((140/2.5) * screen.hScale), toi((140/2.5) * screen.hScale)};
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

void NPCCarLoop(NPCCar (&npcCar)[2], int &score, Screen screen, Car car){
    for(int i = 0; i < 2; i++){
        if(npcCar[i].x < -212*screen.hScale){
            if(car.moveCounter > 150){
                npcCar[i].y = car.y - toi(20*screen.hScale);
            } else {
                npcCar[i].y = rand() % (screen.h-100) + 50;
            }
            while(npcCar[i].y > npcCar[(i + 1) % 2].y - 212/2.5 && npcCar[i].y < npcCar[(i + 1) % 2].y + 424/2.5){
                npcCar[i].y = rand() % (screen.h-100) + 50;
            }
            npcCar[i].speed.x = rand() % 10 + 15;
            npcCar[i].skin = rand() % 15;
            score++;
            if(npcCar[(i + 1) % 2].x < screen.w/2){
                npcCar[i].x = screen.w + 200;
            } else {
                npcCar[i].x = npcCar[(i + 1) % 2].x + rand() % 200 + (screen.w/2);
            }
            return;
        }
        npcCar[i].x = toi(npcCar[i].x - npcCar[i].speed.x * screen.wScale);
    }
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

void drawCarSkin(SDL_Renderer* render, Img img, SDL_Rect npcCarPos[2], NPCCar npcCar[2]){
    for(int i = 0; i < 2; i++){
        if(npcCar[i].skin < 5){
            SDL_Rect npcCarCut = {0, npcCar[i].skin * 212, 444, 212};
            SDL_RenderCopy(render, img.npcCarSprite, &npcCarCut, &npcCarPos[i]);
        } else if(npcCar[i].skin >= 5 && npcCar[i].skin < 7){
            SDL_Rect npcCarCut = {0, (npcCar[i].skin - 5) * 204, 452, 204};
            SDL_RenderCopy(render, img.npcCarSprite2, &npcCarCut, &npcCarPos[i]);
        } else if(npcCar[i].skin >= 7 && npcCar[i].skin < 9){
            SDL_Rect npcCarCut = {0, (npcCar[i].skin - 7) * 216, 456, 216};
            SDL_RenderCopy(render, img.npcCarSprite3, &npcCarCut, &npcCarPos[i]);
        } else if(npcCar[i].skin >= 9 && npcCar[i].skin < 12){
            SDL_Rect npcCarCut = {0, (npcCar[i].skin - 9) * 220, 448, 220};
            SDL_RenderCopy(render, img.npcCarSprite4, &npcCarCut, &npcCarPos[i]);
        } else if(npcCar[i].skin >= 12 && npcCar[i].skin < 15){
            SDL_Rect npcCarCut = {0, (npcCar[i].skin - 12) * 204, 448, 204};
            SDL_RenderCopy(render, img.npcCarSprite5, &npcCarCut, &npcCarPos[i]);
        }
    }
}

void drawSprites(SDL_Renderer *render, int &carState, Road road, SDL_Rect carPos, SDL_Rect npcCarPos[2], Car &car, NPCCar npcCar[2], Img img, Screen screen){
    SDL_Rect carCut = {0, (3-carState)*212, 444, 212};
    SDL_Rect roadCut = {road.x, 0, screen.w, 600};
    SDL_Rect roadPos = {0, 0, screen.w, screen.h};

    SDL_RenderCopy(render, img.bgRoad, &roadCut, &roadPos);
    if(carState > 0){
        SDL_RenderCopyEx(render, img.carSprite, &carCut, &carPos, car.angle.value, nullptr, SDL_FLIP_NONE);
    } else {
        carCrash(car, carState, screen);
        carPos = {car.x - 61, car.y - 50, toi((444/2.5)*screen.hScale), toi((212/2.5)*(screen.hScale))};
        carCut = {0, 424, 444, 212};
        SDL_RenderCopyEx(render, img.carSprite, &carCut, &carPos, car.angle.value, nullptr, SDL_FLIP_NONE);
    }
    if(carState > 0){
        drawCarSkin(render, img, npcCarPos, npcCar);
    }
}

Img initImg(SDL_Renderer* render){
    Img img;
    img.carSprite = IMG_LoadTexture(render, "img/car.png");
    img.carPieces = IMG_LoadTexture(render, "img/carPieces.png");
    img.carHoodSprite = IMG_LoadTexture(render, "img/carHood.png");
    img.bgRoad = IMG_LoadTexture(render, "img/road.png");
    img.npcCarSprite = IMG_LoadTexture(render, "img/otherCars.png");
    img.npcCarSprite2 = IMG_LoadTexture(render, "img/otherCars2.png");
    img.npcCarSprite3 = IMG_LoadTexture(render, "img/otherCars3.png");
    img.npcCarSprite4 = IMG_LoadTexture(render, "img/otherCars4.png");
    img.npcCarSprite5 = IMG_LoadTexture(render, "img/otherCars5.png");
    img.font = IMG_LoadTexture(render, "img/font.png");
    img.cursor = IMG_LoadTexture(render, "img/cursor.png");
    img.lampSprite = IMG_LoadTexture(render, "img/lamp.png");
    return img;
}

void destroy(SDL_Window* mainWindow, SDL_Renderer* render, Img &img){
    SDL_DestroyTexture(img.carSprite);
    SDL_DestroyTexture(img.bgRoad);
    SDL_DestroyTexture(img.npcCarSprite);
    SDL_DestroyTexture(img.npcCarSprite2);
    SDL_DestroyTexture(img.npcCarSprite3);
    SDL_DestroyTexture(img.npcCarSprite4);
    SDL_DestroyTexture(img.npcCarSprite5);
    SDL_DestroyTexture(img.carPieces);
    SDL_DestroyTexture(img.carHoodSprite);
    SDL_DestroyTexture(img.font);
    SDL_DestroyTexture(img.cursor);
    SDL_DestroyTexture(img.lampSprite);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(mainWindow);
}
