#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rail.h"
#include <map>
#include <iostream>


void MainWindow::initialize(){
    trains.push_back(NULL);
   /*GUI*/
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

    label_numberLaps.push_back(ui->label_nb);
    label_numberLaps.push_back(ui->nb_train1);
    label_numberLaps.push_back(ui->nb_train2);
    label_numberLaps.push_back(ui->nb_train3);
    label_numberLaps.push_back(ui->nb_train4);
    label_numberLaps.push_back(ui->nb_train5);
    label_numberLaps.push_back(ui->nb_train6);
    label_numberLaps.push_back(ui->nb_train7);

    label_lastTime.push_back(ui->label_lastTime);
    label_lastTime.push_back(ui->lastTime_train1);
    label_lastTime.push_back(ui->lastTime_train2);
    label_lastTime.push_back(ui->lastTime_train3);
    label_lastTime.push_back(ui->lastTime_train4);
    label_lastTime.push_back(ui->lastTime_train5);
    label_lastTime.push_back(ui->lastTime_train6);
    label_lastTime.push_back(ui->lastTime_train7);
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
        trains.push_back(new Train(i,x+SIZE,y-(SIZE/2), Rail(x, y, width, height)));
    }
    //Connect
    for(int i = 1; i < trains.size(); i++) {
           connect(trains[i],SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
           trains[i]->start();
           trains[i]->setEnable(true);
    }
    server = new Server();
    server->start();
    connect(server,SIGNAL(sendMessage(Mensagem)),SLOT(receiveMessage(Mensagem)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateInterface(int id, int x, int y)
{
    label_train[id]->setGeometry(x,y,SIZE,SIZE);

    //Update number of laps
    QString laps = QString::number(trains[id]->getLaps());
    QLabel *labelLap = qobject_cast<QLabel *>(label_numberLaps[id]);
    if (!labelLap)
       return;
    labelLap->setText(laps);
}

void MainWindow::enableTrains(bool b){
    for (int i = 1; i < trains.size(); i++) {
         trains[i]->setEnable(b);
         label_train[i]->setEnabled(b);
    }
}

void MainWindow::enableTrain(int id, bool b){
    trains[id]->setEnable(b);
    label_train[id]->setEnabled(b);
}

void MainWindow::receiveMessage(Mensagem msg) {

}

