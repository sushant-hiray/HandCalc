#include <QtGui>
#include <QMenu>
#include "mainWindow.h"
#include "scribblearea.h"
#include <iostream>

using namespace std;
 MainWindow::MainWindow()
 {
     scribbleArea = new ScribbleArea;
     setCentralWidget(scribbleArea);
     createActions();
     createMenus();
     resetflag=0;

     setWindowTitle(tr("Scribble"));
     resize(500, 500);
     QPushButton *button = new QPushButton("Evaluate");
     button->setFixedWidth(70);
     button->setFixedHeight(25);
     QPushButton *button2 = new QPushButton("Train Data");
     button2->setFixedWidth(80);
     button2->setFixedHeight(25);
     QPushButton *button3 = new QPushButton("Reset");
     button3->setFixedWidth(70);
     button3->setFixedHeight(25);
     QPushButton *finish = new QPushButton("Finish Training");
     finish->setFixedWidth(70);
     finish->setFixedHeight(25);
     QHBoxLayout *layout = new QHBoxLayout;
     layout->addWidget(button);
     layout->addWidget(button2);
     layout->addWidget(button3);
     layout->addWidget(finish);
     traininginput = new QLineEdit;
     layout->addWidget(traininginput);
     scribbleArea->setLayout(layout);
     connect(button,SIGNAL(clicked()),this,SLOT(drawRect()));
     connect(button2,SIGNAL(clicked()),this,SLOT(addTrainingData()));
     connect(button3,SIGNAL(clicked()),this,SLOT(Reset()));
     connect(finish,SIGNAL(clicked()),this,SLOT(finishTraining()));

 }
 void MainWindow::createMenus()
  {

      optionMenu=menuBar()->addMenu(tr("&Options"));
      helpMenu=menuBar()->addMenu(tr("&Help"));
      optionMenu->addAction(penColorAct);
      optionMenu->addAction(penWidthAct);
      optionMenu->addAction(clearScreenAct);
      helpMenu->addAction(aboutAct);
      helpMenu->addAction(creditsAct);

 }

 void MainWindow::createActions()
  {
     penColorAct = new QAction(tr("&Pen Color..."), this);
     connect(penColorAct, SIGNAL(triggered()), this, SLOT(penColor()));

     penWidthAct = new QAction(tr("Pen &Width..."), this);
     connect(penWidthAct, SIGNAL(triggered()), this, SLOT(penWidth()));

     clearScreenAct = new QAction(tr("&Clear Screen"), this);
     clearScreenAct->setShortcut(tr("Ctrl+L"));
     connect(clearScreenAct, SIGNAL(triggered()),
                  scribbleArea, SLOT(clearImage()));

     aboutAct = new QAction(tr("&About"), this);
     connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

     creditsAct = new QAction(tr("&Credits"), this);
     connect(creditsAct, SIGNAL(triggered()), this, SLOT(credit()));
 }

 void MainWindow::penColor()
 {
     QColor newColor = QColorDialog::getColor(scribbleArea->penColor());
     if (newColor.isValid())
         scribbleArea->setPenColor(newColor);
 }

 void MainWindow::drawRect(){
     scribbleArea->updateRect();

 }

 void MainWindow::addTrainingData(){
     if(resetflag==0){
        scribbleArea->addTrainingData(traininginput->text());
        resetflag=1;
     }
     else{
         return;
     }
 }

 void MainWindow::finishTraining(){
     scribbleArea->finishTrain();
 }


 void MainWindow::penWidth()
 {
     bool ok;
     int newWidth = QInputDialog::getInteger(this, tr("Scribble"),
                                             tr("Select pen width:"),
                                             scribbleArea->penWidth(),
                                             1, 50, 1, &ok);
     if (ok)
         scribbleArea->setPenWidth(newWidth);
 }


 void MainWindow::about()
 {
     QMessageBox::about(this, tr("About Scribble"),
             tr("<p>The <b>Scribble</b> is the main scribbling pad "
                "where you can just input expressions values "
                "or rather just scribble for fun!! :) "

                "It can also be used to paint stuff!!"
                "We sincerely hope u enjoy your time on Scribble!!</p>"
                ));
 }


 void MainWindow::credit()
 {
     QMessageBox msgBox;
     msgBox.setText(
             tr("<p>The <b>Handy_Calc</b> is a "
                "product of IITB Grads<br>"
                "Namely:Sushant , Ashish and Sanchit <br>"
                "To know more about us "
                "just log on to www.cse.iitb.ac.in/people/Btech2 <br>"
                "We are also available for being hired!! :P </p>"
                ));
     msgBox.exec();
 }

 void MainWindow::Reset(){
     scribbleArea->clearImage();
     resetflag=0;
 }
