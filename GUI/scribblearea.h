#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QTime>
#include <vector>
#include "stroke.h"
#include "character.h"
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
     vector<Stroke> getStrokeList();
     void updateRect();

 public slots:
      void clearImage();
      void print();


 protected:
     void mousePressEvent(QMouseEvent *event);
     void mouseMoveEvent(QMouseEvent *event);
     void mouseReleaseEvent(QMouseEvent *event);
     void paintEvent(QPaintEvent *event);
     void resizeEvent(QResizeEvent *event);

 private:
     void drawLineTo(const QPoint &endPoint);
     void resizeImage(QImage *image, const QSize &newSize);
     vector<Stroke> strokeList;
     bool modified;
     bool scribbling;
     bool strokeChanged;
     int myPenWidth;
     int strokeCount;
     QColor myPenColor;
     QImage image;
     QPoint lastPoint;
     QPoint temp;
     //for characterlist
     vector<Character> characterList;
     int lastpro; //last stroke passed
     int currpos; //currpos
     int yup;
     int ydown;
     int judge(int i,int j);// judges whether the two strokes i and j in strokelist belong to same character
     void charprocess();//judges and if allowed pushes a new character into the characterlist called in mouserelease event
     //NOTE will miss the last stroke if second last stroke already taken into a character so process the last stroke
     //take care of this when called evaluate .... if lastpos>curpos then last stroke ok else add last stroke as a character

 };
#endif // SCRIBBLEAREA_H
