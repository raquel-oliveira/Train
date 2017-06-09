#ifndef RAIL_H
#define RAIL_H
#include "semaphore.h"
#include <iostream>
#include <vector>

struct Position{
    int x;
    int y;
    Position(int _x, int _y) : x {_x}, y {_y}{}
    Position(){}
};

class Rail
{
    class CR {
    public:
        Position p1; //begin
        Position p2; //end
        Semaphore* sem;
        CR(Position a, Position b, Semaphore* s) : p1{a}, p2{b}, sem{s} {}
        CR(int x1, int y1, int x2, int y2, Semaphore* s) : p1{Position(x1,y1)}, p2{Position(x2,y2)}, sem{s} {}
        CR(){}
    };

public:
    Rail();
    Rail(int, int, int, int);
    void addCR(Position, Position, Semaphore*);
    Position ulp();
    CR* getCR(int);
    int getCRSize();
    int width; //largura
    int height; //altura

private:
    Position pos;
    std::vector<CR*> crs; //critical regions
};

#endif // RAIL_H
