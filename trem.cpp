#include "trem.h"
#include "sizes.h"

Trem::Trem(int id, int x, int y)
{
    this->id = id;
    this->x = x;
    this->y = y;
    velocidade = 250;
    enable = true;
}

Trem::~Trem()
{
    threadTrem.join();
}

void Trem::setVelocidade(int velocidade)
{
    this->velocidade = velocidade;
}

void Trem::setEnable(bool enable)
{
    this->enable = enable;
}

void Trem::start()
{
    threadTrem = std::thread(&Trem::run,this);
}

void Trem::run()
{
    while(true){
        switch(id){
        case 1:
            if (enable)
            {
                emit updateGUI(id,x,y);
                if (y == (X1+SIZE,Y1-(SIZE/2)) && x < (X1+SIZE1-(SIZE/2)))
                    x+=10;
                else if (x == (X1+SIZE1-(SIZE/2)) && y < (Y1+SIZE2-(SIZE/2)))
                    y+=10;
                else if (x > (X1-(SIZE/2)) && y == (Y1+SIZE2-(SIZE/2)))
                    x-=10;
                else
                    y-=10;
            }
            break;
        case 2:
            if (enable)
            {
                emit updateGUI(id,x,y);
                if (y == (X2+SIZE,Y1-(SIZE/2)) && x < (X2+SIZE2-(SIZE/2)))
                    x+=10;
                else if (x == (X2+SIZE2-(SIZE/2)) && y < (Y1+SIZE1-(SIZE/2)))
                    y+=10;
                else if (x > (X2-(SIZE/2)) && y == (Y1+SIZE1-(SIZE/2)))
                    x-=10;
                else
                    y-=10;
            }
            break;
        case 3:
            if (enable)
            {
                emit updateGUI(id,x,y);
                if (y == (X3+SIZE,Y1-(SIZE/2)) && x < (X3+SIZE2-(SIZE/2)))
                    x+=10;
                else if (x == (X3+SIZE2-(SIZE/2)) && y < (Y1+SIZE1-(SIZE/2)))
                    y+=10;
                else if (x > (X3-(SIZE/2)) && y == (Y1+SIZE1-(SIZE/2)))
                    x-=10;
                else
                    y-=10;
            }
            break;
        case 4:
            if (enable)
            {
                emit updateGUI(id,x,y);
                if (y == (X4+SIZE,Y1-(SIZE/2)) && x < (X4+SIZE1-(SIZE/2)))
                    x+=10;
                else if (x == (X4+SIZE1-(SIZE/2)) && y < (Y1+SIZE2-(SIZE/2)))
                    y+=10;
                else if (x > (X4-(SIZE/2)) && y == (Y1+SIZE2-(SIZE/2)))
                    x-=10;
                else
                    y-=10;
            }
            break;
        case 5:
            if (enable)
            {
                emit updateGUI(id,x,y);
                if (y == (X3+SIZE,Y3-(SIZE/2)) && x < (X3+SIZE2-(SIZE/2)))
                    x+=10;
                else if (x == (X3+SIZE2-(SIZE/2)) && y < (Y3+SIZE1-(SIZE/2)))
                    y+=10;
                else if (x > (X3-(SIZE/2)) && y == (Y3+SIZE1-(SIZE/2)))
                    x-=10;
                else
                    y-=10;
            }
            break;
        case 6:
            if (enable)
            {
                emit updateGUI(id,x,y);
                if (y == (X2+SIZE,Y3-(SIZE/2)) && x < (X2+SIZE2-(SIZE/2)))
                    x+=10;
                else if (x == (X2+SIZE2-(SIZE/2)) && y < (Y3+SIZE1-(SIZE/2)))
                    y+=10;
                else if (x > (X2-(SIZE/2)) && y == (Y3+SIZE1-(SIZE/2)))
                    x-=10;
                else
                    y-=10;
            }
            break;
        case 7:
            if (enable)
            {
                emit updateGUI(id,x,y);
                if (y == (X7+SIZE,Y2-(SIZE/2)) && x < (X7+SIZE2-(SIZE/2)))
                    x+=10;
                else if (x == (X7+SIZE2-(SIZE/2)) && y < (Y2+SIZE1-(SIZE/2)))
                    y+=10;
                else if (x > (X7-(SIZE/2)) && y == (Y2+SIZE1-(SIZE/2)))
                    x-=10;
                else
                    y-=10;
            }
            break;
        default:
            break;
        }
        this_thread::sleep_for(chrono::milliseconds(velocidade));
    }
}

