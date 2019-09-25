#ifndef STRUCTS_H
#define STRUCTS_H

#include <SDL.h>
#include <iostream>

const std::string res[2][13] = {{"640", "800", "1024", "1152", "1176", "1280", "1280", "1280", "1280", "1360", "1440", "1600", "1920"},
                                {"360", "600", "768",  "864",  "664",  "720",  "768",  "800",  "1024", "768",  "900",  "900",  "1080"}};
/*640	    360
1024	768
1152    864
1176    664
1280	720
1280    768
1280    800
1280    1024
1360	768
1440	900
1600	900
1920	1080*/








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
