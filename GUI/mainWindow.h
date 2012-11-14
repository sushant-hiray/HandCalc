#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QList>
#include <QMainWindow>
#include <QLineEdit>
#include "splashscreen.h"
#include "ArithmeticExpression.h"
 class ScribbleArea;
 class splashScreen;
 class MainWindow : public QMainWindow
 {
     Q_OBJECT

 public:
     MainWindow();
     void MainWindowMaker();
     void setParameter(int a,splashScreen* parent);
     QLineEdit* output;


 private slots:
     void penColor();
     void penWidth();
     void about();
     void credit();
     void drawRect();
     void addTrainingData();
     void Reset();
     void finishTraining();
     void undoAction();

 private:
     int val;
     splashScreen* paa;
     QPushButton *back;
     QPushButton *undo; //in the evaluate screen
     void createActions();
     void createMenus();
      int resetflag;
      QMenu *optionMenu;
      QMenu *helpMenu;
      QAction *penColorAct;
      QAction *penWidthAct;
      QAction *clearScreenAct;
      QAction *aboutAct;
      QAction *creditsAct;

     QLineEdit *traininginput ;
     ScribbleArea *scribbleArea;
 };
#endif // MAINWINDOW_H
