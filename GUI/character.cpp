#include "character.h"
using namespace std;

Character::Character()
{
}
int Character::getno(){  //total strokes
    return slist.size();
}

void Character::print(){  //prints stroke list
    cout<<"(";
    for (int i=0;i<slist.size();i++){
        cout<<slist[i].getid()<<",";
    }
    cout<<") ";
}

void Character::push(Stroke x){ //insert a new stroke
    if(slist.empty()) {minx=x.getMinx();miny=x.getMiny();maxx=x.getMaxx();maxy=x.getMaxy();
    }
    else{
        if(x.getMinx()<minx) minx=x.getMinx();
        if(x.getMiny()<miny) miny=x.getMiny();
        if(x.getMaxx()>maxx) maxx=x.getMaxx();
        if(x.getMaxy()>maxy) maxy=x.getMaxy();
    }
    slist.push_back(x);
}

void Character::reorderStrokes(){   //reorder strokes according to direction
    for(int i=0; i <slist.size();i++){
        if(slist[i].directionflag==1){
            continue;
        }
        else{
            for(int k=0,j=slist[i].getsize() - 1; k < j; k++ ,j--){

                Pt temp;
                temp=slist[i].getPoint(k);
                slist[i].setPoint(slist[i].getPoint(j),k);
                slist[i].setPoint(temp,j);

            }
        }
    }
}

int Character::setPreference(){     //1- prefrence is correct by default , 0 - change the prefernece
    int refx=minx;
    int refy=miny;
    Pt lastpoint0=slist[0].getPoint(slist[0].getsize() - 1);
    Pt lastpoint1=slist[1].getPoint(slist[1].getsize() - 1);
    float angle0= (lastpoint0.y - refy)/(lastpoint0.x -refx);
    float angle1= (lastpoint1.y - refy)/(lastpoint1.x -refx);
    if( angle0 <= angle1){
        return 1;

    }
    else{
        return 0;

    }
}

void Character::process_character(){  //processing of character sampling and then scaling
     int size = slist.size();
     reorderStrokes();
     if(size == 1){
          for (int i=0;i<slist[0].getsize();i++){
               sampledChar.push_back(slist[0].getPoint(i));
          }
        ScaleCharacter();
     }
     else{
         int flag=setPreference();
         if(flag==1){
            for(int i=0;i<slist[0].getsize();i=i+2){
                 sampledChar.push_back(slist[0].getPoint(i));
             }
            for(int i=0;i<slist[1].getsize();i=i+2){
              sampledChar.push_back(slist[1].getPoint(i));
             }
         }
         else{
             for(int i=0;i<slist[1].getsize();i=i+2){
               sampledChar.push_back(slist[1].getPoint(i));
              }
             for(int i=0;i<slist[0].getsize();i=i+2){
                  sampledChar.push_back(slist[0].getPoint(i));
              }
         }
         ScaleCharacter();

      }
}

void Character::ScaleCharacter(){   //scaling the character to 1x1 square
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
    orgmaxx=maxx;
    maxx=(maxx-minx)*ratio;
    orgmaxy=maxy;
    maxy=(maxy-miny)*ratio;
    orgminx=minx;
    minx=(minx-minx)*ratio;
    orgminy=miny;
    miny=(miny-miny)*ratio;
}

void Character::printScaledSample(){   //used for debugging
    for(int i=0;i<sampledChar.size();i++){
        cout<<"( "<<sampledChar[i].x<<" , "<<sampledChar[i].y<<" )"<<endl;
    }
}

bool lineoutput(float slope,float c,float x,float y){  //checks if a point lies to left or right of a line
    float ref;
    ref=slope*x-y+c;
    if(c==0){
        if(ref < 0){
            return 1;

        }
        else{
            return 0;
        }
    }
    else if(ref*c>0){
        return 1;   //it lies on the left
    }
    else{
        return 0;  //right
    }
}

string Character::preprocessing(){   //returns the key value after processing the character
    string finalValue;
    int Strokeno=slist.size();
    if(Strokeno==1){
        int orientation=slist[0].getOrientation();
        if(orientation==0){
            finalValue="H1";             //horizontal
            return finalValue;
        }
        if(orientation==1){           //vertical stroke
            //vertical
            float fraction=2;

            if((maxx-minx)/(maxy-miny) < distortion){

                float leftcount=0;
                float rightcount=0;
                if(sampledChar[0].x==sampledChar[sampledChar.size()-1].x){   //finding the number of points which lie to left and right

                    for(int q=0;q<sampledChar.size();q++){

                        if(sampledChar[q].x <= sampledChar[0].x){
                            leftcount++;
                        }
                        else{
                            rightcount++;
                        }
                    }
                    float fraction;
                    fraction=leftcount/(leftcount + rightcount);
                    float g=0.2;
                    float h=0.8;
                    if(fraction < g || fraction > h){
                        finalValue="V1";
                    }
                    else if(fraction < 0.37 ){
                        finalValue="V2";
                    }
                    else{
                        finalValue="V3";
                    }

                }
                else{

                    float y2=sampledChar[sampledChar.size()-1].y;
                    float x2=sampledChar[sampledChar.size()-1].x;
                    float y1=sampledChar[0].y;
                    float x1=sampledChar[0].x;
                    float slope=(y2 - y1)/(x2 - x1);
                    float c = (y1*x2 -y2*x1)/(x2 - x1);

                    for(int q=0;q<sampledChar.size();q++){
                        if(lineoutput(slope,c,sampledChar[q].x,sampledChar[q].y)){
                            leftcount++;
                        }
                        else{
                            rightcount++;
                        }
                    }
                    float fraction;


                    fraction=leftcount/(leftcount + rightcount);

                    float g=0.2;
                    float h=0.8;
                    if(fraction < g || fraction > h){  //Type V1
                        finalValue="V1";
                    }
                    else if(fraction < 0.37 ){   //Type V2
                        finalValue="V2";
                    }
                    else{
                        finalValue="V3";   //Type V3
                    }


                }

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
        if(orientation==2){               //diagonal stroke
            if(sampledChar[0].y < sampledChar[sampledChar.size()-1].y){
                finalValue="D1";
                return finalValue;
            }
            else{
                finalValue="D2";
                return finalValue;
            }
        }
        if(orientation==3){              //closed loop stroke
            finalValue="L1";
            return finalValue;
        }
    }
    else{  // character consists of 2 strokes
        int orientation1=slist[0].getOrientation();
        int orientation2=slist[1].getOrientation();
        if(orientation1==1 && orientation2==1){  //both are vertical
            finalValue="VV";
            return finalValue;
        }
        else if(orientation1==0 && orientation2==0){  //both are horizontal
            finalValue="HH";
            return finalValue;
        }
        else if(orientation1==2 && orientation2==2){  //both are diagonal
            finalValue="DD";
            return finalValue;
        }
        else if(orientation1==3 && orientation2==3){ //both are looped
            finalValue="LL";
            return finalValue;
        }
        else if(orientation1+orientation2==1){  //1-horizontal and 1-vertical
            finalValue="HV";
            return finalValue;
        }
        else if(orientation1*orientation2==0){  //1-horizontal and 1--diagonal
            finalValue="HD";
            return finalValue;
        }
        else if(orientation1*orientation2==2){   //1-vertical and 1-diagonal
            finalValue="VD";
            return finalValue;
        }
        else if(orientation1*orientation2==3){   //1 vertical and 1-loop
            finalValue="VL";
            return finalValue;
        }
    }
}
