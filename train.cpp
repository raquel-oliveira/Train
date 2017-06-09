#include "train.h"

Train::Train(int id, int x, int y, Rail* r)
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

Rail* Train::getRail(){
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

string Train::getMediaRaceTime(){
    int size = timeRace.size();
    if(size == 0){
        return "0";
    } else {
        double media = 0;
        for (int i = 0; i < size; i++){
            media += timeRace[i];
        }
        media = media/size;
        return to_string(media);
    }
}

string Train::getStdDevTime(){
    int size = timeRace.size();
    double mean = stod(this->getMediaRaceTime());
    if(size == 0){
        return "0";
    } else {
        double stdDev = 0;
        for (int i = 0; i < size; i++){
            stdDev += (timeRace[i] - mean) * (timeRace[i] - mean);
        }
        stdDev = stdDev/size;
        stdDev = sqrt(stdDev);
        return to_string(stdDev);
    }
}


void Train::start()
{
    threadTrem = std::thread(&Train::run,this);
}

void Train::run()
{
    int nextCR = 0;
    queue<int> entered;
    while(true){
        if(enable){
            emit updateGUI(id,curr_x,curr_y);
            if (curr_y == rail->ulp().y - (SIZE/2) && curr_x < rail->ulp().x+rail->width-(SIZE/2)){
                if(curr_y == rail->getCR(nextCR)->p1.y - (SIZE/2) && curr_x == rail->getCR(nextCR)->p1.x - SIZE){
                    if(id != 7) {
                        rail->getCR(nextCR)->sem->P();
                        emit updateGUI(rail->getCR(nextCR)->sem->getId(), rail->getCR(nextCR)->sem->getCounter());
                        emit updateLog(id, rail->getCR(nextCR)->sem->getId(), rail->getCR(nextCR)->sem->getCounter());
                        entered.push(nextCR);
                        if(nextCR == rail->getCRSize() - 1)
                            nextCR = 0;
                        else
                            nextCR++;
                    }
                    else {
                        rail->getCR(nextCR+1)->sem->P();
                        emit updateGUI(rail->getCR(nextCR+1)->sem->getId(), rail->getCR(nextCR+1)->sem->getCounter());
                        emit updateLog(id, rail->getCR(nextCR+1)->sem->getId(), rail->getCR(nextCR+1)->sem->getCounter());
                        rail->getCR(nextCR)->sem->P();
                        emit updateGUI(rail->getCR(nextCR)->sem->getId(), rail->getCR(nextCR)->sem->getCounter());
                        emit updateLog(id, rail->getCR(nextCR)->sem->getId(), rail->getCR(nextCR)->sem->getCounter());
                        entered.push(nextCR);
                        entered.push(nextCR+1);
                        if(nextCR+1 == rail->getCRSize() - 1)
                            nextCR = 0;
                        else
                            nextCR+=2;
                    }
                }
                else if(entered.size() > 0 && curr_y == rail->getCR(entered.front())->p2.y - (SIZE/2) && curr_x == rail->getCR(entered.front())->p2.x) {
                    rail->getCR(entered.front())->sem->V();
                    emit updateGUI(rail->getCR(entered.front())->sem->getId(), rail->getCR(entered.front())->sem->getCounter());
                    emit updateLog(id, rail->getCR(entered.front())->sem->getId(), rail->getCR(entered.front())->sem->getCounter());
                    entered.pop();
                }
                curr_x+=10;
            }
            else if (curr_x == rail->ulp().x+rail->width - (SIZE/2) && curr_y < rail->ulp().y+rail->height-(SIZE/2)){
                if(curr_x == rail->getCR(nextCR)->p1.x - (SIZE/2) && curr_y == rail->getCR(nextCR)->p1.y - SIZE){
                    if(id != 7) {
                        rail->getCR(nextCR)->sem->P();
                        emit updateGUI(rail->getCR(nextCR)->sem->getId(), rail->getCR(nextCR)->sem->getCounter());
                        emit updateLog(id, rail->getCR(nextCR)->sem->getId(), rail->getCR(nextCR)->sem->getCounter());
                        entered.push(nextCR);
                        if(nextCR == rail->getCRSize() - 1)
                            nextCR = 0;
                        else
                            nextCR++;
                    }
                    else {
                        rail->getCR(nextCR+1)->sem->P();
                        emit updateGUI(rail->getCR(nextCR+1)->sem->getId(), rail->getCR(nextCR+1)->sem->getCounter());
                        emit updateLog(id, rail->getCR(nextCR+1)->sem->getId(), rail->getCR(nextCR+1)->sem->getCounter());
                        rail->getCR(nextCR)->sem->P();
                        emit updateGUI(rail->getCR(nextCR)->sem->getId(), rail->getCR(nextCR)->sem->getCounter());
                        emit updateLog(id, rail->getCR(nextCR)->sem->getId(), rail->getCR(nextCR)->sem->getCounter());
                        entered.push(nextCR);
                        entered.push(nextCR+1);
                        if(nextCR+1 == rail->getCRSize() - 1)
                            nextCR = 0;
                        else
                            nextCR+=2;
                    }
                }
                else if(entered.size() > 0 && curr_x == rail->getCR(entered.front())->p2.x - (SIZE/2) && curr_y == rail->getCR(entered.front())->p2.y) {
                    rail->getCR(entered.front())->sem->V();
                    emit updateGUI(rail->getCR(entered.front())->sem->getId(), rail->getCR(entered.front())->sem->getCounter());
                    emit updateLog(id, rail->getCR(entered.front())->sem->getId(), rail->getCR(entered.front())->sem->getCounter());
                    entered.pop();
                }
                curr_y+=10;
            }
            else if (curr_x > rail->ulp().x-(SIZE/2) && curr_y == rail->ulp().y+rail->height-(SIZE/2)){
                if(curr_y == rail->getCR(nextCR)->p1.y - (SIZE/2) && curr_x == rail->getCR(nextCR)->p1.x){
                    if(id != 7) {
                        rail->getCR(nextCR)->sem->P();
                        emit updateGUI(rail->getCR(nextCR)->sem->getId(), rail->getCR(nextCR)->sem->getCounter());
                        emit updateLog(id, rail->getCR(nextCR)->sem->getId(), rail->getCR(nextCR)->sem->getCounter());
                        entered.push(nextCR);
                        if(nextCR == rail->getCRSize() - 1)
                            nextCR = 0;
                        else
                            nextCR++;
                    }
                    else {
                        rail->getCR(nextCR+1)->sem->P();
                        emit updateGUI(rail->getCR(nextCR+1)->sem->getId(), rail->getCR(nextCR+1)->sem->getCounter());
                        emit updateLog(id, rail->getCR(nextCR+1)->sem->getId(), rail->getCR(nextCR+1)->sem->getCounter());
                        rail->getCR(nextCR)->sem->P();
                        emit updateGUI(rail->getCR(nextCR)->sem->getId(), rail->getCR(nextCR)->sem->getCounter());
                        emit updateLog(id, rail->getCR(nextCR)->sem->getId(), rail->getCR(nextCR)->sem->getCounter());
                        entered.push(nextCR);
                        entered.push(nextCR+1);
                        if(nextCR+1 == rail->getCRSize() - 1)
                            nextCR = 0;
                        else
                            nextCR+=2;
                    }
                }
                else if(entered.size() > 0 && curr_y == rail->getCR(entered.front())->p2.y - (SIZE/2) && curr_x == rail->getCR(entered.front())->p2.x - SIZE) {
                    rail->getCR(entered.front())->sem->V();
                    emit updateGUI(rail->getCR(entered.front())->sem->getId(), rail->getCR(entered.front())->sem->getCounter());
                    emit updateLog(id, rail->getCR(entered.front())->sem->getId(), rail->getCR(entered.front())->sem->getCounter());
                    entered.pop();
                }
                curr_x-=10;
            }
            else{
                if(curr_x == rail->getCR(nextCR)->p1.x - (SIZE/2) && curr_y == rail->getCR(nextCR)->p1.y){
                    if(id != 7) {
                        rail->getCR(nextCR)->sem->P();
                        emit updateGUI(rail->getCR(nextCR)->sem->getId(), rail->getCR(nextCR)->sem->getCounter());
                        emit updateLog(id, rail->getCR(nextCR)->sem->getId(), rail->getCR(nextCR)->sem->getCounter());
                        entered.push(nextCR);
                        if(nextCR == rail->getCRSize() - 1)
                            nextCR = 0;
                        else
                            nextCR++;
                    }
                    else {
                        rail->getCR(nextCR+1)->sem->P();
                        emit updateGUI(rail->getCR(nextCR+1)->sem->getId(), rail->getCR(nextCR+1)->sem->getCounter());
                        emit updateLog(id, rail->getCR(nextCR+1)->sem->getId(), rail->getCR(nextCR+1)->sem->getCounter());
                        rail->getCR(nextCR)->sem->P();
                        emit updateGUI(rail->getCR(nextCR)->sem->getId(), rail->getCR(nextCR)->sem->getCounter());
                        emit updateLog(id, rail->getCR(nextCR)->sem->getId(), rail->getCR(nextCR)->sem->getCounter());
                        entered.push(nextCR);
                        entered.push(nextCR+1);
                        if(nextCR+1 == rail->getCRSize() - 1)
                            nextCR = 0;
                        else
                            nextCR+=2;
                    }
                }
                else if(entered.size() > 0 && curr_x == rail->getCR(entered.front())->p2.x - (SIZE/2) && curr_y == rail->getCR(entered.front())->p2.y - SIZE) {
                    rail->getCR(entered.front())->sem->V();
                    emit updateGUI(rail->getCR(entered.front())->sem->getId(), rail->getCR(entered.front())->sem->getCounter());
                    emit updateLog(id, rail->getCR(entered.front())->sem->getId(), rail->getCR(entered.front())->sem->getCounter());
                    entered.pop();
                }
                curr_y-=10;
            }
            if(curr_x == x && curr_y == y){
                laps++;
                clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_end);
                timeRace.push_back((double)(ts_end.tv_sec - ts_beg.tv_sec) + (ts_end.tv_nsec - ts_beg.tv_nsec) / 1e9);
                clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_beg);
                emit updateGUI(id);

            }
        }
        this_thread::sleep_for(chrono::milliseconds(CONV-speed));
    }
}
