#include <iostream>
#include <fstream>
#include "structs.h"
using namespace std;

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
    cout << "First line: " << stoi(fileRes) << "\n";
    getline(file, fileRes);
    cout << "Second line: " << stoi(fileRes) << "\n";
    screen.full = stoi(fileRes);
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
