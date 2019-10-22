#ifndef STRUCTS_H
#define STRUCTS_H

#include <SDL.h>
#include <iostream>

const std::string res[2][13] = {{"640", "800", "1024", "1152", "1176", "1280", "1280", "1280", "1280", "1360", "1440", "1600", "1920"},
                                {"360", "600", "768",  "864",  "664",  "720",  "768",  "800",  "1024", "768",  "900",  "900",  "1080"}};

struct Img {
    SDL_Texture* carSprite;
    SDL_Texture* carPieces;
    SDL_Texture* carHoodSprite;
    SDL_Texture* headLights;
    SDL_Texture* bgRoad;
    SDL_Texture* bgRoadRain;
    SDL_Texture* npcCarSprite;
    SDL_Texture* npcCarSprite2;
    SDL_Texture* npcCarSprite3;
    SDL_Texture* npcCarSprite4;
    SDL_Texture* npcCarSprite5;
    SDL_Texture* explosion;
    SDL_Texture* font;
    SDL_Texture* cursor;
    SDL_Texture* lampSpriteOn;
    SDL_Texture* lampSpriteOff;
    SDL_Texture* rainSprite;
    SDL_Texture* truckSprite;
    SDL_Texture* crateSprite;
    SDL_Texture* planeShadow;
    SDL_Texture* bombShadow;
    SDL_Texture* bomb;
};

struct Debug {
    bool active;
    int passwordCounter;
    bool NPCCars;
};

struct Screen {
    int w;
    int h;
    double wScale;
    double hScale;
    bool full;
};

struct Angle {
    double speed;
    double value;
};

struct Speed {
    double x;
    double y;
};

struct Animation {
    int x;
    int y;
    Speed speed;
    int counter;
    bool active;
    SDL_Rect spriteCut;
    SDL_Rect spritePos;
};

struct NPCCar {
    int x;
    int y;
    int skin;
    Speed speed;
    SDL_Rect cut;
    SDL_Rect pos;
};

struct Drift {
    int counter;
    int factor;
};

struct Car {
    int x;
    int y;
    int health;
    Angle angle;
    Speed speed;
    Drift drift;
    int moveCounter;
    SDL_Rect cut;
    SDL_Rect pos;
};

struct Boss {
    int x;
    int y;
    Speed speed;
    bool active;
    bool defineVars;
    bool attacks;
    int endCounter;
    SDL_Point projectile;
    SDL_Rect cut;
    SDL_Rect pos;
};

struct Road {
    int x;
    Speed speed;
    SDL_Rect cut;
    SDL_Rect pos;
};

struct CarPiece {
    int x;
    int y;
    Speed speed;
    Angle angle;
    bool broke;
    SDL_Rect cut;
    SDL_Rect pos;
};

struct Menu {
    int y;
    int state;
    Speed speed;
    bool animate;
};

struct Night {
    int threshold;
    bool active;
};

struct Rain {
    int count;
    int start;
    int puddleCount;
    bool active;
    SDL_Rect cut;
};

#endif // STRUCTS_H
