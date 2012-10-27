#ifndef STROKE_H
#define STROKE_H
#include <vector>
using namespace std;
struct Point{
    int x;
    int y;
    int time;
};

class Stroke {
private:
    int strokeid;
    vector<Point> stroke;
    int min_x;
    int max_x;
    int min_y;
    int max_y;
    int orientation; //0-horizontal,1-vertical,2-diagonal,3-closed

public:
    Stroke(int id);
    void updateStroke();
    void push(int x,int y,int time);
    int abs(int a);
    int findOrientation(float delta);
    void setMinx(int x){
        min_x=x;
    }
    void setMiny(int y){
        min_y=y;
    }
    void setMaxx(int x){
        max_x=x;
    }
    void setMaxy(int y){
        max_y=y;
    }
    void setOrientation(int o){
        orientation=o;

    }
    int getMinx(){
        return min_x;
    }
    int getMiny(){
        return min_y;
    }
    int getMaxx(){
        return max_x;
    }
    int getMaxy(){
        return max_y;
    }
    int getOrientation(){
        return orientation;
    }
    int getid(){
        return strokeid;
    }
};

#endif // STROKE_H
