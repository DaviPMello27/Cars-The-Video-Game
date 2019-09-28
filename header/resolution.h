#ifndef RESOLUTION_H
#define RESOLUTION_H

#include <SDL.h>
#include "structs.h"

void saveResolution(Screen screen, int i);

void loadResolution(Screen &screen, SDL_Window* mainWindow);

void saveFull(Screen screen);

void loadFull(Screen &screen, SDL_Window* mainWindow);

#endif // RESOLUTION_H
