#include "stroke.h"
#include "math.h"
#include <iostream>
#include <cstdio>
#include "qpainter.h"
using namespace std;
Stroke::Stroke(int id){
    strokeid=id;
    pathlength=0;
}

void Stroke::updateStroke(){
    int tempminx=stroke[0].x;
    int tempminy=stroke[0].y;
    int tempmaxx=stroke[0].x;
    int tempmaxy=stroke[0].y;
    for (unsigned int i=1;i<stroke.size();i++){
        if(stroke[i].x < tempminx){
            tempminx=stroke[i].x;
        }
        if(stroke[i].y < tempminy){
            tempminy=stroke[i].y;
        }
        if(stroke[i].x > tempmaxx){
            tempmaxx=stroke[i].x;
        }
        if(stroke[i].y > tempmaxy){
            tempmaxy=stroke[i].y;
        }
    }
    min_x=tempminx;
    min_y=tempminy;
    max_x=tempmaxx;
    max_y=tempmaxy;
    orientation=findOrientation(0.37);
    cout<<"Minimum x is "<<min_x<<endl;
    cout<<"Maximum x is "<<max_x<<endl;
    cout<<"Minimum y is "<<min_y<<endl;
    cout<<"Maximum y is "<<max_y<<endl;
    cout<<"Orientation is "<<orientation<<endl;
}

void Stroke::push(int x, int y, int time){
    Point temp;
    temp.x=x;
    temp.y=y;
    temp.time=time;
    stroke.push_back(temp);
}

int Stroke::abs(int a){
    if(a>0){
        return a;
    }
    else{
        return -a;
    }
}

int Stroke::findOrientation(float delta){
    int tempx=abs(stroke[0].x-stroke[stroke.size()-1].x);
    int tempy=abs(stroke[0].y-stroke[stroke.size()-1].y);
    float diagonal=sqrt((max_x-min_x)^2 + (max_y-min_y)^2);
    float checkx=tempx/diagonal;
    float checky=tempy/diagonal;
    if(checkx > delta && checky < delta ){
        return 0;
    }
    else if(checkx < delta && checky < delta){
        return 3;
    }
    else if(checkx < delta && checky > delta){
        return 1;
    }
    else{
        return 2;
    }

}

float Stroke::distance(Pt a,Pt b){
    return sqrt(pow(b.x-a.x,2)+pow(b.y-a.y,2));
}

void Stroke::findnext(Pt &prev,Pt &next,float dist,int &pointer ){
    float tempdist=distance(next,prev);
    Pt newpoint;
    if(tempdist>dist){
        newpoint.x= (prev.x*(tempdist-dist) + next.x*dist)/tempdist;
        newpoint.y= (prev.y*(tempdist-dist) + next.y*dist)/tempdist;
        pushsampled(newpoint);
        prev=newpoint;
        return;
    }
    else{
        pointer++;
        if(pointer>=stroke.size()){
            pushsampled(next);
            return;
        }
        newpoint.x=stroke[pointer].x;
        newpoint.y=stroke[pointer].y;
            findnext(next,newpoint,tempdist-dist,pointer);
    }
}

void Stroke::pushsampled(Pt a){
    sampled.push_back(a);
}

void Stroke::sampleStroke(){
    float step=pathlength/SR;
    //float currlen=0;
    //int prevx,prevy,
    int pointer=0;
    Pt prev,next;
    prev.x=stroke[0].x; prev.y = stroke[0].y;
    next.x=stroke[1].y; next.y = stroke[1].y;
    for(int i=0;i<SR; i++){
        //int prevx=stroke[pointer].x; int prevy=stroke[pointer].y;
        next.x=stroke[pointer].x;next.y=stroke[pointer].y;
        findnext(prev,next,step,pointer);
    }
}
