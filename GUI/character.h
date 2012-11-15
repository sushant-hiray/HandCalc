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
    void ScaleCharacter();//scales the character to convert it into 1x1 square
    string preprocessing();  //returns the feature type of character after preprocessing.
    float getMinx(){       //returns the minimum x coordinate of character
        return orgminx;
    }
    float getMiny(){      //returns the minimum y coordinate of character
        return orgminy;
    }
    float getMaxx(){     //returns the maximum x coordinate of character
        return orgmaxx;
    }
    float getMaxy(){    //returns the maximum y coordinate of character
        return orgmaxy;
    }
    //void setbox(int x1,int x2,int y1,int y2);
    float minx;       //minimum x of stroke
    float miny;       //minimum y of stroke
    float maxx;       //maximum x of stroke
    float maxy;       //maximum y of stroke
    int orgminx;      //minimum x before sampling
    int orgminy;      //minimum y before sampling
    int orgmaxx;      //maximum x before sampling
    int orgmaxy;      //maximum x before sampling
    void process_character(); //processes the character
    void printScaledSample(); //used for debugging
    vector<Pt> sampledChar;   // sampled character
    void reorderStrokes();   //reorder strokes according to theiir orientation
    int setPreference();    //prefer the strokes

private:
    vector<Stroke> slist;   //stroke list of character


};

#endif // CHARACTER_H
