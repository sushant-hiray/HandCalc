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
    QTime myTimer;
     ScribbleArea(QWidget *parent = 0);

     void setPenColor(const QColor &newColor);
     void setPenWidth(int newWidth);

     bool isModified() const { return modified; }
     QColor penColor() const { return myPenColor; }
     int penWidth() const { return myPenWidth; }
     //vector<Stroke> getStrokeList();
     string updateRect();
     void addTrainingData(QString text);
     void finishTrain();
     void Reset();

 public slots:
      void clearImage();
      void print();
      void undoAction();


 protected:
     void mousePressEvent(QMouseEvent *event);
     void mouseMoveEvent(QMouseEvent *event);
     void mouseReleaseEvent(QMouseEvent *event);
     void paintEvent(QPaintEvent *event);
     void resizeEvent(QResizeEvent *event);

 private:
     Splice BB;
     void drawLineTo(const QPoint &endPoint);
     void resizeImage(QImage *image, const QSize &newSize);
     //vector<Stroke> strokeList;
     bool modified;
     bool scribbling;
    // bool strokeChanged;
     int myPenWidth;
     //int strokeCount;
     QColor myPenColor;
     QImage image;
     QPoint lastPoint;
     QPoint temp;

 };
#endif // SCRIBBLEAREA_H
