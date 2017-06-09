#include "train.h"
#include <iostream>

Train::Train(int id, int x, int y, Rail r)
{
    this->id = id;
    this->x = x;
    this->y = y;
    speed = 270;
    enable = false;
    rail = r;
    laps = 0;
    curr_x = x;
    curr_y = y;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_beg);
}

//gambiarra init
void Train::init(int x, int y){
    this->x = x;
    this->y = y;
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

Rail Train::getRail(){
    return this->rail;
}

void Train::setSpeed(int speed)
{
    this->speed = speed;
}

void Train::setEnable(bool enable)
{
    this->enable = enable;
}

string Train::getLastRaceTime(){
    if(timeRace.size() == 0){
        return "0";
    } else{
        return to_string(this->timeRace.back());
    }
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
                clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_end);
                timeRace.push_back((double)(ts_end.tv_sec - ts_beg.tv_sec) + (ts_end.tv_nsec - ts_beg.tv_nsec) / 1e9);
                clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_beg);
            }
        }
        this_thread::sleep_for(chrono::milliseconds(CONV-speed));
    }
}

