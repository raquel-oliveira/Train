#include "train.h"
#include "sizes.h"
#include "rail.h"

Train::Train(int id, int x, int y, Rail r)
{
    this->id = id;
    this->x = x;
    this->y = y;
    speed = 250;
    enable = true;
    this->rail = r;
}

Train::~Train()
{
    threadTrem.join();
}

int Train::getId() const{
    return this->id;
}

void Train::setSpeed(int speed)
{
    this->speed = speed;
}

void Train::setEnable(bool enable)
{
    this->enable = enable;
}

void Train::start()
{
    threadTrem = std::thread(&Train::run,this);
}

void Train::run()
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
        this_thread::sleep_for(chrono::milliseconds(speed));
    }
}

