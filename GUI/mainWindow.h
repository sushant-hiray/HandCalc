#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QList>
 #include <QMainWindow>

 class ScribbleArea;

 class MainWindow : public QMainWindow
 {
     Q_OBJECT

 public:
     MainWindow();

 private slots:
     void penColor();
     void penWidth();
     void about();

 private:
     void createActions();
     void createMenus();

      QMenu *optionMenu;
      QMenu *helpMenu;
      QAction *penColorAct;
      QAction *penWidthAct;
      QAction *clearScreenAct;
      QAction *aboutAct;

     ScribbleArea *scribbleArea;
 };
#endif // MAINWINDOW_H
