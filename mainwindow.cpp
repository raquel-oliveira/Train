#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rail.h"
#include <map>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int x, y, width, height;

    ui->trainTrack01->geometry().getRect(&x, &y, &width, &height);
    trains[new Trem(1,x+SIZE,y-(SIZE/2), Rail(x, y, width, height))] = ui->train01;

    ui->trainTrack02->geometry().getRect(&x, &y, &width, &height);
    trains[new Trem(2,x+SIZE,y-(SIZE/2), Rail(x, y, width, height))] = ui->train02;

    ui->trainTrack03->geometry().getRect(&x, &y, &width, &height);
    trains[new Trem(3,x+SIZE,y-(SIZE/2), Rail(x, y, width, height))] = ui->train03;

    ui->trainTrack04->geometry().getRect(&x, &y, &width, &height);
    trains[new Trem(4,x+SIZE,y-(SIZE/2), Rail(x, y, width, height))] = ui->train04;

    ui->trainTrack05->geometry().getRect(&x, &y, &width, &height);
    trains[new Trem(5,x+SIZE,y-(SIZE/2), Rail(x, y, width, height))] = ui->train05;

    ui->trainTrack06->geometry().getRect(&x, &y, &width, &height);
    trains[new Trem(6,x+SIZE,y-(SIZE/2), Rail(x, y, width, height))] = ui->train06;

    ui->trainTrack07->geometry().getRect(&x, &y, &width, &height);
    trains[new Trem(7,x+SIZE,y-(SIZE/2), Rail(x, y, width, height))] = ui->train07;

    for(map<Trem*, QWidget*>::iterator it = trains.begin(); it != trains.end(); ++it) {
        connect(it->first,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
        it->first->start();
        it->first->setEnable(true);
     }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateInterface(int id, int x, int y)
{
    //TODO: change for find. Sobrecarregar ==
    for(map<Trem*, QWidget*>::iterator it = trains.begin(); it != trains.end(); ++it) {
        if(it->first->getId() == id){
             it->second->setGeometry(x,y,SIZE,SIZE);
        }
     }
}

void MainWindow::enableTrains(bool b){
    for (map<Trem*, QWidget*>::iterator it = trains.begin(); it != trains.end(); ++it){
         it->first->setEnable(b);
         it->second->setEnabled(b);
    }
}

void MainWindow::enableTrain(int id, bool b){
    //TODO: change for find. Sobrecarregar ==
    for(map<Trem*, QWidget*>::iterator it = trains.begin(); it != trains.end(); ++it) {
        if(it->first->getId() == id){
            it->first->setEnable(b);
            it->second->setEnabled(b);
        }
     }
}

