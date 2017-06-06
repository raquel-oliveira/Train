#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rail.h"
#include <map>

void MainWindow::initialize(){
    label_train.push_back(NULL);
    label_train.push_back(ui->train01);
    label_train.push_back(ui->train02);
    label_train.push_back(ui->train03);
    label_train.push_back(ui->train04);
    label_train.push_back(ui->train05);
    label_train.push_back(ui->train06);
    label_train.push_back(ui->train07);

    label_trainTrack.push_back(NULL);
    label_trainTrack.push_back(ui->trainTrack01);
    label_trainTrack.push_back(ui->trainTrack02);
    label_trainTrack.push_back(ui->trainTrack03);
    label_trainTrack.push_back(ui->trainTrack04);
    label_trainTrack.push_back(ui->trainTrack05);
    label_trainTrack.push_back(ui->trainTrack06);
    label_trainTrack.push_back(ui->trainTrack07);
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initialize();

    int x, y, width, height;
    //Create trains by GUI
    for(int i = 1; i < label_train.size(); i++) {
        label_trainTrack[i]->geometry().getRect(&x, &y, &width, &height);
        trains[new Train(i,x+SIZE,y-(SIZE/2), Rail(x, y, width, height))] = label_train[i];
    }
    //Connect
    for(auto it = trains.begin(); it != trains.end(); ++it) {
           connect(it->first,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
           it->first->start();
           it->first->setEnable(false);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateInterface(int id, int x, int y)
{
    Train* t = new Train (id, 0, 0, Rail(0,0,0,0));
    auto it = trains.find(t);
    it->second->setGeometry(x,y,SIZE,SIZE);
}

void MainWindow::enableTrains(bool b){
    for (map<Train*, QWidget*>::iterator it = trains.begin(); it != trains.end(); ++it){
         it->first->setEnable(b);
         it->second->setEnabled(b);
    }
}

void MainWindow::enableTrain(int id, bool b){
    Train* t = new Train (id, 0, 0, Rail(0,0,0,0));
    auto it = trains.find(t);
    it->first->setEnable(b);
    it->second->setEnabled(b);
}

