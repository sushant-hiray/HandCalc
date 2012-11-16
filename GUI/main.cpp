#include <QApplication>
#include "mainWindow.h"
#include "scribblearea.h"
#include "splashscreen.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    splashScreen* screen;
    MainWindow* window;
    MainWindow* trainingWindow;
    screen = new splashScreen(); //create a new splashscreen
    window = new MainWindow();   //create 2 window instances corresponding to training and evaluation
    trainingWindow = new MainWindow();
    screen->setParam(window,trainingWindow);
    window->setParameter(1,screen);
    window->MainWindowMaker();
    trainingWindow->setParameter(2,screen);
    trainingWindow->MainWindowMaker();
    screen->show();
    return app.exec();
}
