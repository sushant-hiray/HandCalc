#include "character.h"
using namespace std;

Character::Character()
{
}
int Character::getno(){
    return slist.size();
}

void Character::print(){
    cout<<"(";
    for (int i=0;i<slist.size();i++){
        cout<<slist[i].getid()<<",";
    }
    cout<<") ";
}

void Character::push(Stroke x){
    if(slist.empty()) {minx=x.getMinx();miny=x.getMiny();maxx=x.getMaxx();maxy=x.getMaxy();}
    else{
        if(x.getMinx()<minx) minx=x.getMinx();
        if(x.getMiny()<miny) miny=x.getMiny();
        if(x.getMaxx()>maxx) maxx=x.getMaxx();
        if(x.getMaxy()>maxy) maxy=x.getMaxy();
    }
    slist.push_back(x);
}

void Character::process_character(){
     int size = slist.size();
     if(size == 1){
         for (int i=0;i<slist[0].getsize();i++){
             sampledChar.push_back(slist[0].getPoint(i));
         }
         ScaleCharacter();
     }
     else{
         for(int i=0;i<slist[0].getsize();i=i+2){
             sampledChar.push_back(slist[0].getPoint(i));
         }
         for(int i=0;i<slist[1].getsize();i=i+2){
             sampledChar.push_back(slist[1].getPoint(i));
         }
         ScaleCharacter();


     }

}

void Character::ScaleCharacter(){
    float length=maxx-minx;
    float width=maxy-miny;
    float ratio;
    if(length > width){
        ratio=1/length;
    }
    else{
        ratio=1/width;
    }
    for(int i=0;i<sampledChar.size();i++){
        sampledChar[i].x = (sampledChar[i].x - minx)*ratio;
        sampledChar[i].y = (sampledChar[i].y - miny)*ratio;

    }
    maxx=maxx*ratio;
    maxy=maxy*ratio;
    minx=minx*ratio;
    miny=miny*ratio;
    printScaledSample();
}

void Character::printScaledSample(){
    for(int i=0;i<sampledChar.size();i++){
        cout<<"( "<<sampledChar[i].x<<" , "<<sampledChar[i].y<<" )"<<endl;
    }
}

string Character::preprocessing(){
    string finalValue;
    int Strokeno=slist.size();
    if(Strokeno==1){
        int orientation=slist[0].getOrientation();
        if(orientation==0){
            finalValue="H1";             //horizontal
            return finalValue;
        }
        if(orientation==1){               //vertical
            float fraction=2;
            if(abs(sampledChar[0].x - sampledChar[sampledChar.size()-1].x)*fraction > (maxx-minx)){
                finalValue="V1";
                return finalValue;
            }
            else if((maxx - max(sampledChar[0].x ,sampledChar[sampledChar.size()-1].x))*fraction<=(maxx-minx)){
                finalValue="V3";
                return finalValue;
            }
            else{
                finalValue="V2";
                return finalValue;
            }

        }
        if(orientation==2){               //diagonal
            if(sampledChar[0].x < sampledChar[sampledChar.size()-1].x){
                finalValue="D1";
                return finalValue;
            }
            else{
                finalValue="D2";
                return finalValue;
            }
        }
        if(orientation==3){              //closed loop
            finalValue="L1";
            return finalValue;
        }
    }
    else{
        int orientation1=slist[0].getOrientation();
        int orientation2=slist[1].getOrientation();
        if(orientation1==1 && orientation2==1){
            finalValue="VV";
            return finalValue;
        }
        else if(orientation1==0 && orientation2==0){
            finalValue="HH";
            return finalValue;
        }
        else if(orientation1==2 && orientation2==2){
            finalValue="DD";
            return finalValue;
        }
        else if(orientation1==3 && orientation2==3){
            finalValue="LL";
            return finalValue;
        }
        else if(orientation1+orientation2==1){
            finalValue="HV";
            return finalValue;
        }
        else if(orientation1*orientation2==0){
            finalValue="HD";
            return finalValue;
        }
        else if(orientation1*orientation2==2){
            finalValue="VD";
            return finalValue;
        }
        else if(orientation1*orientation2==3){
            finalValue="VL";
            return finalValue;
        }
    }
}
