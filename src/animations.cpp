//////========----------------CARS: THE MOVIE: THE GAME----------------========//////
///                            09/09/2019 - XX/XX/2019                            ///
///                             COPYRIGHT DAVI MELLO                              ///
//////========---------------------------------------------------------========//////

///These will be the EN-US comments
//Esses serão os comentários em PT-BR

#include <SDL.h>
#include <SDL_image.h>
#include <random>
#include "structs.h"
#include "toi.h"
#include <iostream>


///carBreak():
///
///Defines the car pieces' starting position and directions, and animates them.

//carBreak():
//
//Define a posição inicial das peças do carro, e aplica a animação.

void carBreak(CarPiece &piece, Car car, SDL_Renderer *render, SDL_Texture *sprite, Screen screen){
    if(!piece.broke){
        ///(This runs only once) Defines the position and speeds.
        //(Isto é executado apenas uma vez) Define as posições e as velocidades.
        piece.speed.x = (rand() % 5 + 10)*screen.wScale;
        piece.speed.y = (rand() % 10 - 5)*screen.hScale;
        piece.angle.speed = rand() % 10 + 30;
        piece.x = car.x + 20;
        piece.y = car.y;
        piece.pos.x = piece.x;
        piece.pos.y = piece.y;
        piece.broke = true;
    }

    ///Draws the pieces.
    //Desenha as peças.
    SDL_RenderCopyEx(render, sprite, &piece.cut, &piece.pos, static_cast<double>(piece.angle.value), nullptr, SDL_FLIP_NONE);

    ///Applies the speeds to the positions and angles, and increases them.
    //Aplica as velocidades e as aumenta.
    piece.y -= piece.speed.y;
    piece.x += piece.speed.x;
    piece.speed.x--;
    piece.angle.value += piece.angle.speed;
    piece.angle.speed /= 1.1;
}


///carCrash():
///
///Same as carBreak(), but the whole car makes a different animation.

//carCrash():
//
//Faz o mesmo que o carBreak(), mas o carro inteiro faz uma animação diferente.

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


///drawAnimation():
///
///Applies the animations to the sprites.

//drawAnimation():
//
//Aplica as animações aos sprites.

void drawAnimation(SDL_Renderer *render, CarPiece (&pieces)[3], Car car, CarPiece &carHood, Img img, Screen screen){
    ///Car pieces (first and second hit):
    //Peças do carro (na primeira e segunda colisão):
    if(car.health == 2 || car.health == 1){
        for(int i = 0; i < 3; i++){
            pieces[i].cut = {i*20, 0, 20, 12};
            pieces[i].pos = {pieces[i].x, pieces[i].y, toi((20/2) * screen.hScale), toi((12/2) * screen.hScale)};
            carBreak(pieces[i], car, render, img.carPieces, screen);
        }
    }
    ///Car pieces and hood (second hit):
    //Peças do carro e capô (segunda colisão):
    if(car.health == 1 && carHood.x > -50){
        ///Reset the pieces:
        //Reinicializar as peças:
        for(int i = 0; i < 3; i++){
            if(pieces[i].broke == true && carHood.broke == false){
                pieces[i] = {0, 0, {0, 0}, {0, 0}, false, {0, 0, 0, 0}, {0, 0, 0, 0}};
            }
        }
        carHood.cut = {0, 0, 140, 140};
        carHood.pos = {carHood.x, carHood.y, toi((140/2.5) * screen.hScale), toi((140/2.5) * screen.hScale)};
        carBreak(carHood, car, render, img.carHoodSprite, screen);
    }
}


///roadLoop():
///
///Resets the road position, moves it or stops it.

//roadLoop():
//
//Reinicializa a posição da estrada, a move, ou pára.

int roadLoop(Road &road, int carState, Screen screen){
    ///Reset:
    //Reinicalizar:
    if(road.x >= 2300){
        return 0;
    }
    ///Move:
    //Mover:
    if(carState > 0){
        return toi(road.x + road.speed.x * screen.wScale);
    } else {
        ///Stop:
        //Parar:
        road.speed.x /= 1.03;
        return toi(road.x + road.speed.x * screen.wScale);
    }
}


///NPCCarLoop():
///
///Resets the positions of the NPC cars, or moves them.

//NPCCarsLoop():
//
//Reinicializa as posições dos carros NPC, ou os move.

void NPCCarLoop(NPCCar (&npcCar)[2], int &score, Screen screen, Car car, bool restart){
    for(int i = 0; i < 2; i++){
        if(npcCar[i].x < -500 * screen.hScale && !restart){
            ///Anti stand-still counter:
            //Contador anti-ficar-parado:
            if(car.moveCounter > 150){
                npcCar[i].y = car.y - toi(20*screen.hScale);
            } else {
                npcCar[i].y = rand() % (screen.h-100) + 50;
            }

            ///Checks if the cars arent too next to each other, in relation to the y-axis:
            //Checa se os carros não estão muito pertos um do outro em relação ao eixo y:
            while(npcCar[i].y > npcCar[(i + 1) % 2].y - 212/2.5 && npcCar[i].y < npcCar[(i + 1) % 2].y + 424/2.5){
                npcCar[i].y = rand() % (screen.h-100) + 50;
            }

            score++;

            ///Sets the speed and the sprite:
            //Seleciona a velocidade e o sprite:
            npcCar[i].speed.x = (rand() % 10 + 15);
            npcCar[i].skin = rand() % 15;

            ///Checks if the cars arent too next to each other, in relation to the x-axis:
            //Checa se os carros não estão muito pertos um do outro em relação ao eixo x:
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


///lampLoop():
///
///Resets and applies speed to the lamp sprite.

//lampLoop():
//
//Reinicializa e aplica velocidade ao sprite do poste.

int lampLoop(SDL_Point &lamp, Road road, Screen screen){
    if(lamp.x < -800){
        return screen.w + 800;
    }
    return lamp.x - toi(road.speed.x * screen.wScale);
}


///drawCursor():
///
///Draws the cursor.

//drawCursor():
//
//Desenha o cursor.

void drawCursor(SDL_Renderer *render, SDL_Point mouse, SDL_Texture *cursor){
    SDL_Rect cursorPos = {mouse.x - 15, mouse.y - 15, 30, 30};
    SDL_RenderCopy(render, cursor, nullptr, &cursorPos);
}


///drawCarSkin():
///
///Selects and draws the sprite for the NPC cars, between otherCars.png, otherCars2.png, otherCars3.png, otherCars4.png, and otherCars5.png.

//drawCarSkin():
//
//Seleciona e desenha o sprite dos carros NPC entre otherCars.png, otherCars2.png, otherCars3.png, otherCars4.png, e otherCars5.png.

void drawNPCCarSkin(SDL_Renderer* render, Img img, NPCCar npcCar[2]){
    for(int i = 0; i < 2; i++){
        if(npcCar[i].skin < 5){
            npcCar[i].cut = {0, npcCar[i].skin * 212, 444, 212};
            SDL_RenderCopy(render, img.npcCarSprite, &npcCar[i].cut, &npcCar[i].pos);
        } else if(npcCar[i].skin >= 5 && npcCar[i].skin < 7){
            npcCar[i].cut = {0, (npcCar[i].skin - 5) * 204, 452, 204};
            SDL_RenderCopy(render, img.npcCarSprite2, &npcCar[i].cut, &npcCar[i].pos);
        } else if(npcCar[i].skin >= 7 && npcCar[i].skin < 9){
            npcCar[i].cut = {0, (npcCar[i].skin - 7) * 216, 456, 216};
            SDL_RenderCopy(render, img.npcCarSprite3, &npcCar[i].cut, &npcCar[i].pos);
        } else if(npcCar[i].skin >= 9 && npcCar[i].skin < 12){
            npcCar[i].cut = {0, (npcCar[i].skin - 9) * 220, 448, 220};
            SDL_RenderCopy(render, img.npcCarSprite4, &npcCar[i].cut, &npcCar[i].pos);
        } else if(npcCar[i].skin >= 12 && npcCar[i].skin < 15){
            npcCar[i].cut = {0, (npcCar[i].skin - 12) * 204, 448, 204};
            SDL_RenderCopy(render, img.npcCarSprite5, &npcCar[i].cut, &npcCar[i].pos);
        }
    }
}


///drawSprites():
///
///Draws the road, the player's car and the NPC cars.

//drawSprites():
//
//Desenha a estrada, o carro do jogador e os carros NPC.

void drawSprites(SDL_Renderer *render, Road road, Car &car, NPCCar npcCar[2], Img img, Screen screen, bool night, Rain rain){
    ///Draws road:
    //Desenha a estrada:
    road.cut = {road.x, 0, screen.w, 600};
    road.pos = {0, 0, screen.w, screen.h};
    if(rain.active){
        if(rain.puddleCount){
            SDL_RenderCopy(render, img.bgRoad, &road.cut, &road.pos);
        } else {
            SDL_RenderCopy(render, img.bgRoadRain, &road.cut, &road.pos);
        }
    } else {
        if(rain.puddleCount){
            SDL_RenderCopy(render, img.bgRoadRain, &road.cut, &road.pos);
        } else {
            SDL_RenderCopy(render, img.bgRoad, &road.cut, &road.pos);
        }
    }
    if(car.health > 0){
        drawNPCCarSkin(render, img, npcCar);
    }

    ///Draws car:
    //Desenha o carro:
    car.cut = {0, (3 - car.health)*212, 444, 212};
    SDL_SetTextureAlphaMod(img.headLights, (road.x % 90) + 195);
    if(car.health > 0){
        SDL_RenderCopyEx(render, img.carSprite, &car.cut, &car.pos, car.angle.value, nullptr, SDL_FLIP_NONE);
        if(night){
            SDL_Point headlightsPoint = {toi(120 * screen.hScale), toi((211/2) * screen.hScale)};
            SDL_Rect headlightsPos = {car.x - 150, toi(car.y - 82 * screen.hScale), toi(1212/2 * screen.hScale), toi((422/2) * screen.hScale)};
            SDL_RenderCopyEx(render, img.headLights, nullptr, &headlightsPos, car.angle.value, &headlightsPoint, SDL_FLIP_NONE);
        }
    } else {
        carCrash(car, car.health, screen);
        car.pos = {car.x - 61, car.y - 50, toi((444/2.5)*screen.hScale), toi((212/2.5)*(screen.hScale))};
        car.cut = {0, 424, 444, 212};
        SDL_RenderCopyEx(render, img.carSprite, &car.cut, &car.pos, car.angle.value, nullptr, SDL_FLIP_NONE);
    }
    if(night && car.health > 0){
        for(int i = 0; i < 2; i++){
            SDL_Rect headlightsPos = {npcCar[i].x - 50, toi(npcCar[i].y - 55 * screen.hScale), toi(1212/2 * screen.hScale), toi((422/2) * screen.hScale)};
            SDL_RenderCopy(render, img.headLights, nullptr, &headlightsPos);
        }
    }
}


///explodeAnimation():
///
///Draws the explosion animation.

//explodeAnimation():
//
//Desenha a animação da explosão;

void explodeAnimation(SDL_Renderer *render, Img img, Animation &explosion, Screen screen){
    ///Sets the sprite position and applies the speed:
    //Define a posição do sprite e aplica a velocidade:
    explosion.spritePos = {explosion.x, explosion.y, toi((201/1.5) * screen.hScale), toi((177/1.5) * screen.hScale)};
    explosion.x -= explosion.speed.x;
    explosion.speed.x /= 1.05;

    ///Changes the sprite every five frames:
    //Muda o sprite a cada cinco quadros:
    switch(explosion.counter){
        case 0:
            explosion.spriteCut.x = 0;
        break;
        case 5:
            explosion.spriteCut.x = 201;
        break;
        case 10:
            explosion.spriteCut.x = 402;
        break;
        case 15:
            explosion.spriteCut.x = 603;
        break;
        case 20:
            explosion.spriteCut.x = 804;
        break;
        case 25:
            explosion.spriteCut.x = 1005;
        break;
        case 30:
            explosion.spriteCut.x = 1206;
        break;
        case 35:
            explosion.counter = -1;
            explosion.active = false;
        break;
    }
    explosion.counter++;
    SDL_RenderCopy(render, img.explosion, &explosion.spriteCut, &explosion.spritePos);
}

void toggleNight(Night &night, int score){
    if(score % 160 >= 80 && night.threshold < 135){
        night.threshold++;
    } else if (score % 160 < 80 && night.threshold > 0){
        night.threshold--;
    }
    if(night.threshold == 135){
        night.active = true;
    } else if(night.threshold == 0){
        night.active = false;
    }
}

void toggleRain(SDL_Renderer* render, Rain &rain, SDL_Texture* sprite, int score){
    if(score == rain.start && rain.active == false){
        rain.active = true;
        rain.puddleCount = 500;
    }
    if(rain.active){
        if(score >= rain.start && score < rain.start + 40){
            rain.count++;
            if(rain.count % 5 == 0){
                rain.cut.y += (rand() % 6 + 1) * 600;
                rain.cut.y = rain.cut.y % 4200;
            }
            SDL_RenderCopy(render, sprite, &rain.cut, nullptr);
        } else {
            rain.start = score + 40 + (rand() % 30);
            rain.active = false;
            rain.puddleCount = 500;
        }
    }
    if(rain.puddleCount > 0){
        rain.puddleCount--;
    }
}

///initImg():
///
///Initializes the textures.

//initImg():
//
//Inicializa as texturas.

Img initImg(SDL_Renderer* render){
    Img img;
    img.carSprite = IMG_LoadTexture(render, "img/car.png");
    img.carPieces = IMG_LoadTexture(render, "img/carPieces.png");
    img.carHoodSprite = IMG_LoadTexture(render, "img/carHood.png");
    img.headLights = IMG_LoadTexture(render, "img/headLights.png");
    img.bgRoad = IMG_LoadTexture(render, "img/road.png");
    img.bgRoadRain = IMG_LoadTexture(render, "img/rainRoad.png");
    img.npcCarSprite = IMG_LoadTexture(render, "img/otherCars.png");
    img.npcCarSprite2 = IMG_LoadTexture(render, "img/otherCars2.png");
    img.npcCarSprite3 = IMG_LoadTexture(render, "img/otherCars3.png");
    img.npcCarSprite4 = IMG_LoadTexture(render, "img/otherCars4.png");
    img.npcCarSprite5 = IMG_LoadTexture(render, "img/otherCars5.png");
    img.explosion = IMG_LoadTexture(render, "img/explosion.png");
    img.font = IMG_LoadTexture(render, "img/font.png");
    img.cursor = IMG_LoadTexture(render, "img/cursor.png");
    img.lampSpriteOn = IMG_LoadTexture(render, "img/lampOn.png");
    img.lampSpriteOff = IMG_LoadTexture(render, "img/lampOff.png");
    img.rainSprite = IMG_LoadTexture(render, "img/rain.png");
    img.truckSprite = IMG_LoadTexture(render, "img/truck.png");
    img.crateSprite = IMG_LoadTexture(render, "img/crate.png");
    return img;
}


///destroy():
///
///Deletes the window, renderer and textures.

//destroy():
//
//Deleta a janela, o renderizador e as texturas.

void destroy(SDL_Window* mainWindow, SDL_Renderer* render, Img &img){
    SDL_DestroyTexture(img.carSprite);
    SDL_DestroyTexture(img.bgRoad);
    SDL_DestroyTexture(img.bgRoadRain);
    SDL_DestroyTexture(img.npcCarSprite);
    SDL_DestroyTexture(img.npcCarSprite2);
    SDL_DestroyTexture(img.npcCarSprite3);
    SDL_DestroyTexture(img.npcCarSprite4);
    SDL_DestroyTexture(img.npcCarSprite5);
    SDL_DestroyTexture(img.explosion);
    SDL_DestroyTexture(img.carPieces);
    SDL_DestroyTexture(img.carHoodSprite);
    SDL_DestroyTexture(img.headLights);
    SDL_DestroyTexture(img.font);
    SDL_DestroyTexture(img.cursor);
    SDL_DestroyTexture(img.lampSpriteOn);
    SDL_DestroyTexture(img.lampSpriteOff);
    SDL_DestroyTexture(img.rainSprite);
    SDL_DestroyTexture(img.truckSprite);
    SDL_DestroyTexture(img.crateSprite);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(mainWindow);
}
