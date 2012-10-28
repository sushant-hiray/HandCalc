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
     strokeChanged = false;
     strokeCount = -1;
     myPenWidth = 5;
     myPenColor = Qt::blue;
     myTimer.start();
     //@@@   for characterlist
     lastpro=0;
     currpos=0;
     yup=10000;
     ydown=0;
     //---@@@
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
     bool lastScribble = scribbling;
     if (event->button() == Qt::LeftButton) {
         lastPoint = event->pos();
         scribbling = true;
         //@@@update ymin ymax
         if(event->y() < yup ) yup=event->y();
         if(event->y() > ydown) ydown=event->y();
         //---@@@
         if(lastScribble != scribbling){
             strokeChanged = true;
             cout<<"stornkjk................"<<strokeCount<<endl;
             strokeCount++;
             Stroke newStroke(strokeCount);
             strokeList.push_back(newStroke);
             //strokeCount++;
             strokeList[strokeCount].push(event->x(),event->y(),myTimer.elapsed());

             if(strokeCount > 0){
                 strokeList[strokeCount - 1].updateStroke();
             }
             cout<<"Stroke is Changed. New Stroke number is "<<strokeCount<<endl;
             cout<<event->x()<<"  "<<event->y()<<" "<<myTimer.elapsed()<<endl;

         }
         else{
             strokeList[strokeCount].push(event->x(),event->y(),myTimer.elapsed());
             cout<<event->x()<<"  "<<event->y()<<" "<<myTimer.elapsed()<<endl;
         }
      }
 }

 void ScribbleArea::mouseMoveEvent(QMouseEvent *event)
 {
     if ((event->buttons() & Qt::LeftButton) && scribbling){
         drawLineTo(event->pos());
         //@@@update ymin ymax
         if(event->y() < yup ) yup=event->y();
         if(event->y() > ydown) ydown=event->y();
         //---@@@
     }
 }

 void ScribbleArea::mouseReleaseEvent(QMouseEvent *event)
 {
     if (event->button() == Qt::LeftButton && scribbling) {
         drawLineTo(event->pos());
         scribbling = false;
         cout<<event->x()<<"  "<<event->y()<<" "<<myTimer.elapsed()<<endl;
         //@@@
          strokeList[strokeCount].updateStroke();
         currpos=strokeCount; //cout<<"strokecoutn is............................."<<strokeCount<<endl;
         charprocess();
         //---@@@
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
         strokeList[strokeCount].push(lastPoint.x(),lastPoint.y(),myTimer.elapsed());
         cout<<"Moving "<<lastPoint.x() <<" "<<lastPoint.y()<<" "<<myTimer.elapsed()<<endl;
     }
 }

 void ScribbleArea::updateRect(){
     //@@@ do the end case of char list
     if(lastpro>currpos) ;//cout<<"WE are done ^^^^^^^^^^^^^^^^^^^^^^^^\n";//we are done as last go coupled with sec-last
     else{
         Character temp;
         temp.push(strokeList[strokeList.size()-1]);
         characterList.push_back(temp);
     }
     //---@@@ END CASE HANDLED

     strokeList[strokeList.size()-1].updateStroke();
     cout<<"Hello.....now printing about characters formed \n no of characters ="<< characterList.size();
     for(int i=0;i<characterList.size();i++){
         characterList[i].print();
     }

     cout<<"\nNumber of strokes identified "<<strokeList.size()<<endl;
     //@@@

     //---@@@


     QPainter painter(&image);


     /*
     for(int i=0;i < strokeList.size();i++){
         painter.drawRect(strokeList[i].getMinx(),strokeList[i].getMiny(),strokeList[i].getMaxx() - strokeList[i].getMinx(),strokeList[i].getMaxy()-strokeList[i].getMiny());

     }
     */
     for(int i=0;i < characterList.size();i++){
         painter.drawRect(characterList[i].getMinx(),characterList[i].getMiny(),characterList[i].getMaxx() - characterList[i].getMinx(),characterList[i].getMaxy()-characterList[i].getMiny());

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

 vector<Stroke> ScribbleArea::getStrokeList(){
     return strokeList;
 }

//##############################################################################################################################
 //@@@
 int ScribbleArea::judge(int i,int j){
     float delta=(ydown-yup)*(0.1);
     //cout<<"DELATA............"<<delta<<" "<<ydown<< " "<<yup<<"  VV.."<<i<<" "<<j<<strokeList[j].getMinx()<<" "<<strokeList[i].getMaxx()<<endl;
     if (delta < strokeList[i].getMinx()-strokeList[j].getMaxx()){
         //stroke boxes are seperated by more than delta
         return 1; //means 1st stroke can be treated as character
     }
     else if(delta < strokeList[j].getMinx()-strokeList[i].getMaxx()){
         return 2;
     }
     else return 0; //means they belong to same character
 }

void ScribbleArea::charprocess(){
    //cout<<"processing now................"<<lastpro<< "    "<<currpos;
    int result=judge(lastpro,currpos);
    if(lastpro==currpos); //do nothing because only one stroke in hand so wait for next stroke
    else if(result==0){ //same character
        Character temp;
        temp.push(strokeList[lastpro]);
        temp.push(strokeList[currpos]);
        lastpro=currpos+1;
        characterList.push_back(temp);
    }

    else if(result==2) { //make lastpro a character and move lastpro pointr to currpos
        //cout<<"########   into res 2  "<<strokeList[lastpro].getid()<<endl;
        Character temp;
        temp.push(strokeList[lastpro]);
         characterList.push_back(temp);
         //cout<<"printing the first character "<<characterList.size()<<"  ";characterList[0].print();cout<<endl;

         lastpro++;
    }
    else if(result==1){ //make currpro a character
                        //wont happen as we write left to right
                        //and if diff chars then lastpro becomes char first
        Character temp;
        lastpro++;
        temp.push(strokeList[currpos]);
         characterList.push_back(temp);
    }
}

//---@@@
