//////========----------------CARS: THE MOVIE: THE GAME----------------========//////
///                            09/09/2019 - XX/XX/2019                            ///
///                             COPYRIGHT DAVI MELLO                              ///
//////========---------------------------------------------------------========//////

///These will be the EN-US comments
//Esses serão os comentários em PT-BR


#define SDL_MAIN_HANDLED
#include <iostream>
#include <random>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>
#include <fstream>
#include <windows.h>
#include "structs.h"
#include "animations.h"
#include "boss.h"
#include "controls.h"
#include "text.h"
#include "menu.h"
#include "highscore.h"
#include "toi.h"
#include "resolution.h"
using namespace std;

int main(){
    ///Hides console window:
    //Esconde a janela do console:
    //HWND windowHandle = GetConsoleWindow();
    //ShowWindow(windowHandle, SW_HIDE);
    //==========================INIT==========================//
    cout << "nice";
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    SDL_Window *mainWindow = SDL_CreateWindow("Cars: The Movie: The Game", 20, 20, 800, 600, 0);

    ///SDL_SetWindowDisplayMode() to set the window's display mode to default to prevent refresh rate issues.
    //SDL_SetWindowDisplayMode() para definir o modo de display da janela, para previnir problemas com o taxa de atualização do monitor.
    SDL_SetWindowDisplayMode(mainWindow, nullptr);
    SDL_Renderer *render = SDL_CreateRenderer(mainWindow, -1, 0);// SDL_RENDERER_ACCELERATED);

    ///Defining the seed to the random ints using the current time.
    //Define a semente dos números aleatórios usando o horário atual.
    srand(static_cast<unsigned int>(time(nullptr)));

    //==========================VARIABLES==========================//
    Screen screen = {800, 600, 0, 0, false};

    ///loadResolution() and loadFull() are defined in resolution.cpp, open it for more info about the functions.
    //loadResolution() e loadFull() são definidos no arquivo "resolution.cpp", acesse-o para mais informações sobre as funções.
    loadResolution(screen, mainWindow);
    loadFull(screen, mainWindow);
    ///The vars are all defined here. Some will be initialized, when the player clicks "start", in the restart() function.
    //As variáveis são todas definidas aqui. Algumas serão inicializadas, quando o jogador clica "start", na função restart().
    Road road;
    Car car;
    Boss truck;
    SDL_Point mouse, lamp;
    NPCCar npcCar[2];
    CarPiece carHood;
    CarPiece pieces[3];
    Menu menu = {0, 1, {0, 5}, false};
    Animation explosion;
    Rain rain;
    Night night;
    Debug debug = {false, 0, true};

    ///CARSTATE: > 3 means the player hasn't lost yet. < 0 means the game is over.
    //CARSTATE: > 3 significa que o jogador ainda não perdeu. < 0 significa que o jogo acabou.
    int score = 0, highscore;
    bool end = false, restart = false;

    //==========================TEXTURES==========================//
    ///initImg() is defined in animations.cpp, open it for more info about the function.
    //initImg() é definida no arquivo "animations.cpp", acesse-o para mais informações sobre a função.
    Img img = initImg(render);

    SDL_SetTextureBlendMode(img.lampSpriteOn, SDL_BLENDMODE_ADD);
    SDL_SetTextureBlendMode(img.headLights, SDL_BLENDMODE_ADD);

    //==========================SET=HIGHSCORE==========================//
    ///getHighscore() is defined in highscore.cpp, open it for more info about the function.
    //getHighscore() é definida no arquivo "highscore.cpp", acesse-o para mais informações sobre a função.
    highscore = getHighscore();

    //========================================================GAME-LOOP========================================================//
    while (!end){
        SDL_ShowCursor(SDL_DISABLE);
        //-----EVENT-----//
        ///eventCheck() is defined in controls.cpp, open it for more info about the function.
        //eventCheck() é definida no arquivo "controls.cpp", acesse-o para mais informações sobre a função.
        eventCheck(mainWindow, end, restart, highscore, car.health, menu, mouse, screen, debug, rain, night, score);

        //==========================RESOLUTION==========================//
        ///Updates the screen size values every frame because the window is resizeable by dragging.
        //Atualiza os valores das dimensões da tela a cada quadro porque a janela é redimensionável com o mouse.
        SDL_GetWindowSize(mainWindow, &screen.w, &screen.h);

        ///Sets the proportion of the window, for sprite size calculations.
        //Define a taxa de proporção da janela para os cálculos dos sprites.
        screen.wScale = screen.w/800.0;
        screen.hScale = screen.h/600.0;

        //==========================MOUSE==========================//
        ///Gets the mouse position.
        //Pega a posição do mouse.
        mouse = getMouseXY(mouse);

        //==========================DEBUG=MODE==========================//
        if(!debug.active && debug.passwordCounter == 4){
            debug.active = true;
        }
        ///===============================THIS PART RUNS AFTER THE PLAYER HITS START===============================///
        //===========================ESSA PARTE É EXECUTADA APÓS O JOGADOR CLICAR "START"===========================//
        if(menu.state == 0){
            //-----CLEAR-----//
            ///Clears the screen before drawing.
            //Limpa a tela antes de desenhar.
            SDL_RenderClear(render);

            //==========================RESTART==========================//
            ///restartVars() is defined in controls.cpp, open it for more info about the function.
            //restartVars() é definida no arquivo "controls.cpp", acesse-o para mais informações sobre a função.
            restartVars(restart, car.health, road, npcCar, carHood, pieces, score, lamp, night, rain, truck);

            //==========================HIGHSCORE==========================//
            ///Checks if the player has beat the highscore when the game is lost.
            //Checa se o jogador bateu o recorde quando ele perde.
            if(car.health == 0 && score > highscore){
                highscore = setHighscore(score);
            }

            //==========================CONTROLS==========================//

            ///Lets the player controls the car if he hasn't lost the game.
            //Permite que o jogador controle o carro se ele ainda não perdeu.
            if(car.health > 0){
                ///carControl() is defined in controls.cpp, open it for more info about the function.
                //carControl() é definida no arquivo "controls.cpp", acesse-o para mais informações sobre a função.
                carControl(car, mouse, screen, rain);
            }

            //==========================RECTS==========================//
            ///Defining the position and size of the player's car and the NPC cars.
            //Define a posição e o tamanho do carro do jogador e os carros dos NPCs.
            car.pos = {car.x - 100, car.y - 25, toi((444/2.5)*screen.hScale), toi((212/2.5)*(screen.hScale))};
            for(int i = 0; i < 2; i++){
                npcCar[i].pos = {npcCar[i].x, npcCar[i].y, toi((444/2.5)*screen.hScale), toi((212/2.5)*(screen.hScale))};
            }

            //==========================DRAWING==========================//
            ///drawSprites() is defined in animations.cpp, open it for more info about the function.
            //drawSprites() é definida no arquivo "animations.cpp", acesse-o para mais informações sobre a função.
            drawSprites(render, road, car, npcCar, img, screen, night.active, rain);

            //==========================CAR=PIECES=ANIMATIONS==========================//
            ///drawAnimation() is defined in animations.cpp, open it for more info about the function.
            //drawAnimation() é definida no arquivo "animations.cpp", acesse-o para mais informações sobre a função.
            drawAnimation(render, pieces, car, carHood, img, screen);

            //==========================ROADLOOP==========================//
            ///roadLoop() is defined in animations.cpp, open it for more info about the function.
            //roadLoop() é definida no arquivo "animations.cpp", acesse-o para mais informações sobre a função.
            road.x = roadLoop(road, car.health, screen);

            //==========================EXPLOSION==========================//
            ///explodeAnimation() is defined in animations.cpp, open it for more info about the function.
            //explodeAnimation() é definida no arquivo "animations.cpp", acesse-o para mais informações sobre a função.
            if(explosion.active){
                explodeAnimation(render, img, explosion, screen);
            }
            //==========================NPCCAR=LOOP==========================//
            ///Moves the NPC cars across the screen.
            //Move os carros dos NPCs na tela.
            if(car.health > 0 && debug.NPCCars){
                ///NPCCarLoop() is defined in animations.cpp, open it for more info about the function.
                //NPCCarLoop() é definida no arquivo "animations.cpp", acesse-o para mais informações sobre a função.
                NPCCarLoop(npcCar, score, screen, car, truck.active);
            } else {
                npcCar[0].x = screen.w + 400;
                npcCar[1].x = screen.w + 100;
            }

            //==========================TRUCK==========================//
            if(truck.active){
                ///truckBehavior() is defined in boss.cpp, open it for more info about the function.
                //truckBehavior() é definida no arquivo "boss.cpp", acesse-o para mais informações sobre a função.
                truckBehavior(render, truck, img, car, screen, score);
            }

            ///Truck trigger:
            //Ativador do caminhão:
            if((score != 0) && (score % 100 == 0) && (!truck.active)){
                truck.active = true;
                truck.defineVars = true;
            }

            //============================NIGHT===========================
            SDL_SetRenderDrawColor(render, 0, 0, 0, static_cast<Uint8>(night.threshold));
            SDL_RenderFillRect(render, nullptr);
            if(!debug.active){
                toggleNight(night, score);
            }
            //==========================LAMP=LOOP==========================//
            ///lampLoop() is defined in animations.cpp, open it for more info about the function.
            //lampLoop() é definida no arquivo "animations.cpp", acesse-o para mais informações sobre a função.
            lamp.x = lampLoop(lamp, road, screen);

            ///Defines the position and the size of the lamp sprite, and draws it on the screen.
            //Define a posição e o tamanho do sprite do poste, e o desenha na tela.
            SDL_Rect lampPos = {lamp.x, 0, toi(600*screen.hScale), toi(600*screen.hScale)};
            if(night.active){
            SDL_RenderCopy(render, img.lampSpriteOn, nullptr, &lampPos);
            } else {
                SDL_RenderCopy(render, img.lampSpriteOff, nullptr, &lampPos);
            }

            //=============================RAIN==============================//
            toggleRain(render, rain, img.rainSprite, score);

            //==========================WRITE=SCORE==========================//
            ///writeText() is defined in text.cpp, open it for more info about the function.
            //writeText() é definida no arquivo "text.cpp", acesse-o para mais informações sobre a função.
            writeText(render, score, img.font, toi((screen.w / 2.0f) - 30), 30);

            ///The text showing the highscore is displayed only when the player loses or when he hasn't scored yet.
            //O texto mostrando o recorde é mostrado apenas quando o jogador perde ou quando ele ainda não pontuou.
            if(car.health < 1 || score == 0){
                string scoreText = "Highscore: " + to_string(highscore);
                writeText(render, scoreText, img.font, screen.w / 2 - 90, 100, 14, 24);
            }

            //==========================ANTI=STAND-STILL=COUNTER==========================//
            ///This part counts the amount of frames that the player stays still in relation to the y-axis and reset when he moves. Is used in NPCCarLoop().
            //Esta parte conta a quantidade de quadros que o jogador fica parado em relação ao eixo y e retorna a 0 quando ele move. É usado em NPCCarLoop().
            if((mouse.y > car.y - 20 && mouse.y < car.y + 20) || car.y == toi(70*screen.hScale) || car.y == toi(screen.h - 90*screen.hScale)){
                car.moveCounter++;
            } else {
                car.moveCounter = 0;
            }
            //==========================HITBOXES==========================//

            changeHitbox(mouse, car, npcCar);
            ///carCollision() is defined in controls.cpp, open it for more info about the function.
            //carCollision() é definida no arquivo "controls.cpp", acesse-o para mais informações sobre a função.
            carCollision(car, npcCar, screen, explosion);

            ///Enable these lines to show the hitboxes.
            //Ative estas linhas para mostrar as hitboxes.
            /*SDL_SetRenderDrawColor(render, 255, 0, 0, 128);
            SDL_RenderFillRect(render, &car.pos);
            for(int i = 0; i < 2; i++){
                SDL_RenderFillRect(render, &npcCar[i].pos);
            }*/

        //=========================================================MENU==============================================//
        ///===============================THIS PART RUNS BEFORE THE PLAYER HITS START===============================///
        //===========================ESSA PARTE É EXECUTADA ANTES DO JOGADOR CLICAR "START"==========================//
        } else if(menu.state > 0){
            ///drawMenu() is defined in menu.cpp, open it for more info about the function.
            //drawMenu() é definida no arquivo "menu.cpp", acesse-o para mais informações sobre a função.
            drawMenu(render, menu, mouse, img, car, screen, highscore);
        }
        ///drawCursor() is defined in animations.cpp, open it for more info about the function.
        //drawCursor() é definida no arquivo "animations.cpp", acesse-o para mais informações sobre a função.
        drawCursor(render, mouse, img.cursor);

        ///Debug notification:
        //Notificação de debug:
        if(debug.active){
            writeText(render, "Debug Mode", img.font, 5, 5, 14, 24);
            if(menu.state == 1){
                writeText(render, "Press Z to toggle day and night;", img.font, 5, screen.h - 142, 14, 24);
                writeText(render, "Press X to toggle NPC cars;", img.font, 5, screen.h - 116, 14, 24);
                writeText(render, "Press C to toggle rain;", img.font, 5, screen.h - 87, 14, 24);
                writeText(render, "Press H to heal;", img.font, 5, screen.h - 58, 14, 24);
                writeText(render, "Press S to increase the score by 10;", img.font, 5, screen.h - 29, 14, 24);
            }
        }

        ///Displays everything that has been drawn on the screen.
        //Mostra tudo que foi desenhado na tela.
        SDL_RenderPresent(render);

        ///Framerate (60FPS)
        //Taxa de quadros (60 Quadros por Segundo)
        SDL_Delay(1000/60);
    }

    //==========================DESTROY==========================
    ///destroy() is defined in animations.cpp, open it for more info about the function.
    //destroy() é definida no arquivo "animations.cpp", acesse-o para mais informações sobre a função.
    destroy(mainWindow, render, img);

    ///Quits SDL.
    //Finaliza a SDL.
    SDL_Quit();
    return 0;
}
