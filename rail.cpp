#include "rail.h"

Rail::Rail(){

}

Rail::Rail(int x, int y, int w, int h) {
    pos = Position(x, y);
    width = w;
    height = h;
}

//Upper Left Point
Position Rail::ulp() {
    return pos;
}

void Rail::addCR(Position a, Position b, Semaphore* s){
    crs.push_back(new CR(a,b, s));
}

Rail::CR* Rail::getCR(int i) {
    if(i >= 0 && i < crs.size())
        return crs[i];
    else {
        std::cout << "Índice errado: " << crs.size() << std::endl;
        return crs[0];
    }
}

int Rail::getCRSize() {
    return crs.size();
}
