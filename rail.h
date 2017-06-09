#ifndef RAIL_H
#define RAIL_H

#include "semaphore.h"
#include <vector>

struct Position{
    int x;
    int y;
    Position(int _x, int _y) : x {_x}, y {_y}{}
    Position(){}
};

struct CR {
    Position p1; //begin
    Position p2; //end
    Semaphore* sem;
    CR(Position a, Position b, Semaphore* s) : p1{a}, p2{b}, sem{s} {}
    CR(int x1, int y1, int x2, int y2, Semaphore* s) : p1{Position(x1,y1)}, p2{Position(x2,y2)}, sem{s} {}
    CR(){}
};

struct Rail{
    Position pos;
    int width; //largura
    int height; //altura
    std::vector<CR> crs; //critical regions

    //Rail(Position p, int w, int h) : pos {p}, width {w}, height {h} {}
    Rail(int x, int y, int w, int h) : pos {Position(x, y)}, width {w}, height {h} {}
    Rail(){}

    //Upper Left Point
    Position ulp() {
        return pos;
    }

    void addCR(Position a, Position b, Semaphore* s){
        crs.push_back(CR(a,b, s));
    }

};

#endif // RAIL_H
