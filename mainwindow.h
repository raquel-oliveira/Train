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

private:
    Ui::MainWindow *ui;
    map<Train*, QWidget*, Train::CompLessTrain> trains;
};

#endif // MAINWINDOW_H
