#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H

#include <QColor>
 #include <QImage>
 #include <QPoint>
 #include <QWidget>

 class ScribbleArea : public QWidget
 {
     Q_OBJECT

 public:
     ScribbleArea(QWidget *parent = 0);

     void setPenColor(const QColor &newColor);
     void setPenWidth(int newWidth);

     bool isModified() const { return modified; }
     QColor penColor() const { return myPenColor; }
     int penWidth() const { return myPenWidth; }


 protected:
     void mousePressEvent(QMouseEvent *event);
     void mouseMoveEvent(QMouseEvent *event);
     void mouseReleaseEvent(QMouseEvent *event);
     void paintEvent(QPaintEvent *event);
     void resizeEvent(QResizeEvent *event);

 private:
     void drawLineTo(const QPoint &endPoint);
     void resizeImage(QImage *image, const QSize &newSize);

     bool modified;
     bool scribbling;
     int myPenWidth;
     QColor myPenColor;
     QImage image;
     QPoint lastPoint;
     QPoint temp;
 };
#endif // SCRIBBLEAREA_H
