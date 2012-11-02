#ifndef CHARACTER_H
#define CHARACTER_H
#include "stroke.h"
#include <vector>
#include <iostream>
#include "constants.h"
using namespace std;
class Character
{
public:
    Character();
    void push(Stroke x);//pushes the stroke into the list
    int getno(); //returns no of strokes in that character
    void print(); //print the stroke in form (3,4)
    int getMinx(){
        return minx;
    }
    int getMiny(){
        return miny;
    }
    int getMaxx(){
        return maxx;
    }
    int getMaxy(){
        return maxy;
    }
    //void setbox(int x1,int x2,int y1,int y2);
    void process_character();

private:
    vector<Stroke> slist;
    vector<Pt> sampledChar;
    int minx;
    int miny;
    int maxx;
    int maxy;
};

#endif // CHARACTER_H
