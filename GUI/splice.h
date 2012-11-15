#ifndef SPLICE_H
#define SPLICE_H
#include "character.h"
#include "DTW.h"
#include <vector>
#include <fstream>
#include <unordered_map>
#include<map>
#include <QString>
#include <utility>
#include <cstring>
class Splice
{

private:
    vector<Stroke> strokeList;      //CONTAINER TO STORE STROKES
    vector<Character> characterList;        //CONTAINER TO STORE CHARACTERS
    list<string> Keys;              //LIST OF FEATURES
    multimap<string,feature> trainingData;  //STORES ALL TRAINING DATA IN A MAP
    //bool modified;
    //bool scribbling;
    bool strokeChanged; //  TELLS WHEATHER STROKE IS CHANGED OR NOT
    int strokeCount;    //COUNT THE NO. OF STROKES
    int prevx,prevy;    //
    string key;        //



    //for characterlist
    //vector<Character> characterList;
    int lastpro; //last stroke passed
    int currpos; //currpos
    int yup;    //
    int ydown;  //
    int judge(int i,int j);// judges whether the two strokes i and j in strokelist belong to same character
    void charprocess();//judges and if allowed pushes a new character into the characterlist called in mouserelease event
    //NOTE will miss the last stroke if second last stroke already taken into a character so process the last stroke
    //take care of this when called evaluate .... if lastpos>curpos then last stroke ok else add last stroke as a character

public:
    Splice();
    //@@@strokes
    void pushStrokePoint(int x,int y, long int t);
    string lastCase();
    //void readDatabase();
    void TrainingProgram();       //left to be written
    void changeKey(string text);
    myRect backSpace();  //delete last stroke(if alone) or last character(in no lonely stroke left)
    int cgetMinx(int i);    //RETURNS MINIMUM X-COORDINATE OF A CHARACTER
    int cgetMiny(int i);    //RETURNS MINIMUM Y-COORDINATE OF A CHARACTER
    int cgetMaxx(int i);    //RETURNS MAXIMUM X-COORDINATE OF A CHARACTER
    int cgetMaxy(int i);    //RETURNS MAXIMUM Y-COORDINATE OF A CHARACTER
    int csize(){            //RETURNS THE SIZE OF characterList
        return characterList.size();
    }
    void setStrokeChange();     //IT IGNORES STRAY STROKES AND PROCESS THE PREVIOUS STROKE
    void ResetData();           //RESETSS ALL THE DATA OF THIS OBJECT TO THEIR DEFAULT VALUE
    void writeMap();            //WRITES THE FEATURE VECTOR TO DATABASE FILE
    void printfeature(feature& f,ofstream &out);

};

#endif // SPLICE_H
