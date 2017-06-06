#ifndef RAIL_H
#define RAIL_H

struct Position{
    int x;
    int y;
    Position(int _x, int _y) : x {_x}, y {_y}{}
    Position(){}
};

struct Rail{
    Position pos;
    int width; //largura
    int height; //altura

    //Rail(Position p, int w, int h) : pos {p}, width {w}, height {h} {}
    Rail(int x, int y, int w, int h) : pos {Position(x, y)}, width {w}, height {h} {}
    Rail(){}

    //Upper Left Point
    Position ulp() {
        return pos;
    }

};

#endif // RAIL_H
