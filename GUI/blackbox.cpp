#include "blackbox.h"
#include <cmath>

BlackBox::BlackBox()
{
    //scribbling = false;
    strokeChanged = true;
    strokeCount =-1;

    //@@@   for characterlist
    lastpro=0;
    currpos=0;
    yup=10000;
    ydown=0;
    //---@@@

    out.open("strokes.txt");

}

void BlackBox::pushStrokePoint(int x, int y, long t){
    if(strokeChanged==true){
        if(y<yup) yup=y;
        if(y>ydown) ydown=y;
        strokeChanged=false;
        strokeCount++;
        prevx=x;prevy=y;
        out<<".\n";
        strokeList.push_back(Stroke(strokeCount));
        strokeList[strokeCount].push(x,y,t);
    }
    else  {
        strokeList[strokeCount].push(x,y,t);
        strokeList[strokeCount].addtopath(sqrt(pow(x-prevx , 2) + pow(y-prevy,2)));
        prevx=x;prevy=y;
    }

    out<<x<<","<<y<<endl;
}

void BlackBox::setStrokeChange(){
    if(strokeCount >= 0){
        cout<< "path length of stroke is" <<strokeList[strokeCount].getpathlength() << endl;
    }
    strokeChanged=true;
    //@@@
    strokeList[strokeCount].updateStroke();
    strokeList[strokeCount].sampleStroke();
    currpos=strokeCount; //cout<<"strokecoutn is............................."<<strokeCount<<endl;
    charprocess();
    //---@@@
}


//@@@
int BlackBox::judge(int i,int j){
     float delta=(ydown-yup)*(0.1);
     //cout<<"DELATA............"<<delta<<" "<<ydown<< " "<<yup<<"  VV.."<<i<<" "<<j<<strokeList[j].getMinx()<<" "<<strokeList[i].getMaxx()<<endl;
     if (delta < strokeList[i].getMinx()-strokeList[j].getMaxx()){
         //stroke boxes are seperated by more than delta
         return 1; //means 1st stroke can be treated as character
     }
     else if(delta < strokeList[j].getMinx()-strokeList[i].getMaxx()){
         return 2;
     }
     else return 0; //means they belong to same character
 }

void BlackBox::charprocess(){
    //cout<<"processing now................"<<lastpro<< "    "<<currpos;
    int result=judge(lastpro,currpos);
    if(lastpro==currpos); //do nothing because only one stroke in hand so wait for next stroke
    else if(result==0){ //same character
        Character temp;
        temp.push(strokeList[lastpro]);
        temp.push(strokeList[currpos]);
        lastpro=currpos+1;
        characterList.push_back(temp);
    }

    else if(result==2) { //make lastpro a character and move lastpro pointr to currpos
        //cout<<"########   into res 2  "<<strokeList[lastpro].getid()<<endl;
        Character temp;
        temp.push(strokeList[lastpro]);
         characterList.push_back(temp);
         //cout<<"printing the first character "<<characterList.size()<<"  ";characterList[0].print();cout<<endl;

         lastpro++;
    }
    else if(result==1){ //make currpro a character
                        //wont happen as we write left to right
                        //and if diff chars then lastpro becomes char first
        Character temp;
        lastpro++;
        temp.push(strokeList[currpos]);
         characterList.push_back(temp);
    }
}

void BlackBox::lastCase(){
    if(lastpro>currpos) ;//cout<<"WE are done ^^^^^^^^^^^^^^^^^^^^^^^^\n";//we are done as last go coupled with sec-last
         else{
             Character temp;
             temp.push(strokeList[strokeList.size()-1]);
             characterList.push_back(temp);
         }
         //---@@@ END CASE HANDLED

         strokeList[strokeList.size()-1].updateStroke();
         cout<<"Hello.....now printing about characters formed \n no of characters ="<< characterList.size();
         for(int i=0;i<characterList.size();i++){
             characterList[i].print();
         }

         cout<<"\nNumber of strokes identified "<<strokeList.size()<<endl;
         //@@@
         out.close();

}

int BlackBox::cgetMinx(int i){
    return characterList[i].getMinx();
}
int BlackBox::cgetMiny(int i){
    return characterList[i].getMiny();
}
int BlackBox::cgetMaxx(int i){
    return characterList[i].getMaxx();
}
int BlackBox::cgetMaxy(int i){
    return characterList[i].getMaxy();
}

//---@@@


