#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "train.h"
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
    void enableTrains(bool b);
    void enableTrain(int id, bool b);
    void initialize();

private:
    Ui::MainWindow *ui;
    vector<Train*> trains;
    vector<QWidget*> label_trainTrack;
    vector<QWidget*> label_train;
    vector<QWidget*> label_numberLaps;
    vector<QWidget*> label_lastTime;
};

#endif // MAINWINDOW_H
