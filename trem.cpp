#include "trem.h"
#include "sizes.h"
#include "rail.h"

Trem::Trem(int id, int x, int y, Rail r)
{
    this->id = id;
    this->x = x;
    this->y = y;
    velocidade = 250;
    enable = true;
    this->rail = r;
}

Trem::~Trem()
{
    threadTrem.join();
}

int Trem::getId() const{
    return this->id;
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
        if(enable){
            emit updateGUI(id,x,y);
            if (y == rail.ulp().y - (SIZE/2) && x < rail.ulp().x+rail.width-(SIZE/2)){
                x+=10;
            }
            else if (x == rail.ulp().x+rail.width - (SIZE/2) && y < rail.ulp().y+rail.height-(SIZE/2)){
                y+=10;
            }
            else if (x > rail.ulp().x-(SIZE/2) && y == rail.ulp().y+rail.height-(SIZE/2)){
                x-=10;
            }
            else{
                y-=10;
            }
        }
        this_thread::sleep_for(chrono::milliseconds(velocidade));
    }
}

