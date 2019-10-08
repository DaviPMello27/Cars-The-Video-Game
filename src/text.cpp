//////========----------------CARS: THE MOVIE: THE GAME----------------========//////
///                            09/09/2019 - 30/09/2019                            ///
///                             COPYRIGHT DAVI MELLO                              ///
//////========---------------------------------------------------------========//////

///These will be the EN-US comments
//Esses serão os comentários em PT-BR

#include <iostream>
#include <SDL.h>

///writeText():
///
///Analyzes the text given (string or int), character by character, cuts and prints the respective letter from the "img/font.png" file.

//writeText():
//
//Analisa o texto (string ou int), carater por caracter, corta e imprime a respectiva letra do arquivo "img/font.png".

void writeText(SDL_Renderer *render, int text, SDL_Texture *font, int x, int y){
    std::string stringText = std::to_string(text);
    size_t i = 0;
    while(stringText[i] != 0){
        SDL_Rect textCut = {(stringText[i] - 48) * 16, 0, 16, 24};
        SDL_Rect textPos = {x + (30 * static_cast<int>(i)), y, 16*2, 24*2};
        SDL_RenderCopy(render, font, &textCut, &textPos);
        i++;
    }
}

void writeText(SDL_Renderer *render, std::string text, SDL_Texture *font, int x, int y, int w = 28, int h = 48){
    unsigned long long i = 0;
    while(text[i] != 0){
        SDL_Rect textCut = {(text[i] - 48) * 16, 0, 16, 24};
        SDL_Rect textPos = {x + ((w-2) * static_cast<int>(i)), y, w, h};
        SDL_RenderCopy(render, font, &textCut, &textPos);
        i++;
    }
}
