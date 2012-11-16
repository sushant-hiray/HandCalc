#include <QtGui>
#include <cstdio>
#include <iostream>
#include "scribblearea.h"
using namespace std;


 ScribbleArea::ScribbleArea(QWidget *parent)  //default constructor
     : QWidget(parent)
 {
     setAttribute(Qt::WA_StaticContents);
     modified = false;
     scribbling = false;
     myPenWidth = 5;
     myPenColor = Qt::blue;
     myTimer.start();
 }


 void ScribbleArea::setPenColor(const QColor &newColor)   //sets pen color
 {
     myPenColor = newColor;
 }

 void ScribbleArea::setPenWidth(int newWidth)   //sets pen width
 {
     myPenWidth = newWidth;
 }

 void ScribbleArea::mousePressEvent(QMouseEvent *event)   //handles mouse press event
 {
     bool lastScribble = scribbling;
     if (event->button() == Qt::LeftButton) {  //if left button is pressed then proceed
         lastPoint = event->pos();
         scribbling = true;
         BB.pushStrokePoint(event->x(),event->y(),myTimer.elapsed());
      }
 }

 void ScribbleArea::mouseMoveEvent(QMouseEvent *event)   //handles mouse move event
 {
     if ((event->buttons() & Qt::LeftButton) && scribbling){
         drawLineTo(event->pos());
     }
 }

 void ScribbleArea::mouseReleaseEvent(QMouseEvent *event)   //handles mouse release event
 {
     if (event->button() == Qt::LeftButton && scribbling) {
         BB.setStrokeChange();
         drawLineTo(event->pos());
         scribbling = false;
     }
 }

 void ScribbleArea::paintEvent(QPaintEvent *event)     //handles paint event
 {
     QPainter painter(this);
     QRect dirtyRect = event->rect();
     painter.drawImage(dirtyRect, image, dirtyRect);
 }

 void ScribbleArea::resizeEvent(QResizeEvent *event)   //handles window resize event
 {
     if (width() > image.width() || height() > image.height()) {
         int newWidth = qMax(width() + 128, image.width());
         int newHeight = qMax(height() + 128, image.height());
         resizeImage(&image, QSize(newWidth, newHeight));
         update();
     }
     QWidget::resizeEvent(event);
 }

 void ScribbleArea::clearImage()  //clear image handler
  {
      image.fill(qRgb(255, 255, 255));
      modified = true;
      update();

  }

 void ScribbleArea::print(){
     cout<<"Button clicked"<<endl;
 }

 void ScribbleArea::drawLineTo(const QPoint &endPoint) //is called if the user input speed is fast and two pixels detected by the Qt arent consecutive
 {
     QPainter painter(&image);
     painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                         Qt::RoundJoin));
     painter.drawLine(lastPoint, endPoint);
     modified = true;

     int rad = (myPenWidth / 2) + 2;
     update(QRect(lastPoint, endPoint).normalized()
                                      .adjusted(-rad, -rad, +rad, +rad));
     temp=lastPoint;
     lastPoint = endPoint;
     if(lastPoint!=temp)
     {
         BB.pushStrokePoint(lastPoint.x(),lastPoint.y(),myTimer.elapsed());
     }
 }

 string ScribbleArea::updateRect(){   //draws bounding box among all characters
     string out=BB.lastCase();


     QPainter painter(&image);

     for(int i=0;i < BB.csize();i++){

         painter.drawRect(BB.cgetMinx(i),BB.cgetMiny(i),BB.cgetMaxx(i) - BB.cgetMinx(i),BB.cgetMaxy(i)-BB.cgetMiny(i));


     }

     update();
     return out;


 }

 void ScribbleArea::addTrainingData(QString Text){  //add new training data

     char str[100];
     strcpy(str, Text.toAscii().data());
     string s;
     s=str[0];
     BB.changeKey(s);
     BB.TrainingProgram();


     QPainter painter(&image);

       for(int i=0;i < BB.csize();i++){
         painter.drawRect(BB.cgetMinx(i),BB.cgetMiny(i),BB.cgetMaxx(i) - BB.cgetMinx(i),BB.cgetMaxy(i)-BB.cgetMiny(i));

     }

     update();  //updates the canvas

 }


 void ScribbleArea::resizeImage(QImage *image, const QSize &newSize)   //resizes the image
 {
     if (image->size() == newSize)
         return;

     QImage newImage(newSize, QImage::Format_RGB32);
     newImage.fill(qRgb(255, 255, 255));
     QPainter painter(&newImage);
     painter.drawImage(QPoint(0, 0), *image);
     *image = newImage;
 }

 void ScribbleArea::finishTrain(){   //calls the splice to fininsh rh training
     BB.writeMap();
 }

 void ScribbleArea::Reset(){   //Reset the input canvas
     BB.ResetData();
 }

 void  ScribbleArea::undoAction(){   //undo the previous character from the canvas
     myRect delArea=  BB.backSpace();
     QPainter painter(&image);
     painter.setPen(QPen(Qt::white, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                         Qt::RoundJoin));
     painter.setBrush(QBrush( Qt::white,Qt::SolidPattern));
     painter.drawRect(delArea.x1,delArea.y1,delArea.x2-delArea.x1,delArea.y2-delArea.y1);
     update();
 }
