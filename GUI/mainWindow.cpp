#include <QtGui>
#include <QMenu>
#include "mainWindow.h"
#include "scribblearea.h"
#include <iostream>
#include<sstream>
using namespace std;

MainWindow::MainWindow(){
    scribbleArea = new ScribbleArea;
    setCentralWidget(scribbleArea);
    createActions();
    createMenus();
    resetflag=0;

    setWindowTitle(tr("Scribble"));
    resize(500, 500);
}

void  MainWindow::MainWindowMaker()
 {
    QHBoxLayout *layout = new QHBoxLayout;
     if(val==1){ //make the evaluate screen

         QPushButton *button = new QPushButton();
         button->setFixedWidth(70);
         button->setFixedHeight(70);
         QIcon icon("Evaluate.jpg");
         button->setIconSize((QSize(70,70)));
         button->setIcon(icon);

         QPushButton *button3 = new QPushButton();
         button3->setFixedWidth(70);
         button3->setFixedHeight(70);
         QIcon icon3("reset.jpg");
         button3->setIconSize((QSize(70,70)));
         button3->setIcon(icon3);

         output = new QLineEdit;

         back = new QPushButton();
         back->setFixedWidth(70);
         back->setFixedHeight(70);
         QIcon iconB("back.gif");
         back->setIconSize((QSize(70,70)));
         back->setIcon(iconB);

         undo=new QPushButton();
         undo->setFixedWidth(70);
         undo->setFixedHeight(70);
         QIcon iconU("undo.png");
         undo->setIconSize((QSize(70,70)));
         undo->setIcon(iconU);


         layout->addWidget(button);
         layout->addWidget(button3);
         layout->addWidget(back);
         layout->addWidget(undo);
         layout->addWidget(output);

         //scribbleArea->setLayout(layout);
         connect(button,SIGNAL(clicked()),this,SLOT(drawRect()));
         connect(button3,SIGNAL(clicked()),this,SLOT(Reset()));
         connect(undo,SIGNAL(clicked()),this,SLOT(undoAction()));
     }
     else {

         QPushButton *button3 = new QPushButton("Reset");
         button3->setFixedWidth(70);
         button3->setFixedHeight(25);

         QPushButton *button2 = new QPushButton("Train Data");
         button2->setFixedWidth(80);
         button2->setFixedHeight(25);

         QPushButton *finish = new QPushButton("Finish Training");
         finish->setFixedWidth(110);
         finish->setFixedHeight(25);

         back = new QPushButton("Back");
         back->setFixedWidth(70);
         back->setFixedHeight(25);

        // QHBoxLayout *layout = new QHBoxLayout;
         layout->addWidget(button2);
         layout->addWidget(button3);
         layout->addWidget(finish);
         layout->addWidget(back);

         traininginput = new QLineEdit;
         layout->addWidget(traininginput);
         connect(button2,SIGNAL(clicked()),this,SLOT(addTrainingData()));
         connect(button3,SIGNAL(clicked()),this,SLOT(Reset()));
         connect(finish,SIGNAL(clicked()),this,SLOT(finishTraining()));
     }


      connect(back,SIGNAL(clicked()),this,SLOT(hide()));
       connect(back,SIGNAL(clicked()),paa,SLOT(show()));
    // QHBoxLayout *layout1 = new QHBoxLayout;
     //scribbleArea->setLayout(layout1);
     scribbleArea->setLayout(layout);

}

 void MainWindow::setParameter(int a, splashScreen *parent){
     val=a;
     paa=parent;
     //
     //
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
     string out;
     out=scribbleArea->updateRect();

    //if(out=="1+2*3"){cout<<"matching \n";}
    cout<<"printing the ecpression " ;
     ArithmeticExpression a;
     float ans;
     ans=a.evaluate(out);
     cout<<"printing the ecpression " ;a.printExpression();
     ostringstream buffer;
     buffer<<ans;
     string answer=buffer.str();
     out.append(" = ");
     out.append(answer);

     QString qstr(out.c_str());
     output->setText(qstr);
 }

 void MainWindow::undoAction(){
     scribbleArea->undoAction();
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
     scribbleArea->Reset();
     scribbleArea->clearImage();
     output->setText("");

     resetflag=0;
 }
