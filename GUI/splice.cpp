#include "splice.h"
#include <cmath>

Splice::Splice()
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

/*void Splice::readDatabase(){
    ifstream read;
    read.open("DataBase.txt"); */




void Splice::pushStrokePoint(int x, int y, long t){
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

void Splice::setStrokeChange(){
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
    //strokeList[strokeCount].updateStroke();
    strokeList[strokeCount].sampleStroke();
    strokeList[strokeCount].updateSampleStroke();
    currpos=strokeCount; //cout<<"strokecoutn is............................."<<strokeCount<<endl;
    charprocess();
    //---@@@
}


//@@@
int Splice::judge(int i,int j){
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

void Splice::charprocess(){
    //cout<<"processing now................"<<lastpro<< "    "<<currpos;
    int result=judge(lastpro,currpos);
    if(lastpro==currpos); //do nothing because only one stroke in hand so wait for next stroke
    else if(result==0){ //same character
        Character temp;
        temp.push(strokeList[lastpro]);
        temp.push(strokeList[currpos]);
        temp.process_character();
        lastpro=currpos+1;
        characterList.push_back(temp);

    }

    else if(result==2) { //make lastpro a character and move lastpro pointr to currpos
        //cout<<"########   into res 2  "<<strokeList[lastpro].getid()<<endl;
        Character temp;
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
    if(lastpro>currpos) ;//cout<<"WE are done ^^^^^^^^^^^^^^^^^^^^^^^^\n";//we are done as last go coupled with sec-last
         else{
             Character temp;
             temp.push(strokeList[strokeList.size()-1]);
             temp.process_character();
             characterList.push_back(temp);
         }
         //---@@@ END CASE HANDLED

         //strokeList[strokeList.size()-1].updateSampleStroke();
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
            //pair<string,feature>::iterator trainingData.find(*i);
            //DataBase<<(*i)<< ":\n";
            multimap<string,feature>::iterator local_it = trainingData.find(s);
            for (int j=0;j<count ; ++local_it ,j++ ){
               // printfeature(local_it->second,trainingData);
                float cost=DTW(characterList[i].sampledChar,local_it->second.vec);
                if(cost < mincost){
                    mincost=cost;
                    best=local_it->second.id;
                }
            }
            cout<<"Best Match is "<<best<<endl;
            output.append(best);
        }
         cout<<"final Result is "<<output<<endl;
         //ResetData();
         cout<<characterList.size()<<" "<<strokeList.size()<<endl;
        return output;

}

void Splice::changeKey(string text){
    key=text;
}

void Splice::TrainingProgram(){
    if(lastpro>currpos) ;//cout<<"WE are done ^^^^^^^^^^^^^^^^^^^^^^^^\n";//we are done as last go coupled with sec-last
         else{
             Character temp;
             temp.push(strokeList[strokeList.size()-1]);
             temp.process_character();
             characterList.push_back(temp);
         }
         //---@@@ END CASE HANDLED

         //strokeList[strokeList.size()-1].updateSampleStroke();
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
             float cost=DTW(characterList[0].sampledChar,local_it->second.vec);
             if(cost < mincost){
                 mincost=cost;
                 best=local_it->second.id;
             }
         }
         if(best == key){
             cout<<"No need of inserting Training Data for "<<reference<<" with reference value "<<key<<endl;
         }

         else{
             trainingData.insert(make_pair(reference,temp));
             cout<<"Inserted new Training Data for "<<reference<<" with reference value "<<key<<endl;
         }

         ResetData();
}

void Splice::writeMap(){
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

void Splice::ResetData(){
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
    currpos=0;
    yup=10000;
    ydown=0;
    //---@@@
}

int Splice::cgetMinx(int i){
    return characterList[i].getMinx();
}
int Splice::cgetMiny(int i){
    return characterList[i].getMiny();
}
int Splice::cgetMaxx(int i){
    return characterList[i].getMaxx();
}
int Splice::cgetMaxy(int i){
    return characterList[i].getMaxy();
}

void Splice::printfeature(feature &f, ofstream &out){
    out<<"\t"<<f.id <<":\n";
    for(int i=0;i<f.vec.size();i++){
        out<<"\t\t("<<f.vec[i].x <<","<<f.vec[i].y<<")"<<endl;
    }
}
//---@@@

//helper
/*for(  multimap<char,int>::iterator it = mymm.begin(), end = mymm.end(); it != end; it = mymm.upper_bound(it->first))
  {
      cout << it->first << ' ' << it->second << endl;
  }
*/
