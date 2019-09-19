#ifndef STRUCTS_H
#define STRUCTS_H

struct Mouse {
    int x;
    int y;
};

struct Barrel {
    int x;
    int y;
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

#endif // STRUCTS_H
