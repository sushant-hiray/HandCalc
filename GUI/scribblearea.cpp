#include <QtGui>
#include <cstdio>
#include <iostream>
#include "scribblearea.h"
using namespace std;


 ScribbleArea::ScribbleArea(QWidget *parent)
     : QWidget(parent)
 {
     setAttribute(Qt::WA_StaticContents);
     modified = false;
     scribbling = false;
     //strokeChanged = false;
     //strokeCount =-1;
     myPenWidth = 5;
     myPenColor = Qt::blue;
     myTimer.start();
 }


 void ScribbleArea::setPenColor(const QColor &newColor)
 {
     myPenColor = newColor;
 }

 void ScribbleArea::setPenWidth(int newWidth)
 {
     myPenWidth = newWidth;
 }

 void ScribbleArea::mousePressEvent(QMouseEvent *event)
 {
     cout<<"pressed \n";
     //return;
     bool lastScribble = scribbling;
     if (event->button() == Qt::LeftButton) {
         lastPoint = event->pos();
         scribbling = true;
         BB.pushStrokePoint(event->x(),event->y(),myTimer.elapsed());
      }
 }

 void ScribbleArea::mouseMoveEvent(QMouseEvent *event)
 {
     if ((event->buttons() & Qt::LeftButton) && scribbling){
         drawLineTo(event->pos());
     }
 }

 void ScribbleArea::mouseReleaseEvent(QMouseEvent *event)
 {
     if (event->button() == Qt::LeftButton && scribbling) {
         BB.setStrokeChange();
         drawLineTo(event->pos());
         scribbling = false;
     }
 }

 void ScribbleArea::paintEvent(QPaintEvent *event)
 {
     QPainter painter(this);
     QRect dirtyRect = event->rect();
     painter.drawImage(dirtyRect, image, dirtyRect);
 }

 void ScribbleArea::resizeEvent(QResizeEvent *event)
 {
     if (width() > image.width() || height() > image.height()) {
         int newWidth = qMax(width() + 128, image.width());
         int newHeight = qMax(height() + 128, image.height());
         resizeImage(&image, QSize(newWidth, newHeight));
         update();
     }
     QWidget::resizeEvent(event);
 }

 void ScribbleArea::clearImage()
  {
      image.fill(qRgb(255, 255, 255));
      modified = true;
      update();

  }

 void ScribbleArea::print(){
     cout<<"Button clicked"<<endl;
 }

 void ScribbleArea::drawLineTo(const QPoint &endPoint)
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
         //strokeList[strokeCount].push(lastPoint.x(),lastPoint.y(),myTimer.elapsed());
         BB.pushStrokePoint(lastPoint.x(),lastPoint.y(),myTimer.elapsed());
         //cout<<"Moving "<<lastPoint.x() <<" "<<lastPoint.y()<<" "<<myTimer.elapsed()<<endl;
     }
 }

 void ScribbleArea::updateRect(){
	 BB.lastCase();


     QPainter painter(&image);

     /*
     for(int i=0;i < strokeList.size();i++){
         painter.drawRect(strokeList[i].getMinx(),strokeList[i].getMiny(),strokeList[i].getMaxx() - strokeList[i].getMinx(),strokeList[i].getMaxy()-strokeList[i].getMiny());

     }
     */
     for(int i=0;i < BB.csize();i++){

         painter.drawRect(BB.cgetMinx(i),BB.cgetMiny(i),BB.cgetMaxx(i) - BB.cgetMinx(i),BB.cgetMaxy(i)-BB.cgetMiny(i));


     }

     update();

 }

 void ScribbleArea::addTrainingData(QString Text){

     char str[100];
     strcpy(str, Text.toAscii().data());
     string s;
     s=str[0];
     BB.changeKey(s);
     BB.TrainingProgram();


     QPainter painter(&image);

     /*
     for(int i=0;i < strokeList.size();i++){
         painter.drawRect(strokeList[i].getMinx(),strokeList[i].getMiny(),strokeList[i].getMaxx() - strokeList[i].getMinx(),strokeList[i].getMaxy()-strokeList[i].getMiny());

     }
     */
     for(int i=0;i < BB.csize();i++){
         painter.drawRect(BB.cgetMinx(i),BB.cgetMiny(i),BB.cgetMaxx(i) - BB.cgetMinx(i),BB.cgetMaxy(i)-BB.cgetMiny(i));

     }

     update();

 }


 void ScribbleArea::resizeImage(QImage *image, const QSize &newSize)
 {
     if (image->size() == newSize)
         return;

     QImage newImage(newSize, QImage::Format_RGB32);
     newImage.fill(qRgb(255, 255, 255));
     QPainter painter(&newImage);
     painter.drawImage(QPoint(0, 0), *image);
     *image = newImage;
 }
