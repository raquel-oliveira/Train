#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rail.h"
#include <map>
#include <iostream>

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

    //Alimentar regiões criticas.
    fillCR();

    //Connect
    for(int i = 1; i < trains.size(); i++) {
           connect(trains[i],SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
           trains[i]->start();
    }

    enableTrains(false);
    server = new Server();
    server->start();
    connect(server,SIGNAL(sendMessage(int, int, int)),SLOT(receiveMessage(int, int, int)));
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
    if (id > 0 && id < trains.size()){
        trains[id]->setEnable(b);
        label_train[id]->setEnabled(b);
    }
}

void MainWindow::receiveMessage(int command, int train, int speed) {
    switch (command) {
        case DISCONNECT:
            break;
        case TURN_ON_TRAINS:
            cout << "Ligar todos os trens" << endl;
            enableTrains(true);
            break;
        case TURN_OFF_TRAINS:
            cout << "Desligar todos os trens" << endl;
            enableTrains(false);
            break;
        case TURN_ON_TRAIN:
            cout << "Ligar trem "<< train << endl;
            enableTrain(train, true);
            break;
        case TURN_OFF_TRAIN:
            cout << "Desligar trem "<< train << endl;
            enableTrain(train, false);
            break;
        case CHANGE_SPEED:
            if (train > 0 && train < trains.size()){
                trains[train]->setSpeed(speed);
            }
            break;
        case QUIT:
           close();
            break;
        }
    cout << "acabei finalizar msg" << endl;
}

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

    sems.push_back(Semaphore(1234,1));
    sems.push_back(Semaphore(1235,1));
    sems.push_back(Semaphore(1236,1));
    sems.push_back(Semaphore(1237,1));
    sems.push_back(Semaphore(1238,1));
    sems.push_back(Semaphore(1239,1));
    sems.push_back(Semaphore(1240,1));
    sems.push_back(Semaphore(1241,1));
    sems.push_back(Semaphore(1242,1));
    sems.push_back(Semaphore(1243,1));

}

void MainWindow::fillCR(){
    //Train 1
    trains[1]->getRail().addCR(Position(180,20), Position(180,130), &sems[0]); //RC1
    trains[1]->getRail().addCR(Position(180,240), Position(180,350), &sems[7]); //RC8
    //Train 2
    trains[2]->getRail().addCR(Position(510,20), Position(510,130), &sems[1]); //RC2
    trains[2]->getRail().addCR(Position(510,130), Position(180,130), &sems[3]); //RC4
    trains[2]->getRail().addCR(Position(180,130), Position(180,20), &sems[0]); //RC1
    //Train 3
    trains[3]->getRail().addCR(Position(840,20), Position(840,130), &sems[2]); //RC3
    trains[3]->getRail().addCR(Position(675,130), Position(510,130), &sems[4]); //RC5
    trains[3]->getRail().addCR(Position(510,130), Position(510,20), &sems[1]); //RC2
    //Train 4
    trains[4]->getRail().addCR(Position(840,350), Position(840,210), &sems[9]); //RC10
    trains[4]->getRail().addCR(Position(840,130), Position(180,20), &sems[2]); //RC3
    //Train 5
    trains[5]->getRail().addCR(Position(510,350), Position(510,240), &sems[8]); //RC9
    trains[5]->getRail().addCR(Position(510,240), Position(675,240), &sems[6]); //RC7
    trains[5]->getRail().addCR(Position(840,210), Position(840,350), &sems[9]); //RC10
    //Train 6
    trains[6]->getRail().addCR(Position(180,350), Position(180,240), &sems[7]); //RC8
    trains[6]->getRail().addCR(Position(345,240), Position(510,240), &sems[5]); //RC6
    trains[6]->getRail().addCR(Position(510,240), Position(510,350), &sems[8]); //RC9
    //Train 7
    trains[7]->getRail().addCR(Position(180,130), Position(510,130), &sems[3]); //RC4
    trains[7]->getRail().addCR(Position(510,130), Position(675,130), &sems[4]); //RC5
    trains[7]->getRail().addCR(Position(675,240), Position(510,240), &sems[6]); //RC7
    trains[7]->getRail().addCR(Position(510,240), Position(345,240), &sems[5]); //RC6
}
