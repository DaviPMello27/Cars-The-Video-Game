//////========----------------CARS: THE MOVIE: THE GAME----------------========//////
///                            09/09/2019 - 22/10/2019                            ///
///                             COPYRIGHT DAVI MELLO                              ///
//////========---------------------------------------------------------========//////

///1973 lines

///These will be the EN-US comments
//Esses serão os comentários em PT-BR


#include <SDL.h>
#include "structs.h"
#include "toi.h"
#include "controls.h"
#include "animations.h"



void truckBehavior(SDL_Renderer* render, Boss &truck, Img img, Car &car, Screen screen, int &score){
    ///Defines the initial variables:
    //Define as variáveis iniciais:
    if(truck.defineVars){
        truck.x = toi(screen.w + 100 * screen.hScale);
        truck.y = toi((screen.h/2) - 100 * screen.hScale);
        truck.speed.x = 25;
        truck.speed.y = ((rand() % 3) + 2) * screen.hScale;
        truck.projectile.x = -100;
        ///Truck will be active for 50 seconds:
        //O caminhão estará ativo por 50 segundos:
        truck.endCounter = 3000;
        truck.attacks = false;
        truck.defineVars = false;
    }
    ///Truck's begginning animation:
    //Animação inicial do caminhão:
    if(truck.speed.x > 0 && truck.endCounter > 0 && truck.endCounter < 2800 && car.health > 0){
        truck.speed.x--;
        truck.x -= truck.speed.x;

    ///Back-and-forth behavior:
    //Comportamento vai-e-volta:
    } else if (truck.endCounter > 30 && truck.endCounter < 2800){
        truck.attacks = true;
        if(truck.y < 70){
            if(truck.endCounter > 100){
                truck.speed.y = ((rand() % 3) + 3) * screen.hScale;
            } else {
                truck.speed.y = ((rand() % 3) + 6) * screen.hScale;
            }
        } else if (truck.y > (screen.h - 100)){
            if(truck.endCounter > 100){
                truck.speed.y = 0 - (((rand() % 3) + 3) * screen.hScale);
            } else {
                truck.speed.y = 0 - ((rand() % 3) + 6) * screen.hScale;
            }
        }
        truck.y += truck.speed.y;
    }

    ///crate loop:
    //Loop das caixas:
    if(truck.projectile.x > -200){
        truck.projectile.x -= toi(30 * screen.hScale);
    } else if (truck.attacks && car.health > 0){
        truck.projectile.x = truck.x;
        truck.projectile.y = toi(truck.y + 30 * screen.hScale);
    }

    ///Game over truck animation:
    //Animação do caminhão no game over:
    if(car.health < 1 && truck.endCounter > 0){
        truck.speed.x++;
        truck.x += truck.speed.x;
        truck.attacks = false;
    }
    SDL_Rect cratePos = {truck.projectile.x, truck.projectile.y, toi(80 * screen.hScale), toi(80 * screen.hScale)};
    if(collide(car.pos, cratePos)){
        car.health--;
        truck.projectile.x = truck.x;
        truck.projectile.y = truck.y + 30;
    }

    ///Car collision with the truck:
    //Colisão do carro com o caminhão:
    if(collide(car.pos, truck.pos)){
        car.health--;
    }

    ///Decreases the counter that removes the truck:
    //Diminui o contador que remove o caminhão:
    if(truck.endCounter > 0){
        truck.endCounter--;
    }

    ///Final truck animation:
    //Animação final do caminhão:
    if(truck.endCounter == 0){
        truck.attacks = false;
        truck.speed.x++;
        truck.x -= truck.speed.x;
    }

    ///Restores the game to its normal state:
    //Restaura o jogo ao seu estado normal:
    if(truck.x < -500){
        score += 20;
        truck.active = false;
    }

    ///Draws the truck:
    //Desenha o caminhão:
    truck.pos = {truck.x, truck.y, toi((197*2.5)*screen.hScale), toi((70*2.5)*screen.hScale)};
    SDL_RenderCopy(render, img.crateSprite, nullptr, &cratePos);
    SDL_RenderCopy(render, img.truckSprite, &truck.cut, &truck.pos);
}

void planeBehavior(SDL_Renderer* render, Boss &plane, SDL_RendererFlip &planeFlip, Animation &bomb, Animation &explosion, Img img, Car &car, Screen screen, int &score){
    ///Defines the initial variables:
    //Define as variáveis iniciais:
    if(plane.active){
        if(plane.defineVars){
            plane.x = -1200;
            plane.y = toi((screen.h/2) - (plane.pos.h/2) * screen.hScale);
            plane.speed.x = 50;
            ///Plane will be active for about 36 seconds:
            //O avião estará ativo por 36 segundos, mais ou menos:
            plane.endCounter = 2200;
            plane.attacks = false;
            bomb.counter = 0;
            bomb.active = false;
            planeFlip = SDL_FLIP_NONE;
            plane.defineVars = false;
        }
    }
    ///Initial animation:
    //Animação inicial:
    if(plane.speed.x > 0 && plane.endCounter > 2100 && plane.endCounter < 2200 && car.health > 0){
        plane.speed.x--;
    } else if(plane.speed.x < 60 && plane.endCounter > 2000 && plane.endCounter <= 2100 && car.health > 0){
        plane.speed.x++;
    }
    ///Plane back-and-forth behavior:
    //Comportamento vai-e-vem do avião:
    if(plane.endCounter % 100 == 0 && plane.endCounter < 2000 && car.health > 0 && plane.endCounter > 150){
        plane.attacks = true;
        if(plane.x > 0){
            plane.y = car.y - (plane.pos.h/2);
            plane.x = screen.w;
            plane.speed.x = -40 * screen.wScale;
            planeFlip = SDL_FLIP_HORIZONTAL;
        } else {
            plane.y = car.y - (plane.pos.h/2);
            plane.x = 0 - plane.pos.w;
            plane.speed.x = 40 * screen.wScale;
            planeFlip = SDL_FLIP_NONE;
        }
    }
    ///Applies the plane's speed to its position.
    //Aplica a velocidade do avião à sua posição.
    plane.x += plane.speed.x;

    ///Defines the initial position and speed of the bombs on each attack:
    //Define a posição e velocidades iniciais das bombas a cada ataque:
    if(plane.attacks){
        if((plane.x + (plane.pos.w/2)) > car.x - 40 && (plane.x + (plane.pos.w/2)) < car.x + 40){
            bomb.x = plane.x + (plane.pos.w/2);
            bomb.y = plane.y + (plane.pos.h/2);
            bomb.spritePos = {bomb.x, bomb.y, 72, 47};
            bomb.speed.x = (5 - rand() % 10) * screen.hScale;
            ///Throws bomb down if the plane is above 25% of the screen:
            //Joga a bomba para baixo se o avião estiver acima de 25% da tela:
            if(plane.y + plane.pos.h/2 < screen.h * 0.25){
                bomb.speed.y = (rand() % 5) * screen.hScale;
            ///Throws bomb up if the plane is below 75% of the screen:
            //Joga a bomba para cima se o avião estiver abaixo de 75% da tela:
            } else if (plane.y + plane.pos.h/2 > screen.h * 0.75){
                bomb.speed.y = (0 - rand() % 5) * screen.hScale;
            } else {
                ///Else, throws it up or down:
                //Senão, joga para cima ou para baixo:
                bomb.speed.y = (5 - rand() % 10) * screen.hScale;
            }
            ///Sets the counter for the bomb animation:
            //Define o contador da animação da bomba:
            bomb.counter = 60;
        }
    }
    bomb.counter--;
    ///In the beggining the bomb's shadow increases in size and the position decreases to compensate the size growth:
    //No começo a sombra da bomba aumenta em tamanho e a posição diminui para compensar esse aumento:
    if(bomb.counter > 40){
        bomb.spritePos.h *= 1.08;
        bomb.spritePos.w *= 1.08;
        bomb.spritePos.x -= bomb.spritePos.w * 0.02;
        bomb.spritePos.y -= bomb.spritePos.h * 0.02;
        bomb.spritePos.x += bomb.speed.x;
        bomb.spritePos.y += bomb.speed.y;
        SDL_RenderCopyEx(render, img.bombShadow, nullptr, &bomb.spritePos, 0, nullptr, planeFlip);
    ///Then the bomb's positions and dimensions are prepared to start decreasing in size:
    //Então, as posições e dimensões da bomba são preparadas para começar a diminuir em tamanho:
    } else if (bomb.counter == 40){
        bomb.spritePos.x -= bomb.spritePos.w;
        bomb.spritePos.y -= bomb.spritePos.h;
        bomb.spritePos.h = 950;
        bomb.spritePos.w = 1450;
        bomb.spritePos.x += bomb.speed.x;
        bomb.spritePos.y += bomb.speed.y;
    ///Then the bomb starts increasing in size and the position increases to compensate:
    //Então a bomba começa a diminuir em tamanho e a posição aumenta para compensar:
    } else if (bomb.counter < 40 && bomb.counter > 0){
        bomb.spritePos.h /= 1.08;
        bomb.spritePos.w /= 1.08;
        bomb.spritePos.x += bomb.spritePos.w * 0.02 + 1;
        bomb.spritePos.y += bomb.spritePos.h * 0.02 + 1;
        bomb.spritePos.x += bomb.speed.x;
        bomb.spritePos.y += bomb.speed.y;
        SDL_RenderCopyEx(render, img.bomb, nullptr, &bomb.spritePos, 0, nullptr, planeFlip);
    ///When it hits the ground, the explosion's variables are prepared to execute the animation:
    //Quando atinge o chão, as variáveis da explosão são preparadas para executar a animação:
    } else if(bomb.counter == 0){
        explosion.counter = 0;
        explosion.spriteCut = {0, 0, 43, 38};
        explosion.active = true;
        explosion.x = bomb.spritePos.x - toi((201*2) * screen.hScale);
        explosion.y = bomb.spritePos.y - toi((177*2) * screen.hScale);
        explosion.spritePos = {explosion.x, explosion.y, toi((201*4) * screen.hScale), toi((177*4) * screen.hScale)};
    ///During the explosion, if the car's and the explosion's hitboxes collide, the player loses:
    //Durante a explosão se a hitbox do carro e da explosão colidirem, o jogador perde:
    } else if (bomb.counter < 0 && bomb.counter >= -36){
        if(explosion.active){
            explodeAnimation(render, img, explosion);
            if(bomb.counter < -10 && bomb.counter >= -22){
                SDL_Rect boomHitbox = {toi(explosion.x + explosion.spritePos.w * 0.15), toi(explosion.y + explosion.spritePos.h * 0.15), toi(explosion.spritePos.w * 0.7), toi(explosion.spritePos.h * 0.7)};
                if(collide(car.pos, boomHitbox)){
                    car.health--;
                }
            }
        }
    }
    if(plane.endCounter > 0){
        plane.endCounter--;
    } else {
        score += 20;
        plane.active = false;
    }
    ///Draws the Plane:
    //Desenha o avião:
    plane.pos = {plane.x, plane.y, toi((657* 1.5) * screen.hScale), toi((591* 1.5) * screen.hScale)};
    SDL_RenderCopyEx(render, img.planeShadow, nullptr, &plane.pos, 0, nullptr, planeFlip);
}
