#include "splashscreen.h"

splashScreen::splashScreen(){
    setWindowTitle(tr("SplashScreen"));
    resize(500, 500);
    button = new QPushButton("Calculate",this);
    button->setGeometry(QRect(QPoint(100, 100),QSize(70, 25)));
    button2 = new QPushButton("Train Me",this);
   button2->setGeometry(QRect(QPoint(200, 100),QSize(70, 25)));
    /**/
}

void splashScreen::setParam(MainWindow *a, MainWindow *b){
    window=a;
    trainingWindow=b;
    connect(button,SIGNAL(clicked()),window,SLOT(show()));
        connect(button,SIGNAL(clicked()),this,SLOT(hide()));

        connect(button2,SIGNAL(clicked()),trainingWindow,SLOT(show()));
        connect(button2,SIGNAL(clicked()),this,SLOT(hide()));
}



