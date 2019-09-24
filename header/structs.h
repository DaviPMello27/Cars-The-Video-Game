#ifndef STRUCTS_H
#define STRUCTS_H

#include <SDL.h>

struct Img {
    SDL_Texture* carSprite;
    SDL_Texture* carPieces;
    SDL_Texture* carHoodSprite;
    SDL_Texture* bgRoad;
    SDL_Texture* barrelSprite;
    SDL_Texture* font;
    SDL_Texture* cursor;
    SDL_Texture* lampSprite;
};

struct Screen {
    int w;
    int h;
    double wScale;
    double hScale;
    bool full;
};

struct Barrel {
    int x;
    int y;
    int skin;
};

struct Angle {
    double speed;
    double value;
};

struct Speed {
    double x;
    double y;
};

struct Car {
    int x;
    int y;
    Angle angle;
    Speed speed;
};

struct Road {
    int x;
    Speed speed;
};

struct CarPiece {
    int x;
    int y;
    Speed speed;
    Angle angle;
    bool broke;
};

struct Menu {
    int y;
    int state;
    Speed speed;
    bool animate;
};

#endif // STRUCTS_H
