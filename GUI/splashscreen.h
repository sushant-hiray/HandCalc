#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QList>
#include <QMainWindow>
#include <QLineEdit>
#include <QtGui>
#include "mainWindow.h"

class MainWindow;
class splashScreen :public QMainWindow
{
    Q_OBJECT

private:
    MainWindow* window;
    MainWindow* trainingWindow;
    QPushButton *button;
    QPushButton *button2;
public:
    splashScreen();
    void setParam(MainWindow* a,MainWindow* b);
};

#endif // SPLASHSCREEN_H
