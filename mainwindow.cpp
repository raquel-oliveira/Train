#include "mainwindow.h"

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
        trains.push_back(new Train(i,0,0, new Rail(x, y, width, height)));
    }

    //Creation of critical regions and update position
    fillCR();

    //Connect
    for(int i = 1; i < trains.size(); i++) {
           connect(trains[i],SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
           connect(trains[i],SIGNAL(updateGUI(int,int)),SLOT(updateSem(int,int)));
           updateInterface(i); //to initialize
           connect(trains[i],SIGNAL(updateGUI(int, bool)),SLOT(enableTrain(int, bool)));
           connect(trains[i],SIGNAL(updateGUI(int)),SLOT(updateInterface(int)));
           connect(trains[i],SIGNAL(updateLog(int,int,int)),SLOT(updateLog(int,int,int)));
           trains[i]->start();
    }

    server = new Server();
    server->start();
    connect(server,SIGNAL(sendMessage(int, int, int)),SLOT(receiveMessage(int, int, int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateInterface(int id){
    //Update number of laps
    QString laps = QString::number(trains[id]->getLaps());
    QLabel *labelLap = qobject_cast<QLabel *>(label_numberLaps[id]);
    if (!labelLap)
       return;
    labelLap->setText(laps);

    //Update time of last race
    QString lastTime = QString::fromStdString(trains[id]->getLastRaceTime());
    QLabel *labelLastTime = qobject_cast<QLabel *>(label_lastTime[id]);
    if (!labelLastTime)
       return;
    labelLastTime->setText(lastTime);

    //Update mean(time) of races
    QString average = QString::fromStdString(trains[id]->getMediaRaceTime());
    QLabel *labelMediaTime = qobject_cast<QLabel *>(label_mediaTime[id]);
    if (!labelMediaTime)
       return;
    labelMediaTime->setText(average);

    //Update standard deviation(time) of races
    QString stdDev = QString::fromStdString(trains[id]->getStdDevTime());
    QLabel *labelStdDevTime = qobject_cast<QLabel *>(label_stdDevTime[id]);
    if (!labelStdDevTime)
       return;
    labelStdDevTime->setText(stdDev);
}

void MainWindow::updateInterface(int id, int x, int y)
{
    label_train[id]->setGeometry(x,y,SIZE,SIZE);
}

void MainWindow::updateSem(int id, int flag){
    if (id >= 0 && id < label_sem.size()){
        QLabel *pLabel = qobject_cast<QLabel *>(label_sem[id]);
        if (flag == 1){
            pLabel->setStyleSheet("QLabel { background-color : white;}");
        } else if (flag == 0) {
            pLabel->setStyleSheet("QLabel { background-color : black;}");
        } else{
            pLabel->setStyleSheet("QLabel { background-color : pink;}");
        }
    }
}

void MainWindow::updateLog(int trainId, int semId, int semCounter) {
    string s;
    if(semCounter == 1)
        s = "Trem " + to_string(trainId) + " deu V no semáforo " + to_string(semId) + ".";
    else
        s = "Trem " + to_string(trainId) + " deu P no semáforo " + to_string(semId) + ".";
    QString Qs = QString::fromStdString(s);
    ui->listWidget->addItem(Qs);
}

void MainWindow::enableTrain(int id, bool b){
    if (id > 0 && id < trains.size()){
        label_train[id]->setEnabled(b);
    }
}

void MainWindow::receiveMessage(int command, int train, int speed) {
    switch (command) {
        case DISCONNECT:
            break;
        case TURN_ON_TRAINS:
            cout << "Ligar todos os trens" << endl;
            for (int i = 1; i < trains.size(); i++) {
                trains[i]->setEnable(true);
            }
            break;
        case TURN_OFF_TRAINS:
            cout << "Desligar todos os trens" << endl;
            for (int i = 1; i < trains.size(); i++) {
                trains[i]->setEnable(false);
            }
            break;
        case TURN_ON_TRAIN:
            cout << "Ligar trem "<< train << endl;
            trains[train]->setEnable(true);
            break;
        case TURN_OFF_TRAIN:
            cout << "Desligar trem "<< train << endl;
            trains[train]->setEnable(false);
            break;
        case CHANGE_SPEED:
            if (train > 0 && train < trains.size()){
                cout << "Mudar velocidade do trem "<< train << endl;
                trains[train]->setSpeed(speed);
            }
            break;
        case QUIT:
           close();
            break;
        }
}

void MainWindow::initTrain(int id, int x, int y) {
    trains[id]->init(x, y);
    //label_train[id]->geometry().setX(x);
    //label_train[id]->geometry().setY(y);
    label_train[id]->setGeometry(x, y, SIZE, SIZE);
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

    label_mediaTime.push_back(ui->label_average);
    label_mediaTime.push_back(ui->mediaTime_train1);
    label_mediaTime.push_back(ui->mediaTime_train2);
    label_mediaTime.push_back(ui->mediaTime_train3);
    label_mediaTime.push_back(ui->mediaTime_train4);
    label_mediaTime.push_back(ui->mediaTime_train5);
    label_mediaTime.push_back(ui->mediaTime_train6);
    label_mediaTime.push_back(ui->mediaTime_train7);

    label_stdDevTime.push_back(NULL);
    label_stdDevTime.push_back(ui->stdDev_train1);
    label_stdDevTime.push_back(ui->stdDev_train2);
    label_stdDevTime.push_back(ui->stdDev_train3);
    label_stdDevTime.push_back(ui->stdDev_train4);
    label_stdDevTime.push_back(ui->stdDev_train5);
    label_stdDevTime.push_back(ui->stdDev_train6);
    label_stdDevTime.push_back(ui->stdDev_train7);


    sems.push_back(new Semaphore(1234,1,0));
    sems.push_back(new Semaphore(1235,1,1));
    sems.push_back(new Semaphore(1236,1,2));
    sems.push_back(new Semaphore(1237,1,3));
    sems.push_back(new Semaphore(1238,1,4));
    sems.push_back(new Semaphore(1239,1,5));
    sems.push_back(new Semaphore(1240,1,6));
    sems.push_back(new Semaphore(1241,1,7));
    sems.push_back(new Semaphore(1242,1,8));
    sems.push_back(new Semaphore(1243,1,9));

    label_sem.push_back(ui->sem0);
    label_sem.push_back(ui->sem1);
    label_sem.push_back(ui->sem2);
    label_sem.push_back(ui->sem3);
    label_sem.push_back(ui->sem4);
    label_sem.push_back(ui->sem5);
    label_sem.push_back(ui->sem6);
    label_sem.push_back(ui->sem7);
    label_sem.push_back(ui->sem8);
    label_sem.push_back(ui->sem9);

    for (int i = 1; i < trains.size(); i++) {
        trains[i]->setEnable(false);
    }
}

void MainWindow::fillCR(){
    //Train 1
    initTrain(1, 60, 160);
    trains[1]->getRail()->addCR(Position(180,20), Position(180,130), sems[0]); //RC1
    trains[1]->getRail()->addCR(Position(180,240), Position(180,350), sems[7]); //RC8
    //Train 2
    initTrain(2, 330, 10);
    trains[2]->getRail()->addCR(Position(510,20), Position(510,130), sems[1]); //RC2
    trains[2]->getRail()->addCR(Position(510,130), Position(340,130), sems[3]); //RC4
    trains[2]->getRail()->addCR(Position(180,130), Position(180,20), sems[0]); //RC1
    //Train 3
    initTrain(3, 730, 10);
    trains[3]->getRail()->addCR(Position(840,20), Position(840,130), sems[2]); //RC3
    trains[3]->getRail()->addCR(Position(670,130), Position(510,130), sems[4]); //RC5
    trains[3]->getRail()->addCR(Position(510,130), Position(510,20), sems[1]); //RC2
    //Train 4
    initTrain(4, 940, 170);
    trains[4]->getRail()->addCR(Position(840,350), Position(840,240), sems[9]); //RC10
    trains[4]->getRail()->addCR(Position(840,130), Position(840,20), sems[2]); //RC3
    //Train 5
    initTrain(5, 690, 340);
    trains[5]->getRail()->addCR(Position(510,350), Position(510,240), sems[8]); //RC9
    trains[5]->getRail()->addCR(Position(510,240), Position(670,240), sems[6]); //RC7
    trains[5]->getRail()->addCR(Position(840,240), Position(840,350), sems[9]); //RC10
    //Train 6
    initTrain(6, 320, 340);
    trains[6]->getRail()->addCR(Position(180,350), Position(180,240), sems[7]); //RC8
    trains[6]->getRail()->addCR(Position(340,240), Position(510,240), sems[5]); //RC6
    trains[6]->getRail()->addCR(Position(510,240), Position(510,350), sems[8]); //RC9
    //Train 7
    initTrain(7, 660, 150);
    trains[7]->getRail()->addCR(Position(340,130), Position(510,130), sems[3]); //RC4
    trains[7]->getRail()->addCR(Position(510,130), Position(670,130), sems[4]); //RC5
    trains[7]->getRail()->addCR(Position(670,240), Position(510,240), sems[6]); //RC7
    trains[7]->getRail()->addCR(Position(510,240), Position(340,240), sems[5]); //RC6
}
