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
    int getMinx(){
        return orgminx;
    }
    int getMiny(){
        return orgminy;
    }
    int getMaxx(){
        return orgmaxx;
    }
    int getMaxy(){
        return orgmaxy;
    }
    //void setbox(int x1,int x2,int y1,int y2);
    void process_character();
    void printScaledSample();
    vector<Pt> sampledChar;
    void reorderStrokes();
    int setPreference();

private:
    vector<Stroke> slist;

    int minx;
    int miny;
    int maxx;
    int maxy;
    int orgminx;
    int orgminy;
    int orgmaxx;
    int orgmaxy;
};

#endif // CHARACTER_H
