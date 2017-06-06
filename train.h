#ifndef TREM_H
#define TREM_H

#include <QObject>
#include <thread>
#include <chrono>
#include "rail.h"

//Defize size of train
#define SIZE 20
using namespace std;

class Train : public QObject
{
    Q_OBJECT
public:

    struct CompLessTrain {
        bool operator()(Train * t1, const Train * t2) const{
            return (t1->getId() < t2->getId());
        }
    };

    Train(int,int,int,Rail);
    ~Train();
    void start();
    void run();
    void setSpeed(int);
    void setEnable(bool);
    int getId() const;
    int getLaps();

signals:
    void updateGUI(int,int,int);

private:
   std::thread threadTrem;
   int id;
   int x;
   int y;
   int speed;
   bool enable;
   Rail rail;
   int laps;
   int curr_x, curr_y;
};

#endif // TREM_H


