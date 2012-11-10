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
    screen = new splashScreen();
    window = new MainWindow();
    trainingWindow = new MainWindow();
    screen->setParam(window,trainingWindow);

    //
    window->setParameter(1,screen);
   window->MainWindowMaker();
    //
    trainingWindow->setParameter(2,screen);
    //cout<<"reached\n";
    trainingWindow->MainWindowMaker();
    //screen->setParam(window,trainingWindow);
    screen->show();
    return app.exec();
}
