#include "splice.h"
#include <cmath>

Splice::Splice()   //default constructor
{
    //scribbling = false;
    strokeChanged = true;
    strokeCount =-1;

    // for characterlist
    lastpro=0;
    currpos=-1;
    yup=10000;
    ydown=0;
    //
    //push keys into the keylist
    Keys.push_back("H1");
    Keys.push_back("V1");
    Keys.push_back("V2");
    Keys.push_back("V3");
    Keys.push_back("D1");
    Keys.push_back("D2");
    Keys.push_back("L1");

    Keys.push_back("VV");
    Keys.push_back("HH");
    Keys.push_back("DD");
    Keys.push_back("LL");
    Keys.push_back("HV");
    Keys.push_back("HD");
    Keys.push_back("VD");
    Keys.push_back("VL");
  //  readDatabase();
   readDatabase(trainingData);
}



void Splice::pushStrokePoint(int x, int y, long t){   //push stroke point in the stroke vector
    if(y<yup) yup=y;
    if(y>ydown) ydown=y;
    if(strokeChanged==true){
        strokeChanged=false;
        strokeCount++;
        prevx=x;prevy=y;
        strokeList.push_back(Stroke(strokeCount));
        strokeList[strokeCount].push(x,y,t);
    }
    else  {
        strokeList[strokeCount].push(x,y,t);
        strokeList[strokeCount].addtopath(sqrt(pow(x-prevx , 2) + pow(y-prevy,2)));
        prevx=x;prevy=y;
    }
}

void Splice::setStrokeChange(){  //new stroke input!
    float StrayStrokeLength = 20.0;
    if(strokeCount >= 0){
        cout<< "path length of stroke is" <<strokeList[strokeCount].getpathlength() << endl;
    }
    strokeChanged=true;
    //@@@
    if(strokeList[strokeCount].getpathlength()  < StrayStrokeLength) { //stray mark identified ignoring
        cout<<"Stray mark .... Ignored \n";
        strokeCount-- ;
        strokeList.pop_back();
        return;
    }
    //update previous Stroke
    strokeList[strokeCount].sampleStroke();
    strokeList[strokeCount].updateSampleStroke();
    currpos=strokeCount; //cout<<"stroke count  is "<<strokeCount<<endl;
    charprocess();
    cout<<"charprocessing done wiht stokelist size"<< strokeList.size()<<"charaaterlist size "<<characterList.size()<< " currpos" <<currpos<<"lastpro "<<lastpro<<endl;
    //---@@@
}


//@@@
int Splice::judge(int i,int j){
     float delta=(ydown-yup)*(0.1);
     //cout<<"delta values "<<delta<<" "<<ydown<< " "<<yup<<"  VV.."<<i<<" "<<j<<strokeList[j].getMinx()<<" "<<strokeList[i].getMaxx()<<endl;
     if (delta < strokeList[i].getMinx()-strokeList[j].getMaxx()){
         //stroke boxes are seperated by more than delta
         return 1; //means 1st stroke can be treated as character
     }
     else if(delta < strokeList[j].getMinx()-strokeList[i].getMaxx()){
         return 2;
     }
     else return 0; //means they belong to same character
 }

void Splice::charprocess(){
    //cout<<"processing now................"<<lastpro<< "    "<<currpos;
    int result=judge(lastpro,currpos);
    if(lastpro==currpos); //do nothing because only one stroke in hand so wait for next stroke
    else if(result==0){ //same character formed by two strokes at currpos and lastpro
        Character temp;
        //set flags of strokes in the strokeList that they've been used as a part of the character in characterlist
        strokeList[lastpro].intocharlist=1;
        strokeList[currpos].intocharlist=1;
        temp.push(strokeList[lastpro]);
        temp.push(strokeList[currpos]);
        temp.process_character();
        lastpro=currpos+1;
        characterList.push_back(temp);
    }

    else if(result==2) { //make lastpro a character and move lastpro pointr to currpos
        //cout<<"########   into res 2  "<<strokeList[lastpro].getid()<<endl;
        Character temp;
        strokeList[lastpro].intocharlist=1;
        temp.push(strokeList[lastpro]);
        temp.process_character();
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
        temp.process_character();
        characterList.push_back(temp);
    }
}

string Splice::lastCase(){
    if(lastpro>currpos) ;//cout<<"WE are done \n";//we are done as last go coupled with sec-last
         else{
        cout<<"lastCase "<<lastpro<<" "<<currpos<<endl;
             Character temp;
             strokeList[strokeList.size()-1].intocharlist=1; //set flag (part of charlist) in the last stroke which is inserted as a character
             temp.push(strokeList[strokeList.size()-1]);
             temp.process_character();
             characterList.push_back(temp);
             //currpos++;
             lastpro++;
         }
         //---@@@ END CASE HANDLED

         cout<<"Printing characters formed \n no of characters ="<< characterList.size();
         for(int i=0;i<characterList.size();i++){
             characterList[i].print();
         }

         cout<<"\nNumber of strokes identified "<<strokeList.size()<<endl;
         //@@@

         cout<< "info about primary preprocessing ";
         string best;
         string output;
         for (int i=0;i<characterList.size();i++){
            float mincost=1000;
            string s;
            s=characterList[i].preprocessing();
            cout<<"preprocessed "<< s<<endl;
            int count = trainingData.count(s);
            multimap<string,feature>::iterator local_it = trainingData.find(s);
            for (int j=0;j<count ; ++local_it ,j++ ){
                DTW temp;
                float cost=temp.warp(characterList[i].sampledChar,local_it->second.vec);
                if(cost < mincost){
                    mincost=cost;
                    best=local_it->second.id;
                }
            }
            cout<<"Best Match is "<<best<<endl;
            output.append(best);
        }
         cout<<"final Result is "<<output<<endl;
         //Reset previous Data
         cout<<characterList.size()<<" "<<strokeList.size()<<endl;
        return output;

}

void Splice::changeKey(string text){  //changes key of a given character
    key=text;
}

void Splice::TrainingProgram(){   //training data
    if(lastpro>currpos) ;//we are done as last go coupled with sec-last
         else{
             Character temp;
             temp.push(strokeList[strokeList.size()-1]);
             temp.process_character();
             characterList.push_back(temp);
         }
         //END CASE HANDLED

         //updateSampleStroke
         cout<<"Hello.....now printing about characters formed \n no of characters ="<< characterList.size();
         for(int i=0;i<characterList.size();i++){
             characterList[i].print();
         }

         cout<<"\nNumber of strokes identified "<<strokeList.size()<<endl;
         //@@@
         feature temp;
         temp.id=key;
         temp.vec=characterList[0].sampledChar;
         cout<< "info about primary preprocessing: "<<endl;
         string reference;
         reference=characterList[0].preprocessing();


         //matching the characters
         float mincost=10000;
         string best;
         multimap<string,feature>::iterator local_it = trainingData.find(reference);
         int count = trainingData.count(reference);
         for (int j=0;j<count ; ++local_it ,j++ ){
             DTW temp;
             float cost=temp.warp(characterList[0].sampledChar,local_it->second.vec);
             if(cost < mincost){
                 mincost=cost;
                 best=local_it->second.id;
             }
         }
         if(best == key){  //the match found is correct so need to improve database
             cout<<"No need of inserting Training Data for "<<reference<<" with reference value "<<key<<endl;
         }

         else{  //match found is incorrect update dataset
             trainingData.insert(make_pair(reference,temp));
             cout<<"Inserted new Training Data for "<<reference<<" with reference value "<<key<<endl;
         }

         ResetData();
}

void Splice::writeMap(){   //after training is complete write all new data into the database
    ofstream DataBase("DataBase.txt");
    for(list<string>::iterator i=Keys.begin();i!=Keys.end();i++){
        int count = trainingData.count(*i);
        //pair<string,feature>::iterator trainingData.find(*i);
        DataBase<<(*i)<< ":\n";
        multimap<string,feature>::iterator local_it = trainingData.find(*i);
        for (int j=0;j<count ; ++local_it ,j++ ){
            printfeature(local_it->second,DataBase);

        }
    }
    DataBase<<"end";
}

void Splice::ResetData(){   //Reset the data remove previous stroke from character list
    if(!strokeList.empty()){
        strokeList.erase(strokeList.begin(),strokeList.end());
    }
     if(!characterList.empty()){
        characterList.erase(characterList.begin(),characterList.end());
     }
     cout<<strokeList.size()<<"in reset Data   "<<characterList.size()<<endl;
    strokeChanged = true;
    strokeCount =-1;
 //@@@   for characterlist
    lastpro=0;
    currpos=-1;
    yup=10000;
    ydown=0;
    //---@@@
}

int Splice::cgetMinx(int i){   //returns minimum x of character
    return characterList[i].getMinx();
}
int Splice::cgetMiny(int i){
    return characterList[i].getMiny(); //returns minimum y of character
}
int Splice::cgetMaxx(int i){
    return characterList[i].getMaxx();  //returns maximum x of character
}
int Splice::cgetMaxy(int i){  //returns maximum y of character
    return characterList[i].getMaxy();
}

void Splice::printfeature(feature &f, ofstream &out){
    out<<"\t"<<f.id <<":\n";
    for(int i=0;i<f.vec.size();i++){
        out<<"\t\t("<<f.vec[i].x <<","<<f.vec[i].y<<")"<<endl;
    }
}
//---@@@

myRect Splice::backSpace(){
    cout<<"Deleting command called with currpos "<<currpos<< " and lastpro "<<lastpro<<endl;
    myRect delArea;
    if(currpos==-1) {cout<<"nothig to do"<<endl;
        /*do nothing as no strokes or character drawn till now*/}
    else if(currpos==lastpro){ //Case when one lonely stroke in hand
        cout<<"deleting last stroke with listsize"<<strokeList.size()<<endl;
        Stroke temp=strokeList.back();
        delArea.x1=temp.min_x;
        delArea.y1=temp.min_y;
        delArea.x2=temp.max_x;
        delArea.y2=temp.max_y;

        currpos--; strokeCount--;lastpro=lastpro ; //lastpro remains as it is
        strokeList.pop_back(); //remove the deleted stroke from strokelist

        //NOW to update the charactedList see if the last stroke is a part of the characterList as an individual character
        if(temp.intocharlist==1){ //it is the last character formed so pop the last character
            characterList.pop_back();
        }

        cout<<"DELETED last stroke NOW STROKELIST SIZE IS"<<strokeList.size()<<endl;
    }
    else if(currpos<lastpro){ //lastly character was formed and so no lone stroke ,, delete this character
        cout<<"deleting last character with charllistsize "<<characterList.size()<<endl;
        Character temp=characterList.back();
        delArea.x1=temp.orgminx;
        delArea.y1=temp.orgminy;
        delArea.x2=temp.orgmaxx;
        delArea.y2=temp.orgmaxy;
        int strokesno = temp.getno();
        currpos-=strokesno ;  strokeCount-=strokesno; lastpro-=strokesno; //update the counts
        for(int i=0;i<strokesno;i++) { strokeList.pop_back();}
        characterList.pop_back(); //pop one character
    }
    return delArea;
}
