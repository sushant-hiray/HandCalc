#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <list>
#include<vector>
#include<fstream>
#include<cstring>
#include<stdio.h>
using namespace std;

#define SR 36  //sampling rate

//constants for preprocessing
#define Delta 0.37
#define Threshold 0.5
struct Pt{
    float x;
    float y;
};

struct feature{
    string id; //id is the actual symbol
    vector<Pt> vec;
};

#endif // CONSTANTS_H
