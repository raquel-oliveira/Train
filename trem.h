#ifndef TREM_H
#define TREM_H

#include <QObject>
#include <thread>
#include <chrono>
#include "rail.h"

//Defize size of train
#define SIZE 20
using namespace std;

class Trem : public QObject
{
    Q_OBJECT
public:
    Trem(int,int,int,Rail);
    ~Trem();
    void start();
    void run();
    void setVelocidade(int);
    void setEnable(bool);
    int getId();

signals:
    void updateGUI(int,int,int);

private:
   std::thread threadTrem;
   int id;
   int x;
   int y;
   int velocidade;
   bool enable;
   Rail rail;
};

#endif // TREM_H



