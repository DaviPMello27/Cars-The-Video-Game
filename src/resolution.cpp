//////========----------------CARS: THE MOVIE: THE GAME----------------========//////
///                            09/09/2019 - 30/09/2019                            ///
///                             COPYRIGHT DAVI MELLO                              ///
//////========---------------------------------------------------------========//////

///These will be the EN-US comments
//Esses serão os comentários em PT-BR

#include <iostream>
#include <fstream>
#include "structs.h"
using namespace std;


///saveResolution() and saveFull():
///
///Opens the "bin/res.bin" file and types out the index of the res matrix, or the screen.full bool value that the player last chose.

//saveResolution() and saveFull():
//
//Abre o arquivo "bin/res.bin" e digita o índice da matris res, ou o valor do screen.full que o jogador escolheu por último.


///loadResolution() and loadFull():
///
///Opens the "bin/res.bin" file and retrieves the index of the res matrix from the first line,
///or the screen.full bool value, from the second line, that the player last chose.

//loadResolution() and loadFull():
//
//Abre o arquivo "bin/res.bin" e pega o índice da matriz res na primeira linha,
//ou o valor do screen.full, na segunda linha, que o jogador escolheu por último.

void saveResolution(Screen screen, int i){
    ofstream file("bin/res.bin", ios::out | ios::binary);
    file << i << "\n" << screen.full;
    file.close();
}

void loadResolution(Screen &screen, SDL_Window* mainWindow){
    ifstream file("bin/res.bin");
    string fileRes;
    getline(file, fileRes);
    screen.w = stoi(res[0][stoi(fileRes)]);
    screen.h = stoi(res[1][stoi(fileRes)]);
    file.close();
    SDL_SetWindowSize(mainWindow, screen.w, screen.h);
    if(screen.full){
        SDL_SetWindowFullscreen(mainWindow, SDL_WINDOW_FULLSCREEN);
    }
}

void saveFull(Screen screen){
    ifstream file("bin/res.bin");
    string temp;
    getline(file, temp);
    file.close();
    ofstream fileOut("bin/res.bin", ios::out | ios::binary);
    fileOut << temp << "\n" << screen.full;
    fileOut.close();
}

void loadFull(Screen &screen, SDL_Window* mainWindow){
    ifstream file("bin/res.bin");
    string fileRes;
    getline(file, fileRes);
    getline(file, fileRes);
    screen.full = stoi(fileRes);
    file.close();
    if(screen.full){
        SDL_SetWindowFullscreen(mainWindow, SDL_WINDOW_FULLSCREEN);
    }
}
