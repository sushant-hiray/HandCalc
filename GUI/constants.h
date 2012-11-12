#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <list>
#include<vector>
#include<fstream>
#include<cstring>
#include<stdio.h>
#include<map>
using namespace std;

#define SR 36  //sampling rate
#define distortion 0.3 // x/y

//constants for preprocessing
#define Delta 0.20
#define Threshold 0.5
struct Pt{
    float x;
    float y;
};

struct feature{
    string id; //id is the actual symbol
    vector<Pt> vec;
};
void whitespace(ifstream& in);
void readDatabase(multimap<string,feature>& trainingData);
void readXY(float& x,float& y,ifstream& in);

#endif // CONSTANTS_H
