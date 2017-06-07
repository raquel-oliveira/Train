#include "train.h"
#include <iostream>

Train::Train(int id, int x, int y, Rail r)
{
    this->id = id;
    this->x = x;
    this->y = y;
    speed = 50;
    enable = true;
    rail = r;
    laps = 0;
    curr_x = x;
    curr_y = y;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_beg);
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

double Train::getLastRaceTime(){
    if(timeRace.size() == 0){
        return 0;
    } else{
        this->timeRace.back();
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
                timeRace.push_back((ts_end.tv_sec - ts_beg.tv_sec) + (ts_end.tv_nsec - ts_beg.tv_nsec) / 1e9);
                //cout << id <<"  FIM VOLTA: " << (ts_end.tv_sec - ts_beg.tv_sec) + (ts_end.tv_nsec - ts_beg.tv_nsec) / 1e9 << " sec" <<endl;
                clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_beg);
            }
        }
        this_thread::sleep_for(chrono::milliseconds(speed));
    }
}

