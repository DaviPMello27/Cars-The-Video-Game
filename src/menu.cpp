//////========----------------CARS: THE MOVIE: THE GAME----------------========//////
///                            09/09/2019 - 30/09/2019                            ///
///                             COPYRIGHT DAVI MELLO                              ///
//////========---------------------------------------------------------========//////

///These will be the EN-US comments
//Esses serão os comentários em PT-BR

#include <SDL.h>
#include <iostream>
#include "structs.h"
#include "text.h"
#include "toi.h"


///createButton():
///
///Creates a rectangle that gets brighter when the mouse is on it.

//createButton():
//
//Cria um retângulo que se torna mais claro quando o mouse está dentro.

void createButton(SDL_Renderer *render, SDL_Point &mouse, int x, int y, int w, int h){
    SDL_Rect button = {x, y, w, h};
    if(SDL_PointInRect(&mouse, &button)){
        SDL_SetRenderDrawColor(render, 255, 255, 255, 64);
    } else {
        SDL_SetRenderDrawColor(render, 255, 255, 255, 24);
    }
    SDL_RenderFillRect(render, &button);
}


///drawMenu():
///
///Draws the title and the buttons. They're centered in the x-axis.

//drawMenu():
//
//Desenha o título e os botões. São centralizados no eixo x.

void drawMenu(SDL_Renderer *render, Menu &menu, SDL_Point mouse, Img img, Car &car, int &carState, Screen screen, int highscore){
    SDL_Rect bgCut = {0, 0, 800, 600};
    SDL_RenderCopy(render, img.bgRoad, &bgCut, nullptr);
    SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(render, 0, 0, 0, 128);
    bgCut = {0, (0 - menu.y), screen.w, screen.h};
    SDL_RenderFillRect(render, &bgCut);
    if(menu.state == 1){
        writeText(render, "CARS: THE MOVIE: THE GAME", img.font, toi((screen.w / 2.0f) - 330), toi(100.0f - menu.y));
        createButton(render, mouse, toi((screen.w / 2.0f) - 150), toi(200.0f - menu.y), 300, 100);
        writeText(render, "START", img.font, toi((screen.w / 2.0f) - 100), toi(222.0f - menu.y), 44, 72);
        createButton(render, mouse, toi((screen.w / 2.0f) - 100), toi(350.0f - menu.y), 200, 75);
        writeText(render, "Options", img.font, toi((screen.w / 2.0f) - 89), toi(370.0f - menu.y));
        createButton(render, mouse, toi((screen.w / 2.0f) - 100), toi(475.0f - menu.y), 200, 75);
        writeText(render, "Quit", img.font, toi((screen.w / 2.0f) - 50), toi(495.0f - menu.y));
        if(menu.animate){
            menu.y += menu.speed.y;
            menu.speed.y *= 1.2;
            if(menu.y > 1000){
                menu.y = 0;
                menu.speed.y = 3;
                menu.animate = false;
                menu.state = 0;
                car = {mouse.x, mouse.y, {0, 0}, {0, 0}, 0, {0, 0, 0, 0}, {0, 0, 0, 0}};
                carState = 3;
            }
        }
    } else if(menu.state == 2){
        bgCut = {screen.w/2 - 300, screen.h/2 - 200, 600, 450};
        writeText(render, "Options", img.font, toi((screen.w / 2.0f) - 140), 10, 44, 72);
        SDL_SetRenderDrawColor(render, 255, 255, 255, 32);
        SDL_RenderFillRect(render, &bgCut);
        writeText(render, "Resolution:", img.font, (bgCut.x + bgCut.w/20), (bgCut.y + bgCut.h/15), 20, 28);

        ///This part draws all of the resolution buttons.
        //Esta parte desenha todos os botões das resoluções.
        for(int i = 0; i < 13; i++){
            std::string text = res[0][i] + "x" + res[1][i];
            if(i < 6){
                createButton(render, mouse, (bgCut.x + bgCut.w/20), (bgCut.y + bgCut.h/5 + bgCut.h/8 * i), 150, 50);
                writeText(render, text, img.font, (bgCut.x + bgCut.w/20 + 22), (bgCut.y + toi(bgCut.h/4.2) + bgCut.h/8 * i), 16, 24);
            } else {
                createButton(render, mouse, toi(bgCut.x + bgCut.w*0.4), (bgCut.y + bgCut.h/5 + bgCut.h/8 * (i - 6) - bgCut.h/8), 150, 50);
                writeText(render, text, img.font, toi(bgCut.x + bgCut.w*0.4 + 22), (bgCut.y + toi(bgCut.h/4.2) + bgCut.h/8 * (i - 6) - bgCut.h/8), 16, 24);
            }
            writeText(render, "Press F to toggle", img.font, bgCut.x + bgCut.w - 185, (bgCut.y + bgCut.h/15), 12, 18);
            writeText(render, "fullscreen anytime", img.font, bgCut.x + bgCut.w - 190, (bgCut.y + bgCut.h/15) + 30, 12, 18);
            writeText(render, "Toggle fullscreen", img.font, bgCut.x + bgCut.w - 190, (bgCut.y + bgCut.h/15) + 122, 12, 18);
            createButton(render, mouse, bgCut.x + bgCut.w - 130, (bgCut.y + bgCut.h/15) + 150, 50, 50);
            if(screen.full){
                writeText(render, "X", img.font, bgCut.x + bgCut.w - 121, (bgCut.y + bgCut.h/15) + 155, 44, 52);
            }
            std::string highScoreButtonText = "Reset highscore: " + std::to_string(highscore);
            writeText(render, highScoreButtonText, img.font, bgCut.x + bgCut.w - 200, (bgCut.y + bgCut.h/15) + 222, 12, 18);
            createButton(render, mouse, bgCut.x + bgCut.w - 130, (bgCut.y + bgCut.h/15) + 250, 50, 50);
        }
        writeText(render, "< Back", img.font, 25, (screen.h - 50));
    }
}
