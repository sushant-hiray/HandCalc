#include <QtGui>
#include <QMenu>
 #include "mainWindow.h"
 #include "scribblearea.h"

 MainWindow::MainWindow()
 {
     scribbleArea = new ScribbleArea;
     setCentralWidget(scribbleArea);
     createActions();
     createMenus();

     setWindowTitle(tr("Scribble"));
     resize(500, 500);
 }

 void MainWindow::createMenus()
  {

      optionMenu=menuBar()->addMenu(tr("&Options"));
      optionMenu->addAction(penColorAct);
      optionMenu->addAction(penWidthAct);
 }

 void MainWindow::createActions()
  {
     penColorAct = new QAction(tr("&Pen Color..."), this);
     connect(penColorAct, SIGNAL(triggered()), this, SLOT(penColor()));

     penWidthAct = new QAction(tr("Pen &Width..."), this);
     connect(penWidthAct, SIGNAL(triggered()), this, SLOT(penWidth()));
 }

 void MainWindow::penColor()
 {
     QColor newColor = QColorDialog::getColor(scribbleArea->penColor());
     if (newColor.isValid())
         scribbleArea->setPenColor(newColor);
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

