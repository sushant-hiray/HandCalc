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
    vector<Stroke> strokeList;
    vector<Character> characterList;
    list<string> Keys;
    multimap<string,feature> trainingData;
    //bool modified;
    //bool scribbling;
    bool strokeChanged;
    int strokeCount;
    int prevx,prevy;
    string key;



    //for characterlist
    //vector<Character> characterList;
    int lastpro; //last stroke passed
    int currpos; //currpos
    int yup;
    int ydown;
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
    int cgetMinx(int i);
    int cgetMiny(int i);
    int cgetMaxx(int i);
    int cgetMaxy(int i);
    int csize(){
        return characterList.size();
    }
    void setStrokeChange();
    void ResetData();
    void writeMap();
    void printfeature(feature& f,ofstream &out);

};

#endif // SPLICE_H
