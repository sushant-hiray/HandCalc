#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QTime>
#include <vector>
#include "splice.h"
#include "constants.h"
using namespace std;


 class ScribbleArea : public QWidget
 {
     Q_OBJECT

 public:
    QTime myTimer;   //Timer to generate timestamp for each point
     ScribbleArea(QWidget *parent = 0); //Constructor

     void setPenColor(const QColor &newColor); //sets pen color
     void setPenWidth(int newWidth);          //sets pen width

     bool isModified() const { return modified; }  //checks if the current image is changed
     QColor penColor() const { return myPenColor; }  //returns current pen color
     int penWidth() const { return myPenWidth; }   //returns pen width
     string updateRect();   //returns the string corresponding to the preprocessed data
     void addTrainingData(QString text); //add the new data into the training Data
     void finishTrain(); //finish the training and add all the data from map to database
     void Reset(); //Reset the input screen

 public slots:
      void clearImage();  //Clear the current input screen
      void print(); //debugging
      void undoAction();//Undos the previous action i.e stroke or character


 protected:
     void mousePressEvent(QMouseEvent *event);  //signal emitted on mouse press
     void mouseMoveEvent(QMouseEvent *event);   //signal emitted on mouse movement
     void mouseReleaseEvent(QMouseEvent *event);  //signal emitted when mouse button is released
     void paintEvent(QPaintEvent *event);  //called to show mouse movement output on screen
     void resizeEvent(QResizeEvent *event); // called when screen is resized

 private:
     Splice BB; //New Object for the connector class
     void drawLineTo(const QPoint &endPoint); //called when user moves mouse fast and the pixels recorded are not adjacent
     void resizeImage(QImage *image, const QSize &newSize); //Resizes the screen
     bool modified; //true when mouse position is modified
     bool scribbling; //true when scribbling mode is on
     int myPenWidth; //current pen width
     QColor myPenColor; //Pen color
     QImage image; //Curretn image
     QPoint lastPoint; //Last recorded Point
     QPoint temp; //current point

 };
#endif // SCRIBBLEAREA_H
