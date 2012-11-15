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
     void MainWindowMaker(); //creates an instance of MainWindow
     void setParameter(int a,splashScreen* parent);  //sets parameter to create required window
     QLineEdit* output;


 private slots:
     void penColor();  //slot to change the color : required to call the color picker instance
     void penWidth();  //slot to change the color : required to call the color picker instance
     void about();     //slot to show about dialog box
     void credit();    //slot to show credit dialog box
     void drawRect();  //slot to draw rectangle
     void addTrainingData();  //slot to add the new stroke to training data
     void Reset();       //slot to reset the input box
     void finishTraining();  //slot to add all new data acquired into the database and stop further training
     void undoAction();  //removes the last stroke/character added by the user

 private:
     int val;   //index of the current window
     splashScreen* paa; //parent splashscreen
     QPushButton *back; //back button
     QPushButton *undo; //in the evaluate screen
     void createActions();  //creates instanses of menu actions
     void createMenus();   //creates menu
      int resetflag;   //changes its value when reset button is pushed
      QMenu *optionMenu; //Menu of options
      QMenu *helpMenu;   //Help Menu
      QAction *penColorAct; //Action to change Pen Color
      QAction *penWidthAct; //Action to change Pen Width
      QAction *clearScreenAct; //Actions to clear the input screen
      QAction *aboutAct; //Action for about menu
      QAction *creditsAct; //Action for credits menu

     QLineEdit *traininginput ;  //Training input screen
     ScribbleArea *scribbleArea;  //Pointer to scribble Area object
 };
#endif // MAINWINDOW_H
