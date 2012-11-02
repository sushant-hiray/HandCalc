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
     }
     else{
         for(int i=0;i<slist[0].getsize();i=i+2){
             sampledChar.push_back(slist[0].getPoint(i));
         }
         for(int i=0;i<slist[1].getsize();i=i+2){
             sampledChar.push_back(slist[1].getPoint(i));
         }

     }

}
