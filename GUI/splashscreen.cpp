#include "splashscreen.h"

splashScreen::splashScreen(){   //default constructor
    setWindowTitle(tr("SplashScreen"));
    resize(500, 500);
    button = new QPushButton("Calculate",this);
    button->setGeometry(QRect(QPoint(100, 100),QSize(70, 25)));
    button->setStyleSheet(" border: 2px solid #8f8f91; " "background-color: #cbe4fb ;" "border-radius: 6px; " "min-width: 80px ");
    button2 = new QPushButton("Train Me",this);
    button2->setGeometry(QRect(QPoint(200, 100),QSize(70, 25)));
    button2->setStyleSheet(" border: 2px solid #8f8f91; " "background-color: #cbe4fb ;" "border-radius: 6px; " "min-width: 80px ");

}

void splashScreen::setParam(MainWindow *a, MainWindow *b){   //sets parameter to individual windows
    window=a;
    trainingWindow=b;
    connect(button,SIGNAL(clicked()),window,SLOT(show()));
        connect(button,SIGNAL(clicked()),this,SLOT(hide()));

        connect(button2,SIGNAL(clicked()),trainingWindow,SLOT(show()));
        connect(button2,SIGNAL(clicked()),this,SLOT(hide()));
}



