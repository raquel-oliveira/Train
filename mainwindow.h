#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "train.h"
#include "server.h"
#include "semaphore.h"
#include <QMainWindow>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updateInterface(int,int,int);
    void receiveMessage(int, int, int);

private:
    Ui::MainWindow *ui;
    vector<Train*> trains;
    vector<QWidget*> label_trainTrack;
    vector<QWidget*> label_train;
    vector<QWidget*> label_numberLaps;
    vector<QWidget*> label_lastTime;
    vector<QWidget*> label_mediaTime;
    Server *server;
    vector<Semaphore> sems;
    void enableTrains(bool);
    void enableTrain(int, bool);
    void initialize();
    void fillCR();
    const void initTrain(int, const int, const int);
};

#endif // MAINWINDOW_H
