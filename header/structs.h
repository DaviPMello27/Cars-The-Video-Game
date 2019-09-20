#ifndef STRUCTS_H
#define STRUCTS_H

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
