#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QList>
#include <QMainWindow>
#include <QLineEdit>
#include <QtGui>
#include "mainWindow.h"

class MainWindow;
class splashScreen :public QMainWindow      //class derived from mainWindow
{
    Q_OBJECT

private:
    MainWindow* window;
    MainWindow* trainingWindow; //shows training window
    QPushButton *button;        //Button to ENTER EVALUATE WINDOW
    QPushButton *button2;       //ENTER IN TRAINING WINDOW
public:
    splashScreen();     //CONSTRUCTOR
    void setParam(MainWindow* a,MainWindow* b);     //PARAMERTER IS SET TO ENTER IN DESIRED WINDOW
};

#endif // SPLASHSCREEN_H
