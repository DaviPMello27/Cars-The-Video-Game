//////========----------------CARS: THE MOVIE: THE GAME----------------========//////
///                            09/09/2019 - 24/10/2019                            ///
///                             COPYRIGHT DAVI MELLO                              ///
//////========---------------------------------------------------------========//////

///These will be the EN-US comments
//Esses serão os comentários em PT-BR

#include <SDL.h>
#include <iostream>
#include <random>
#include "structs.h"
#include "toi.h"
#include "highscore.h"
#include "resolution.h"


///eventCheck():
///
///Determines what should happen when a button is pressed. More info inside.

//eventCheck:
//
//Determina o que acontece ao clicar em um botão. Mais informações dentro da função.

void eventCheck(SDL_Window* mainWindow, bool &end, bool &restart, int &highscore, int &carHealth, Menu &menu, SDL_Point mouse, Screen &screen, Debug &debug, Rain &rain, Night &night, int &score){
    SDL_Event gameEvent;
    while(SDL_PollEvent(&gameEvent)){
        switch(gameEvent.type){
            ///Quit when the user closes the window.
            //Finaliza o programa quando o usuário fecha a janela.
            case SDL_QUIT:
                end = true;
            break;
            ///Keys:
            //Teclas:
            case SDL_KEYDOWN:
                switch(gameEvent.key.keysym.sym){
                    case SDLK_r:
                        ///R to restart.
                        //R para recomeçar.
                        restart = true;
                    break;
                    case SDLK_ESCAPE:
                        ///ESC to return to the menu.
                        //ESC para retornar ao menu.
                        menu.state = 1;
                    break;
                    case SDLK_f:
                        ///F to toggle fullscreen mode.
                        //F para alternar o modo tela cheia.
                    if(screen.full == false){
                        SDL_SetWindowFullscreen(mainWindow, SDL_WINDOW_FULLSCREEN);
                        screen.full = true;
                    } else {
                        SDL_SetWindowFullscreen(mainWindow, 0);
                        screen.full = false;
                    }
                    break;
                    ///Debug keys:
                    //Teclas de debug:
                    case SDLK_z:
                        if(debug.active){
                            if(!night.active){
                                night.threshold = 135;
                            } else {
                                night.threshold = 0;
                            }
                            if(night.threshold == 135){
                                night.active = true;
                            } else if(night.threshold == 0){
                                night.active = false;
                            }
                        }
                    break;
                    case SDLK_x:
                        if(debug.active){
                            if(!debug.NPCCars){
                                debug.NPCCars = true;
                            } else {
                                debug.NPCCars = false;
                            }
                        }
                    break;
                    case SDLK_c:
                        if(debug.active){
                            if(!rain.active){
                                rain.active = true;
                                rain.puddleCount = 500;
                                rain.start = score;
                            } else {
                                rain.start = score + 40 + (rand() % 30);
                                rain.active = false;
                                rain.puddleCount = 0;
                            }
                        }
                    break;
                    case SDLK_h:
                        if(debug.active && carHealth < 3){
                            carHealth++;
                        }
                    break;
                    case SDLK_s:
                        if(debug.active){
                            score += 10;
                        }
                    break;
                    ///Debug password keys:
                    //Teclas da senha de debug:
                    case SDLK_d:
                        if(!debug.active && debug.passwordCounter == 0){
                            debug.passwordCounter++;
                        } else {
                            debug.passwordCounter = 0;
                        }
                    break;
                    case SDLK_a:
                        if(!debug.active && debug.passwordCounter == 1){
                            debug.passwordCounter++;
                        } else {
                            debug.passwordCounter = 0;
                        }
                    break;
                    case SDLK_v:
                        if(!debug.active && debug.passwordCounter == 2){
                            debug.passwordCounter++;
                        } else {
                            debug.passwordCounter = 0;
                        }
                    break;
                    case SDLK_i:
                        if(!debug.active && debug.passwordCounter == 3){
                            debug.passwordCounter++;
                        } else {
                            debug.passwordCounter = 0;
                        }
                    break;
                    default:
                    if(!debug.active){
                        debug.passwordCounter = 0;
                    }
                    break;
                }
            break;
            ///Mouseclick:
            //Clique do mouse:
            case SDL_MOUSEBUTTONDOWN:
                switch(gameEvent.button.button){
                    case SDL_BUTTON_LEFT:
                    SDL_Rect test;
                    ///======================THIS PART RUNS IN THE MAIN MENU======================///
                    //====================ESTA PARTE É EXECUTADA NO MENU INICIAL===================//
                    if(menu.state == 1){
                        ///START button:
                        //Botão START:
                        test = {(screen.w / 2) - 150, (200 - menu.y), 300, 100};
                        if(SDL_PointInRect(&mouse, &test)){
                                restart = true;
                                menu.animate = true;
                        }
                        ///OPTIONS button:
                        //Botão OPTIONS:
                        test = {(screen.w / 2) - 100, (350 - menu.y), 200, 75};
                        if(SDL_PointInRect(&mouse, &test)){
                                menu.state = 2;
                        }
                        ///QUIT button:
                        //Botão QUIT:
                        test = {(screen.w / 2) - 100, (475 - menu.y), 200, 75};
                        if(SDL_PointInRect(&mouse, &test)){
                                end = true;
                        }
                        ///======================THIS PART RUNS IN THE OPTIONS MENU======================///
                        //====================ESTA PARTE É EXECUTADA NO MENU DE OPÇÕES====================//
                    } else if (menu.state == 2){
                        ///This loops checks every button in the resolutions part.
                        //Este loop checa cada botão da parte das resoluções.
                        for(int i = 0; i < 13; i++){
                            if(i < 6){
                                ///First column:
                                //Primeira coluna:
                                test = {(screen.w/2 - 270), (screen.h/2 - 110) + i*56, 150, 50};
                            } else {
                                ///Second column:
                                //Segunda coluna:
                                test = {(screen.w/2 - 60), (screen.h/2 - 166) + (i - 6)*56, 150, 50};
                            }
                            ///Changes the resolution and save it.
                            //Muda a resolução e salva.
                            if(SDL_PointInRect(&mouse, &test)){
                                screen.w = stoi(res[0][i]);
                                screen.h = stoi(res[1][i]);
                                SDL_SetWindowSize(mainWindow, screen.w, screen.h);
                                saveResolution(screen, i);
                                break;
                            }
                        }
                        /// < BACK button:
                        // Botão < BACK:
                        test = {25, (screen.h - 60), 150, 50};
                        if(SDL_PointInRect(&mouse, &test)){
                            menu.state = 1;
                        }
                        ///"Toggle Fullscreen" button:
                        //Botão "Toggle fullscreen":
                        test = {screen.w/2 + 170, (screen.h/2 - 170) + 150, 50, 50};
                        if(SDL_PointInRect(&mouse, &test)){
                            if(screen.full == false){
                                SDL_SetWindowFullscreen(mainWindow, SDL_WINDOW_FULLSCREEN);
                                screen.full = true;
                            } else {
                                SDL_SetWindowFullscreen(mainWindow, 0);
                                screen.full = false;
                            }
                            saveFull(screen);
                        }
                        ///"Reset highscore" button:
                        //Botão "Reset highscore":
                        test = {screen.w/2 + 170, (screen.h/2 - 70) + 150, 50, 50};
                        if(SDL_PointInRect(&mouse, &test)){
                            highscore = setHighscore(0);
                        }
                    }
                    ///=======================THIS PART RUNS DURING GAMEPLAY======================///
                    //====================ESTA PARTE É EXECUTADA DURANTE O JOGO====================//
                    ///Click to restart:
                    //Clicar para recomeçar:
                    if(menu.state == 0 && carHealth < 1){
                        restart = true;
                    }
                    break;
                }
            break;
        }
    }
}


///restartVars():
///
///Resets all the variables for a new game session.

//restartVars():
//
//Reinicializa as variáveis para uma nova sessão de jogo.

void restartVars(bool &restart, int &carHealth, Road &road, NPCCar (&npcCar)[2], CarPiece &carHood, CarPiece (&pieces)[3], int &score, SDL_Point &lamp, Night &night, Rain &rain, Boss &truck, Boss &plane, PowerUp &powerUp){
    if(restart == true){
        carHealth = 3;
        npcCar[0] = {3000, rand() % 410 + 50, rand() % 15, {20, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
        npcCar[1] = {4000, rand() % 410 + 50, rand() % 15, {20, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
        carHood = {0, 0, {0, 0}, {0, 0}, false, {0, 0, 0, 0}, {0, 0, 0, 0}};
        pieces[0] = {0, 0, {0, 0}, {0, 0}, false, {0, 0, 0, 0}, {0, 0, 0, 0}};
        pieces[1] = {0, 0, {0, 0}, {0, 0}, false, {0, 0, 0, 0}, {0, 0, 0, 0}};
        pieces[2] = {0, 0, {0, 0}, {0, 0}, false, {0, 0, 0, 0}, {0, 0, 0, 0}};
        score = 0;
        road = {0, {30, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
        lamp = {800, 0};
        restart = false;
        night = {0, false};
        rain = {0, 40 + (rand() % 30), 0, false, {0, 0, 1000, 600}};
        truck = {0, 0, {0, 0}, false, false, false, 0, {0, 0}, {0, 0, 197, 70}, {0, 0, 197/2, 70/2}};
        plane = {0, 0, {0, 0}, false, false, false, 0, {0, 0}, {0, 0, 657, 591}, {0, 0, toi(657*1.5), toi(591*1.5)}};
        powerUp = {0, 0, ((rand() % 20) + 30), false, {0, 0, 0, 0}};
    }
}


///getMouseXY():
///
///Gets the mouse coordinates.

//getMouseXY():
//
//Pega as coordenadas do mouse.

SDL_Point getMouseXY(SDL_Point mouse){
    SDL_GetMouseState(&mouse.x, &mouse.y);
    return {mouse.x, mouse.y};
}


///carControl():
///
///Moves the car with the mouse.

//carControl():
//
//Move o carro com o mouse.

void carControl(Car &car, SDL_Point mouse, Screen screen, Rain &rain){
    if(!rain.active ^ (rain.puddleCount > 0)){
        ///Delays the car's movement.
        //Atrasa o movemento do carro.
        double newMouseY = mouse.y - 20 * screen.hScale;
        double newMouseX = mouse.x - 20 * screen.hScale;
        car.y += ((newMouseY - car.y)/10);
        car.x += ((newMouseX - car.x)/10);
        ///Sets the angles for the curves.
        //Muda o ângulo do carro nas curvas.
        car.angle.value = (newMouseY - car.y)/5;
    } else {
        ///Delays the car's movement.
        //Atrasa o movemento do carro.
        double newMouseY = mouse.y - 20 * screen.hScale;
        double newMouseX = mouse.x - 20 * screen.hScale;
        if(abs(newMouseY - car.y) > 200 * screen.hScale){
            car.drift.counter = 15;
        }
        if(car.drift.counter > 0){
            car.drift.counter--;
        }
        if (car.drift.counter == 0) {
            newMouseY = mouse.y - 20 * screen.hScale;
            car.y += ((newMouseY - car.y)/10);
            car.drift.factor = 0;
        } else {
            car.drift.factor += ((newMouseY - car.y)/200);
            car.y += car.drift.factor;
        }
        car.x += ((newMouseX - car.x)/10);
        ///Sets the angles for the curves.
        //Muda o ângulo do carro nas curvas.
        car.angle.value = ((mouse.y - 20 * screen.hScale) - car.y)/5;
    }
    ///Limits the cars movement in the y-axis.
    //Limita o movimento do carro no eixo y.
    if(car.y < toi(70*screen.hScale)){
        car.y = toi(70*screen.hScale);
    } else if (car.y > toi(screen.h - 90*screen.hScale)){
        car.y = toi(screen.h - 90*screen.hScale);
    }
}


///collide():
///
///Checks if two rects intersect.

//collide():
//
//Checa se dois retângulos se interseccionam.

bool collide(SDL_Rect first, SDL_Rect second){
    if(first.x + first.w > second.x && first.x < second.x + second.w && first.y < second.y + second.h && first.y + first.h > second.y){
        return true;
    }
    return false;
}


///carCollision():
///
///Defines what happens when two cars collide.

//carCollision():
//
//Define o que acontece quando dois carros colidem.

bool carCollision(Car &car, NPCCar (&npcCar)[2], Screen screen, Animation &explosion){
    for(int i = 0; i < 2; i++){
        ///Decreases carHealth and resets the NPCCar position.
        //Diminui o carHealth e reinicializa a posição do carro NPC.
        if(collide(car.pos, npcCar[i].pos)){
            car.health--;
            npcCar[i].x = screen.w + 500;
            npcCar[i].speed.x = rand() % 10 + 10;
            if(car.moveCounter > 150){
                npcCar[i].y = car.y - toi(20*screen.hScale);
            } else {
                npcCar[i].y = rand() % (screen.h-100) + 50;
            }
            explosion.x = car.x;// + toi(10*screen.hScale);
            explosion.y = car.y + toi(car.angle.value * screen.hScale);
            explosion.speed.x = rand() % 5;
            explosion.counter = 0;
            explosion.spriteCut = {0, 0, 43, 38};
            explosion.active = true;
            return true;
        }
    }
    return false;
}

///changeHitbox():
///
///Adapts the cars' hitbox to the sprites.

//changeHitbox():
//
//Adapta a hitbox dos carros aos sprites.

void changeHitbox(SDL_Point mouse, Car &car, NPCCar (&npcCar)[2]){
    ///Decreases the player's car's hitbox's width based on the angle, to adapt to the sprite.
    //Diminui a largura da hitbox do carro do jogador baseado no ângulo, para adaptar ao sprite.
    car.pos.w -= abs(((mouse.y - car.y)/3));
    car.pos.x += abs(((mouse.y - car.y)/5));
    car.pos.y += ((mouse.y - car.y)/10);
    car.pos.h -= 5;

    ///Shrinks the NPC cars' hitboxes:
    //Diminui a hitbox dos carros NPC:
    for(int i = 0; i < 2; i++){
        npcCar[i].pos.h -= 10;
        npcCar[i].pos.w -= 10;
        npcCar[i].pos.x += 5;
        npcCar[i].pos.y += 5;
    }
}
