#ifndef STROKE_H
#define STROKE_H
#include <vector>
#include "constants.h"
using namespace std;
struct Point{       //STRUCTURE OF A POINT
    int x;
    int y;
    int time;
};


//STROKE CLASS
class Stroke {
private:
    int strokeid;
    vector<Point> stroke;
    vector<Pt> sampled;     //VECTOR CONTAINS SAMPLED POINTS
    int orientation; //0-horizontal,1-vertical,2-diagonal,3-closed
    float pathlength;       //DETERMINES PATH LENGTH


public:
    bool intocharlist; //whether it is a part of some character in characterList or not USED WHEN BACKSPACE FUNC IS CALLED
    int min_x;
    int max_x;
    int min_y;
    int max_y;
    int directionflag;  //1- correct direction 0-reverse direction

    Stroke(int id);
    void updateStroke();    //UPDATES MIN X,Y AND MAX X,Y AND ORIENTATION OF THE STROKE
    void updateSampleStroke();      //UPDATES MIN X,Y AND MAX X,Y AND ORIENTATION OF THE SAMPLE STROKE
    void push(int x,int y,int time);    //PUSHES A POINT IN stroke VECTOR
    void pushsampled(Pt x);             //PUSHES A POINT IN sample VECTOR
    void findnext(Pt &prev,Pt &next,float dist,int &pointer );  //GIVEN A POINT, NEXT POINT TO BE SAMPLED IN STROKE
    float distance(Pt,Pt);          //RETURNS DISTANCE B/W TWO POINTS
    int abs(int a);                 //RETURNS ABSOLUTE VALUE OF a
    int findOrientation(float delt);//GIVEN A PARAMETER 'delt' FIND ITS ORIENTATION
    void printSample();             //PRINTS THE SAMPLE POINTS
    Pt getPoint(int i);             //RETURNS THE i'th POINT
    void setPoint(Pt point,int i);  //SETS point TO i'th INDEX
    int getsize(){                  //RETURNS SAMPLE SIZE
        return sampled.size();
    }

    //VARIOUS MUATATORS
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
    void addtopath(float x){
        pathlength+=x;
    }


    //VARIOUS ACCESSORS
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

    float getpathlength(){
        return pathlength;
    }

    //SAMPLES THE STROKE
    void sampleStroke();

};

#endif // STROKE_H
