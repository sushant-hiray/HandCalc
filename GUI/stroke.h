#ifndef STROKE_H
#define STROKE_H
#include <vector>
#include "constants.h"
using namespace std;
struct Point{
    int x;
    int y;
    int time;
};

struct Pt{
    float x;
    float y;
};

class Stroke {
private:
    int strokeid;
    vector<Point> stroke;
    vector<Pt> sampled;
    int min_x;
    int max_x;
    int min_y;
    int max_y;
    int orientation; //0-horizontal,1-vertical,2-diagonal,3-closed
    float pathlength;

public:
    Stroke(int id);
    void updateStroke();
    void push(int x,int y,int time);
    void pushsampled(Pt x);
    void findnext(Pt &prev,Pt &next,float dist,int &pointer );
    float distance(Pt,Pt);
    int abs(int a);
    int findOrientation(float delta);
    void printSample();
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
    void addtopath(float x){
        pathlength+=x;
    }
    float getpathlength(){
        return pathlength;
    }
    void sampleStroke();

};

#endif // STROKE_H
