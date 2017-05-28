#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sizes.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    train1 = new Trem(1,X1+SIZE,Y1-(SIZE/2));
    connect(train1,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    train1->start();

    train2 = new Trem(2,X2+SIZE,Y1-(SIZE/2));
    connect(train2,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    train2->start();

    train3 = new Trem(3,X3+SIZE,Y1-(SIZE/2));
    connect(train3,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    train3->start();

    train4 = new Trem(4,X4+SIZE,Y1-(SIZE/2));
    connect(train4,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    train4->start();

    train5 = new Trem(5,X3+SIZE,Y3-(SIZE/2));
    connect(train5,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    train5->start();

    train6 = new Trem(6,X2+SIZE,Y3-(SIZE/2));
    connect(train6 ,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    train6->start();

    train7 = new Trem(7,X7+SIZE,Y2-(SIZE/2));
    connect(train7,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    train7->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateInterface(int id, int x, int y)
{
    switch(id){
        case 1:
            ui->train01->setGeometry(x,y,SIZE,SIZE);
            break;
        case 2:
            ui->train02->setGeometry(x,y,SIZE,SIZE);
            break;
        case 3:
            ui->train03->setGeometry(x,y,SIZE,SIZE);
            break;
        case 4:
            ui->train04->setGeometry(x,y,SIZE,SIZE);
            break;
        case 5:
            ui->train05->setGeometry(x,y,SIZE,SIZE);
            break;
        case 6:
            ui->train06->setGeometry(x,y,SIZE,SIZE);
            break;
        case 7:
            ui->train07->setGeometry(x,y,SIZE,SIZE);
            break;
        default:
            break;
    }
}

