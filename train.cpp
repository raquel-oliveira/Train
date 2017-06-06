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
    rail = r;
    laps = 0;
    curr_x = x;
    curr_y = y;
}

Train::~Train()
{
    threadTrem.join();
}

int Train::getId() const{
    return this->id;
}

int Train::getLaps() {
    return this->laps;
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
            emit updateGUI(id,curr_x,curr_y);
            if (curr_y == rail.ulp().y - (SIZE/2) && curr_x < rail.ulp().x+rail.width-(SIZE/2)){
                curr_x+=10;
            }
            else if (curr_x == rail.ulp().x+rail.width - (SIZE/2) && curr_y < rail.ulp().y+rail.height-(SIZE/2)){
                curr_y+=10;
            }
            else if (curr_x > rail.ulp().x-(SIZE/2) && curr_y == rail.ulp().y+rail.height-(SIZE/2)){
                curr_x-=10;
            }
            else{
                curr_y-=10;
            }
            if(curr_x == x && curr_y == y){
                laps++;
            }
        }
        this_thread::sleep_for(chrono::milliseconds(speed));
    }
}

