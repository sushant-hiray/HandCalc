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

 private:
     void createActions();
     void createMenus();

      QMenu *optionMenu;
      QAction *penColorAct;
      QAction *penWidthAct;

     ScribbleArea *scribbleArea;
 };
#endif // MAINWINDOW_H
