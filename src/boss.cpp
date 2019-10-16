#include <SDL.h>
#include "structs.h"
#include "toi.h"
#include "controls.h"

void truckBehavior(SDL_Renderer* render, Boss &truck, Img img, Car &car, Screen screen, int &score){
    ///Defines the initial variables:
    //Define as variáveis iniciais:
    if(truck.defineVars){
        truck.x = toi(screen.w + 100 * screen.hScale);
        truck.y = toi((screen.h/2) - 100 * screen.hScale);
        truck.speed.x = 25;
        truck.speed.y = ((rand() % 3) + 2) * screen.hScale;
        truck.crate.x = -100;
        truck.endCounter = 600;
        truck.attacks = false;
        truck.defineVars = false;
    }
    ///Truck's begginning animation:
    //Animação inicial do caminhão:
    if(truck.speed.x > 0 && truck.endCounter > 0 && truck.endCounter < 2800 && car.health > 0){
        truck.speed.x -= 1;
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
    //Loop dos barris:
    if(truck.crate.x > -200){
        truck.crate.x -= toi(30 * screen.hScale);
    } else if (truck.attacks && car.health > 0){
        truck.crate.x = truck.x;
        truck.crate.y = toi(truck.y + 30 * screen.hScale);
    }

    ///Game over truck animation:
    //Animação do caminhão no game over:
    if(car.health < 1 && truck.endCounter > 0){
        truck.speed.x++;
        truck.x += truck.speed.x;
        truck.attacks = false;
    }
    SDL_Rect cratePos = {truck.crate.x, truck.crate.y, toi(80 * screen.hScale), toi(80 * screen.hScale)};
    if(collide(car.pos, cratePos)){
        car.health--;
        truck.crate.x = truck.x;
        truck.crate.y = truck.y + 30;
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
