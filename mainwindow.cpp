#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sizes.h"
#include <map>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    trains[new Trem(1,X1+SIZE,Y1-(SIZE/2))] = ui->train01;
    trains[new Trem(2,X2+SIZE,Y1-(SIZE/2))] = ui->train02;
    trains[new Trem(3,X3+SIZE,Y1-(SIZE/2))] = ui->train03;
    trains[new Trem(4,X4+SIZE,Y1-(SIZE/2))] = ui->train04;
    trains[new Trem(5,X3+SIZE,Y3-(SIZE/2))] = ui->train05;
    trains[new Trem(6,X2+SIZE,Y3-(SIZE/2))] = ui->train06;
    trains[new Trem(7,X7+SIZE,Y2-(SIZE/2))] = ui->train07;

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

