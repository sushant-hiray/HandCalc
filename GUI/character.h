#ifndef CHARACTER_H
#define CHARACTER_H
#include "stroke.h"
#include <vector>
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
class Character
{
public:
    Character();
    void push(Stroke x);//pushes the stroke into the list
    int getno(); //returns no of strokes in that character
    void print(); //print the stroke in form (3,4)
    void ScaleCharacter();
    string preprocessing();
    float getMinx(){
        return orgminx;
    }
    float getMiny(){
        return orgminy;
    }
    float getMaxx(){
        return orgmaxx;
    }
    float getMaxy(){
        return orgmaxy;
    }
    //void setbox(int x1,int x2,int y1,int y2);
    float minx;
    float miny;
    float maxx;
    float maxy;
    int orgminx;
    int orgminy;
    int orgmaxx;
    int orgmaxy;
    void process_character();
    void printScaledSample();
    vector<Pt> sampledChar;
    void reorderStrokes();
    int setPreference();

private:
    vector<Stroke> slist;


};

#endif // CHARACTER_H
